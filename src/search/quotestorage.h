#ifndef QUOTESTORAGE_H
#define QUOTESTORAGE_H

#include <QWidget>

#include "helpers/qregexphighlighter.h"

namespace Ui {
class Quotestorage;
}

//Класс виджета дополнительного окна для копирования цитат из списка объектов основного окна

class Quotestorage : public QWidget
{
    Q_OBJECT

    QString result;

    //Переменная для подсветки
    QRegexpHighlighter *highlighter;

public:
    Quotestorage(QString pattern, QWidget *parent = nullptr);
    ~Quotestorage();

    void setQuote(QString str);

private slots:
    void on_edtPattern_textChanged(const QString &);
    void shutdown();
    void chooseFont();
    void copyToBuffer();

private:
    Ui::Quotestorage *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

signals:
    void iamclosed();
};

#endif // QUOTESTORAGE_H
