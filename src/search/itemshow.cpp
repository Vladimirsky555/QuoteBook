#include "itemshow.h"
#include "ui_itemshow.h"

#include <QFontDialog>
#include <QMessageBox>

ItemShow::ItemShow(QString str, QString bookName, QString chapterName,
                   QString textName, QString pattern, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemShow)
{
    ui->setupUi(this);

    setWindowTitle(bookName + ", " + chapterName + ", " + textName);//название текста

    ui->edtText->setHtml(str);

    //Подсветка
    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtText->document());
    highlighter->setPattern(pattern);

    ui->btnFont->setDefaultAction(ui->actionFont);
    connect(ui->actionFont, SIGNAL(triggered()), this, SLOT(chooseFont()));
}

ItemShow::~ItemShow()
{
    delete ui;
}

void ItemShow::chooseFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, QFont("MS Shell Dlg 2", 12), this);
    if (ok) {
        ui->edtText->setFont(font);

        QRegExp e("font-size");
        QString txt = ui->edtText->toHtml().replace(e," ");

        ui->edtText->clear();
        ui->edtText->setHtml(txt);

    } else {
        QMessageBox::information(this,"Сообщение","Шрифт не выбран");
    }
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

