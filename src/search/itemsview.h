#ifndef ITEMSVIEW_H
#define ITEMSVIEW_H

#include <QWidget>

#include "helpers/qregexphighlighter.h"

namespace Ui {
class ItemsView;
}

//Класс виджета, в который выводится список цитат, которые находятся на главном окне
//в виде объектов ItemView

class ItemsView : public QWidget
{
    Q_OBJECT

    //Переменная для подсветки
    QRegexpHighlighter *highlighter;

public:
    ItemsView(QString result, QString pattern, QWidget *parent = nullptr);
    ~ItemsView();

private slots:
    void on_edtPattern_textChanged(const QString &);
    void shutdown();
    void chooseFont();
    void copyToBuffer();

private:
    Ui::ItemsView *ui;
};

#endif // ITEMSVIEW_H
