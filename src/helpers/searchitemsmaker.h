#ifndef SEARCHITEMSMAKER_H
#define SEARCHITEMSMAKER_H

#include <QObject>

#include "data/storage.h"
#include "data/searchstorage.h"

//Класс для формирования списка текстов, в которых найдено хотя бы одно
//ключевое слово, а также списка цитат с найденным хотя бы одни ключевым словом, на
//основе этих текстов

class SearchItemsMaker : public QObject
{
    Q_OBJECT

    Storage *s;
    SearchStorage *ss;
    QString pattern;

public:
    SearchItemsMaker(Storage *s, SearchStorage *ss, QString pattern,
                              QObject *parent = nullptr);

    //формирует массив текстов, в которых есть искомое слово
    void searchItemsMakerfromCatalogs();
    void searchItemsMakerfromBooks(QList<BookItem*> booksList);

     //формирует массив цитат, в которых есть искомое слово
    void quoteMaker();

    //Вспомогательные для поиска функции
    int findInOneText(int *c, QString txt, QString pattern);
    bool checkRegExp(QRegExp rx);
};

#endif // SEARCHITEMSMAKER_H
