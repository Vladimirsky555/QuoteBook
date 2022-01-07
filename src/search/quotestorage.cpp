#include "quotestorage.h"
#include "ui_quotestorage.h"

#include <QFontDialog>
#include <QMessageBox>
#include <QClipboard>

Quotestorage::Quotestorage(QString pattern, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Quotestorage)
{
    ui->setupUi(this);

    this->result = "";

    setWindowTitle("Поисковое слово (фраза) - " + pattern +
                   ". Последующие цитаты будут добавляться в это окно");

    //Подсветка
    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtText->document());
    highlighter->setPattern(pattern);

    ui->btnFont->setDefaultAction(ui->actionFont);
    connect(ui->actionFont, SIGNAL(triggered()), this, SLOT(chooseFont()));

    ui->btnCopyToBuffer->setDefaultAction(ui->actionCopyToBuffer);
    connect(ui->actionCopyToBuffer, SIGNAL(triggered()), this, SLOT(copyToBuffer()));
}

Quotestorage::~Quotestorage()
{
    delete ui;
}

void Quotestorage::setQuote(QString str)
{
    ui->edtText->append(str);
    ui->edtText->append("");
}

void Quotestorage::on_edtPattern_textChanged(const QString &)
{
    highlighter->setPattern(ui->edtPattern->text());
    highlighter->rehighlight();
}

void Quotestorage::shutdown()
{
    close();
}

void Quotestorage::chooseFont()
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

void Quotestorage::copyToBuffer()
{
    QClipboard *clipboard = QApplication::clipboard();
    QTextDocument doc;
    doc.setHtml(ui->edtText->toHtml());
    QString str = doc.toPlainText();
    clipboard->setText(str);
    close();
}

void Quotestorage::closeEvent(QCloseEvent *event)
{
    emit iamclosed();
    QWidget::closeEvent(event);
}


