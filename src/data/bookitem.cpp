#include "bookitem.h"

#include <QIODevice>
#include <QDataStream>

BookItem::BookItem(QString name, QObject *parent) : QObject(parent)
{
     this->bookName = name;
}

BookItem::BookItem(QByteArray arr, QObject *parent) : QObject(parent){
    QDataStream str(&arr, QIODevice::ReadOnly);

    str >> this->bookName;

    while(!str.atEnd()){
        QByteArray tmp;
        str >> tmp;
       chapters.append(new ListItem(tmp));
    }
}

QString BookItem::getName()
{
    return this->bookName;
}


ListItem* BookItem::getChapterById(int id){
    if(id < chapters.count()){
    return chapters[id];
    }
    return NULL;
}

int BookItem::getCount()
{
    return chapters.size();
}

QList<ListItem *> BookItem::getChapters()
{
    return this->chapters;
}


ListItem *BookItem::getChapterByName(QString value)
{
    for(int i = 0; i < chapters.size(); i++){
        if(chapters[i]->getName() == value){
            return chapters[i];
        }
    }

    return NULL;
}


QByteArray BookItem::saveIt(){
    QByteArray arr;
    QDataStream str(&arr, QIODevice::WriteOnly);

    str << this->bookName;

    for(int i = 0; i < chapters.size(); i++){
        str << this->chapters[i]->saveIt();
    }

    return arr;
}

