#include "quotestorage.h"
#include "ui_quotestorage.h"

Quotestorage::Quotestorage(QString pattern, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Quotestorage)
{
    ui->setupUi(this);

    setWindowTitle("Поисковое слово (фраза) - " + pattern +
                   ". Последующие цитаты будут добавляться в это окно");

    //Подсветка
    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtText->document());
    highlighter->setPattern(pattern);
}

Quotestorage::~Quotestorage()
{
    delete ui;
}

void Quotestorage::setQuote(QString str)
{
    ui->edtText->append(str);
    ui->edtText->append(" ");
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

void Quotestorage::closeEvent(QCloseEvent *event)
{
    emit iamclosed();
    QWidget::closeEvent(event);
}

