#include "listitem.h"

#include <QIODevice>
#include <QDataStream>

ListItem::ListItem(QString name, QObject *parent) : QObject(parent)
{
    this->chapterName = name;
}

ListItem::ListItem(QByteArray arr, QObject *parent) : QObject(parent){
    QDataStream str(&arr, QIODevice::ReadOnly);

    str >> this->chapterName;

    while(!str.atEnd()){
        QByteArray tmp;
        str >> tmp;
        sections.append(new TextItem(tmp));
    }
}


QString ListItem::getName()
{
    return this->chapterName;
}

TextItem* ListItem::getSectionById(int id){
    if(id < sections.count()){
        return sections[id];
    }
    return NULL;
}

TextItem *ListItem::getSectionByName(QString value)
{
    for(int i = 0; i < sections.size(); i++){
        if(sections[i]->getName() == value){
            return sections[i];
        }
    }

    return NULL;
}

int ListItem::getCount()
{
    return sections.count();
}

QByteArray ListItem::saveIt(){
    QByteArray arr;
    QDataStream writer(&arr, QIODevice::WriteOnly);

    writer << this->chapterName;

    for(int i = 0; i < sections.size(); i++){
        writer << this->sections[i]->saveIt();
    }

    return arr;
}


