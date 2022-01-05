#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>

#include "textitem.h"

class ListItem : public QObject
{
    Q_OBJECT

    QString chapterName;
    QList<TextItem*> sections;

public:
    ListItem(QString, QObject *parent = nullptr);
    ListItem(QByteArray arr, QObject *parent = nullptr);

    QString getName();
    TextItem* getSectionById(int);
    TextItem* getSectionByName(QString value);
    int getCount();
    QByteArray saveIt();
};

#endif // LISTITEM_H
