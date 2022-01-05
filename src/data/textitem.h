#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QObject>

class TextItem : public QObject
{
    Q_OBJECT

    QString name;
    QString text;

public:
    explicit TextItem(QString name, QObject *parent = nullptr);
    TextItem(QByteArray arr, QObject *parent = nullptr);

    QString getName();
    QString getData();
    void setName(QString);
    QByteArray saveIt();
};

#endif // TEXTITEM_H
