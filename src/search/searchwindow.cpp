#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWindowTitle("Исследование цитат святых текстов");

    s = new Storage();
    ss = new SearchStorage();
    storage = NULL;

    this->resource = true;

    //Подключим ко всем toolButton экшены
    ui->btnFind->setDefaultAction(ui->actionFind);
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(find()));

    ui->btnBooksSelect->setDefaultAction(ui->action_books_select);
    connect(ui->action_books_select, SIGNAL(triggered()), this, SLOT(selectBooks()));

    ui->btnCatalogsSelect->setDefaultAction(ui->action_catalogs_select);
    connect(ui->action_catalogs_select, SIGNAL(triggered()), this, SLOT(selectCatalogs()));

    ui->btnShow->setDefaultAction(ui->actionShow);
    connect(ui->actionShow, SIGNAL(triggered()), this, SLOT(showQuotesList()));
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::showQuotesList()
{
    ItemsView *v = new ItemsView(ss->exportToDisplay(),
                                 ui->edtSearch->text());
    v->show();

    connect(this, SIGNAL(shutdown()),
            v, SLOT(shutdown()));
}

//Вспомогательная функция для очищения скроллэрии от всех объектов
void SearchWindow::clearScrollArea()
{
    QObjectList f = ui->scrollAreaWidgetContents->children();
    for (int i = 0; i < f.count(); i++){
        delete f[i];
    }
}

//Перерисовка новыми объектами скроллэрии после удаления элемента
void SearchWindow::Redraw(QList<quoteItem*> quoteItems)
{
    clearScrollArea();

    int lastY = 0;
    for(int i = 0; i < quoteItems.count(); i++){
        ItemView *v = new ItemView(quoteItems[i],//цитата и источник
                                   ui->edtSearch->text(),//поисковое слово в каждый блок
                                   ui->scrollAreaWidgetContents);

        QRect r = v->geometry();
        r.moveTop(lastY);
        lastY += r.height();
        v->setGeometry(r);
        v->show();

        connect(v,SIGNAL(deleteMe(quoteItem*,bool)),
                this,SLOT(RemoveElement(quoteItem*,bool)));

        connect(v, SIGNAL(sendQuote(QString)),
                this, SLOT(acceptQuote(QString)));

        connect(this, SIGNAL(shutdown()),
                v, SLOT(acceptshutdown()));

    }

    ui->scrollAreaWidgetContents->resize(
                ui->scrollAreaWidgetContents->width(),
                lastY
                );
}

//Вспомогательная функция для поиска текстов с искомой фразой по каталогам
void SearchWindow::searchItemsMakerfromCatalogs()
{
    //Обнуляем окно для записей для следующего поиска
    delete storage;
    storage = NULL;
    sim->searchItemsMakerfromCatalogs();
}

//Вспомогательная функция для поиска текстов с искомой фразой по книгам
void SearchWindow::searchItemsMakerfromBooks()
{
    //Обнуляем окно для записей для следующего поиска
    delete storage;
    storage = NULL;
    sim->searchItemsMakerfromBooks(s->booksList);
}

//Отображение результатов поиска на экране в виде объектов
//Из массива с текстами уже формируем массив цитат, который впоследствии используем
//при отображении всех цитат на экран
//Отображение результатов поиска в цитатах на экране
void SearchWindow::showResults()
{   
    sim->quoteMaker();//формирование списка цитат
    Redraw(ss->quoteItems);//отрисовка списка цитат
}

//Поиск по каталогам
void SearchWindow::findInCatalogs()
{
    //Уничтожаем результаты предыдущего поиска
    ss->destroySearchList();
    //Получаем массив текстов, в которых встречается искомое слово
    searchItemsMakerfromCatalogs();
    //Отображаем на экране результат
    showResults();
}

void SearchWindow::findInBooks()
{
    //Уничтожаем результаты предыдущего поиска
    ss->destroySearchList();
    //Получаем массив текстов, в которых встречается искомое слово
    searchItemsMakerfromBooks();
    //Отображаем на экране результат
    showResults();
}

//Запускается по сигналу от объекта. Указатель на объект фомируется в виджете.
//Поэтому эту функцию невозможно перенести в хранилище
//Скрываем объект или удаляем
void SearchWindow::RemoveElement(quoteItem *item, bool hidden)
{
    if(hidden){
        ss->quoteItems.removeOne(item);
    } else {
        ss->quoteItems.removeOne(item);
        Redraw(ss->quoteItems);
    }
}


//Реализация поиска
void SearchWindow::find()
{
    sim = new SearchItemsMaker(s, ss, ui->edtSearch->text());

    if(resource){
        findInCatalogs();
    } else {
        findInBooks();
    }
}

void SearchWindow::on_edtSearch_returnPressed()
{
    sim = new SearchItemsMaker(s, ss, ui->edtSearch->text());

    if(resource){
        findInCatalogs();
    } else {
        findInBooks();
    }
}

//Действие на кнопку выбора каталогов для поиска
//Мы переходим в виджет выбора каталогов, выбираем каталог
//Результат приходит в слот selectedCatalogs(QList<Catalog *> catalogs)
void SearchWindow::selectCatalogs()
{
    catalogs_selector = new CatalogsSelector(s);

    connect(catalogs_selector, SIGNAL(select(QList<Catalog*>)),
            this, SLOT(selectedCatalogs(QList<Catalog*>)));

    catalogs_selector->exec();
}

void SearchWindow::selectedCatalogs(QList<Catalog *> catalogs)
{
    resource = true;//ищем по каталогам
    s->catalogsList = catalogs;
}

//Действие на кнопку выбора книг для поиска
//Мы переходим в виджет выбора книг, выбираем книги
//Результат приходит в слот selectedBooks(QList<BookItem *> selectedBooks)
void SearchWindow::selectBooks()
{
    books_selector = new BooksSelector(s);

    connect(books_selector, SIGNAL(select(QList<BookItem*>)),
            this, SLOT(selectedBooks(QList<BookItem*>)));

    books_selector->exec();
}

void SearchWindow::selectedBooks(QList<BookItem *> selectedBooks)
{
    resource = false;//ищем по книгам
    s->booksList = selectedBooks;
}


//Слот для копирования цитаты в отдельный виджет storage
//Виджет создаётся с первой цитатой, следующая добавляется
void SearchWindow::acceptQuote(QString quote)
{
    if(storage != NULL){
        storage->setQuote(quote);
    } else {
        storage = new Quotestorage(ui->edtSearch->text());
        storage->show();
        storage->setQuote(quote);

        connect(this, SIGNAL(shutdown()),
                storage, SLOT(shutdown()));

        //при закрытии редактора цитат, чтобы была возможность снова его открыть
        connect(storage, SIGNAL(iamclosed()),
                this, SLOT(acceptfromquotestorage()));
    }
}

//слот для обнуления редактора цитат. Иначе при закрытии окна, второе не открывалось, ибо
//storage не был NULL
void SearchWindow::acceptfromquotestorage()
{
    delete storage;
    storage = NULL;
}

void SearchWindow::closeEvent(QCloseEvent *event)
{
    emit shutdown();
    QWidget::closeEvent(event);
}




