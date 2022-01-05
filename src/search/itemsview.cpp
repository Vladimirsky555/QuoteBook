#include "itemsview.h"
#include "ui_itemsview.h"

ItemsView::ItemsView(QString result, QString pattern, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsView)
{
    ui->setupUi(this);
    setWindowTitle("Список текстов с заданным словом (фразой)");

    ui->edtText->setHtml(result);

    //Подсветка
    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtText->document());
    highlighter->setPattern(pattern);
}

ItemsView::~ItemsView()
{
    delete ui;
}

void ItemsView::on_edtPattern_textChanged(const QString &)
{
    highlighter->setPattern(ui->edtPattern->text());
    highlighter->rehighlight();
}

void ItemsView::shutdown()
{
    close();
}

