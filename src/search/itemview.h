#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include <QClipboard>
#include <QTextDocument>

#include "data/quoteitem.h"
#include "helpers/qregexphighlighter.h"
#include "search/itemshow.h"
#include "search/quotestorage.h"

//Класс объекта цитаты, которая отражается в основном окне динамически


namespace Ui {
class ItemView;
}

class ItemView : public QWidget
{
    Q_OBJECT

    quoteItem *item;
    QString pattern;

    //Переменная для подсветки
    QRegexpHighlighter *highlighter;

public:
    explicit ItemView(quoteItem *item, QString pattern,
                      QWidget *parent = nullptr);
    ~ItemView();

private slots:
    void on_btnHide_clicked();
    void on_btnCopy_clicked();
    void on_btnText_clicked();
    void on_btnDel_clicked();
    void on_btnCopyToWidget_clicked();
    void acceptshutdown();//для передачи от осного виджета сигнала закрытия дальше

signals:
    void deleteMe(quoteItem*, bool);
    void sendQuote(QString quote);
    void shutdown();

private:
    Ui::ItemView *ui;
};

#endif // ITEMVIEW_H
