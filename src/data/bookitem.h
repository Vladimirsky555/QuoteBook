#ifndef BOOKITEM_H
#define BOOKITEM_H

#include <QObject>

#include "listitem.h"

class BookItem : public QObject
{
    Q_OBJECT

    QString bookName;
    QList<ListItem*> chapters;

public:
    BookItem(QString, QObject *parent = nullptr);
    BookItem(QByteArray arr, QObject *parent = nullptr);

    QString getName();
    ListItem* getChapterById(int);
    ListItem* getChapterByName(QString value);
    int getCount();
    QList<ListItem *> getChapters();//Используется для вывода содержания
    QByteArray saveIt();
};

#endif // BOOKITEM_H
