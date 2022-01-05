#ifndef CATALOG_H
#define CATALOG_H

#include <QObject>
#include "bookitem.h"

class Catalog : public QObject
{
    Q_OBJECT

    QList<BookItem*> books;
    QString name;
    QString path;

public:
    Catalog(QString, QString, QObject *parent = nullptr);
    Catalog(QByteArray arr, QObject *parent = nullptr);
    ~Catalog(){}

    QList<BookItem *> Books();
    void setBook(QList<BookItem*> books);
    BookItem* getBookById(int id);
    BookItem *getBookByName(QString name);
    QString getName();
    void setName(QString name);
    void setCatalogName(QString name);
    int getCount();
    QString getPath();
    void setPath(QString path);

    QByteArray saveIt();
};

#endif // CATALOG_H
