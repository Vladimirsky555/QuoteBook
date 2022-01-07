#include "itemview.h"
#include "ui_itemview.h"


ItemView::ItemView(quoteItem *item, QString pattern, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemView)
{
    ui->setupUi(this);

    this->item = item;
    this->pattern = pattern;

    ui->edtItemText->setHtml(this->item->res);
    ui->label->setText(QString::number(this->item->id));

    //Подсветка
    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtItemText->document());
    highlighter->setPattern(pattern);

    ui->btnFont->setDefaultAction(ui->actionFont);
    connect(ui->actionFont, SIGNAL(triggered()), this, SLOT(chooseFont()));

    ui->btnCopyToBuffer->setDefaultAction(ui->actionCopyToBuffer);
    connect(ui->actionCopyToBuffer, SIGNAL(triggered()), this, SLOT(copyToBuffer()));

    ui->btnCopyToWidget->setDefaultAction(ui->actionCopyToWidget);
    connect(ui->actionCopyToWidget, SIGNAL(triggered()), this, SLOT(copyToWidget()));

    ui->btnDelete->setDefaultAction(ui->actionDelete);
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteItem()));

    ui->btnHide->setDefaultAction(ui->actionHide);
    connect(ui->actionHide, SIGNAL(triggered()), this, SLOT(hideItem()));

    ui->btnText->setDefaultAction(ui->actionText);
    connect(ui->actionText, SIGNAL(triggered()), this, SLOT(showText()));
}

ItemView::~ItemView()
{
    delete ui;
}

void ItemView::chooseFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, QFont("MS Shell Dlg 2", 12), this);
    if (ok) {
        ui->edtItemText->setFont(font);

        QRegExp e("font-size");
        QString txt = ui->edtItemText->toHtml().replace(e," ");

        ui->edtItemText->clear();
        ui->edtItemText->setHtml(txt);

    } else {
        QMessageBox::information(this,"Сообщение","Шрифт не выбран");
    }
}

void ItemView::copyToBuffer()
{
    QClipboard *clipboard = QApplication::clipboard();
    //QString originalText = clipboard->text();

    QTextDocument doc;
    doc.setHtml(this->item->res);
    QString str = doc.toPlainText();

    str += "\n\n";
//    str += "***";
//    str += "\n\n";

    clipboard->setText(str);

    this->hide();
    emit deleteMe(this->item, true);
}

void ItemView::copyToWidget()
{
    emit sendQuote(this->item->res);
    this->hide();
    emit deleteMe(this->item, true);//спрячем объект после копирования
}

void ItemView::deleteItem()
{
    emit deleteMe(this->item, false);//удалим элемент с перерисовкой
}

void ItemView::hideItem()
{
    this->hide();
    emit deleteMe(this->item, true);//удалим элемент без перерисовки
}

void ItemView::showText()
{
    QString data = this->item->itemSearch->_section->getData();
    QString bookName = this->item->itemSearch->_book->getName();
    QString chapterName = this->item->itemSearch->_chapter->getName();
    QString textName = this->item->itemSearch->_section->getName();

    ItemShow *w = new ItemShow(data, bookName, chapterName, textName, this->pattern);
    w->show();

    connect(this, SIGNAL(shutdown()), w, SLOT(shutdown()));
}



void ItemView::acceptshutdown()
{
    emit shutdown();
}


