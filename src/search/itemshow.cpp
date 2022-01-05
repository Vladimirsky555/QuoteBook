#include "itemshow.h"
#include "ui_itemshow.h"

ItemShow::ItemShow(QString str, QString bookName, QString chapterName,
                   QString textName, QString pattern, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemShow)
{
    ui->setupUi(this);
    ui->edtText->setHtml(str);
    setWindowTitle(bookName + ", " + chapterName + ", " + textName);//название текста

    //Подсветка
    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtText->document());
    highlighter->setPattern(pattern);
}

ItemShow::~ItemShow()
{
    delete ui;
}

void ItemShow::on_edtPattern_textChanged(const QString &)
{
    highlighter->setPattern(ui->edtPattern->text());
    highlighter->rehighlight();
}

void ItemShow::shutdown()
{
    close();
}

