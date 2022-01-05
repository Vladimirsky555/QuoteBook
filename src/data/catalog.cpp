#include "catalog.h"

#include <QDataStream>
#include <QIODevice>


Catalog::Catalog(QString name, QString path, QObject *parent) : QObject(parent)
{
    this->name = name;
    this->path = path;

}

Catalog::Catalog(QByteArray arr, QObject *parent) :
    QObject(parent){
    {
        QDataStream str(&arr, QIODevice::ReadOnly);

        str >> this->name >> this->path;

        while(!str.atEnd()){
            QByteArray tmp;
            str >> tmp;
            books.append(new BookItem(tmp));
        }
    }
}


QString Catalog::getName()
{
    return this->name;
}

void Catalog::setName(QString name)
{
    this->name = name;
}

void Catalog::setCatalogName(QString name)
{
    this->name = name;
}

int Catalog::getCount()
{
    return books.count();
}

QString Catalog::getPath()
{
    return this->path;
}

void Catalog::setPath(QString path)
{
    this->path = path;
}


QList<BookItem *> Catalog::Books()
{
    return this->books;
}

void Catalog::setBook(QList<BookItem *> books)
{
    this->books = books;
}

BookItem *Catalog::getBookById(int id)
{
    if(id < books.count()){
    return books[id];
    }
    return NULL;
}

BookItem *Catalog::getBookByName(QString name)
{
    for(int i = 0; i < books.size(); i++){
        if(books[i]->getName() == name){
            return books[i];
        }
    }

    return NULL;
}


QByteArray Catalog::saveIt()
{
    QByteArray arr;
    QDataStream str(&arr, QIODevice::WriteOnly);

    str << this->name << path;

    for(int i = 0; i < books.size(); i++){
        str << this->books[i]->saveIt();
    }

    return arr;
}
