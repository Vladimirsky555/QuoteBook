#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include <QScrollBar>

#include "data/quoteitem.h"
#include "data/searchitem.h"
#include "data/searchstorage.h"
#include "search/itemview.h"
#include "search/itemsview.h"
#include "search/booksselector.h"
#include "search/catalogsselector.h"
#include "search/quotestorage.h"
#include "helpers/searchitemsmaker.h"

namespace Ui {
class SearchWindow;
}

//Основное окно программы

class SearchWindow : public QWidget
{
    Q_OBJECT

    Storage *s;//Хранилище данных
    SearchStorage *ss;//Хранилище результатов поиска и цитат

    bool resource;//выбор ресурса для поиска (книги, каталоги)

    CatalogsSelector *catalogs_selector;//Виджежет выбора каталогов (каталога)
    BooksSelector *books_selector;//Виджет выбора книг (книги)

    Quotestorage *storage;//Виджет для копирования цитат из объекта ItemView
    SearchItemsMaker *sim;//Переменная для формирования результата поиска и цитат

    Ui::SearchWindow *ui;

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

    void findInCatalogs();//поиск по всем каталогам
    void findInBooks();

    //формирует массив текстов, в которых есть искомое слово
    void searchItemsMakerfromCatalogs();
    void searchItemsMakerfromBooks();

    //Отображение на экране результатов поиска
    void showResults();


private slots:
    void RemoveElement(quoteItem* item, bool hidden);
    void showQuotesList();// отображение цитат на отдельном виджете

    //Поиск
    void find();
    void on_edtSearch_returnPressed();//поиск по всем каталогам

    //Выбор каталогов, книг для поиска
    void selectBooks();//вызов BooksSelector
    void selectedBooks(QList<BookItem*> selectedBooks);//список книг, результат из chooseFinder
    void selectCatalogs();//вызов CatalogSelector
    void selectedCatalogs(QList<Catalog*> catalogs);

    //Перерисовка виджетов
    void Redraw(QList<quoteItem *> quoteItems);
    void clearScrollArea();

    void acceptQuote(QString quote);
    void acceptfromquotestorage();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

signals:
    void shutdown();
};

#endif // SEARCHWINDOW_H
