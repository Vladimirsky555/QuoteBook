#ifndef QUOTEITEM_H
#define QUOTEITEM_H

#include <QObject>

#include "data/searchitem.h"

//Хотел создать структурку, но нужно передавать её в класс для отображения цитаты

class quoteItem : public QObject
{
    Q_OBJECT

public:

    QString res;
    int id;
    searchItem *itemSearch; //указатель на текст, из которого цитата

public:
    quoteItem(QObject *parent = nullptr);
};

#endif // QUOTEITEM_H
