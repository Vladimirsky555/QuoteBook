#ifndef ITEMSHOW_H
#define ITEMSHOW_H

#include <QWidget>

#include "helpers/qregexphighlighter.h"

namespace Ui {
class ItemShow;
}

class ItemShow : public QWidget
{
    Q_OBJECT

    //Переменная для подсветки
    QRegexpHighlighter *highlighter;

public:
    explicit ItemShow(QString str, QString bookName, QString chapterName, QString textName,
                      QString pattern, QWidget *parent = nullptr);
    ~ItemShow();

private slots:
    void on_edtPattern_textChanged(const QString &);
    void shutdown();

private:
    Ui::ItemShow *ui;
};

#endif // ITEMSHOW_H
