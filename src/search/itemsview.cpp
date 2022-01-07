#include "itemsview.h"
#include "ui_itemsview.h"

#include <QFontDialog>
#include <QMessageBox>
#include <QClipboard>

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

    ui->btnFont->setDefaultAction(ui->actionFont);
    connect(ui->actionFont, SIGNAL(triggered()), this, SLOT(chooseFont()));

    ui->btnCopyToBuffer->setDefaultAction(ui->actionCopyToBuffer);
    connect(ui->actionCopyToBuffer, SIGNAL(triggered()), this, SLOT(copyToBuffer()));
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

void ItemsView::chooseFont()
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

void ItemsView::copyToBuffer()
{
    QClipboard *clipboard = QApplication::clipboard();
    QTextDocument doc;
    doc.setHtml(ui->edtText->toHtml());
    QString str = doc.toPlainText();
    clipboard->setText(str);
    close();
}

