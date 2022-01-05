#include "itemview.h"
#include "ui_itemview.h"

#include <QDebug>
#include <QBuffer>

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
}

ItemView::~ItemView()
{
    delete ui;
}

void ItemView::on_btnHide_clicked()
{
    this->hide();
    emit deleteMe(this->item, true);//удалим элемент без перерисовки
}

void ItemView::on_btnDel_clicked()
{
    emit deleteMe(this->item, false);//удалим элемент с перерисовкой
}

void ItemView::on_btnCopy_clicked()
{ 
    QClipboard *clipboard = QApplication::clipboard();
    //QString originalText = clipboard->text();

    QTextDocument doc;
    doc.setHtml(this->item->res);
    QString str = doc.toPlainText();

    str += "\n\n";
    str += "***";
    str += "\n\n";

    clipboard->setText(str);

    this->hide();
    emit deleteMe(this->item, true);
}


void ItemView::on_btnText_clicked()
{
    QString data = this->item->itemSearch->_section->getData();
    QString bookName = this->item->itemSearch->_book->getName();
    QString chapterName = this->item->itemSearch->_chapter->getName();
    QString textName = this->item->itemSearch->_section->getName();
    ItemShow *w = new ItemShow(data, bookName, chapterName, textName, this->pattern);
    w->show();

    connect(this, SIGNAL(shutdown()),
            w, SLOT(shutdown()));
}



void ItemView::on_btnCopyToWidget_clicked()
{
    emit sendQuote(this->item->res);
    this->hide();
    emit deleteMe(this->item, true);//спрячем объект после копирования
}

void ItemView::acceptshutdown()
{
    emit shutdown();
}


