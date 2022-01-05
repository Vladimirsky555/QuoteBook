#include "searchitemsmaker.h"

SearchItemsMaker::SearchItemsMaker(Storage *s, SearchStorage *ss, QString pattern,
                                   QObject *parent) : QObject(parent)
{
    this->s = s;
    this->ss = ss;
    this->pattern = pattern;
}

void SearchItemsMaker::searchItemsMakerfromCatalogs()
{
    ss->searchItems.clear();
    ss->quoteItems.clear();

    int c = 0;
    for(int k = 0; k < s->catalogsList.count(); k++){

        Catalog *currentCatalog = s->catalogsList[k];
        int cnt = 0;

        for(int l = 0; l < currentCatalog->getCount(); l++){
            BookItem *currentBook = currentCatalog->getBookById(l);

            for(int i = 0; i < currentBook->getCount(); i++){
                ListItem *currentChapter = currentBook->getChapterById(i);

                for(int j = 0; j < currentChapter->getCount(); j++){
                   TextItem *currentSection = currentChapter->getSectionById(j);

                    cnt = findInOneText(&c, currentSection->getData(),
                                            this->pattern);
                    if(cnt != 0){
                        ss->addSearchItem(cnt, currentCatalog, currentBook,
                                         currentChapter, currentSection);
                    }
                    cnt = 0;
                }
            }
        }
    }
}

void SearchItemsMaker::searchItemsMakerfromBooks(QList<BookItem *> booksList)
{
    ss->searchItems.clear();
    ss->quoteItems.clear();

    int c = 0;
    int cnt = 0;
    for(int l = 0; l < booksList.count(); l++){
        BookItem *currentBook = booksList[l];
        Catalog *currentCatalog = s->getCatalogByBook(currentBook);

        for(int i = 0; i < currentBook->getCount(); i++){
            ListItem *currentChapter = currentBook->getChapterById(i);

            for(int j = 0; j < currentChapter->getCount(); j++){
                TextItem *currentSection = currentChapter->getSectionById(j);

                //если cnt > 0 это достаточно, чтобы зарегистрировать этот текст
                cnt = findInOneText(&c, currentSection->getData(),
                                        this->pattern);
                if(cnt != 0){
                    ss->addSearchItem(cnt, currentCatalog, currentBook,
                                      currentChapter, currentSection);
                }
                cnt = 0;
            }
        }
    }
}

void SearchItemsMaker::quoteMaker()
{
    QStringList strList; // список абзацев одного текста

    int cnt = 1;

    for(int i = 0; i < ss->searchItems.count(); i++){

        QString currentText = ss->searchItems[i]->_section->getData();
        QRegExp rx_("</p>");
        strList = currentText.split(rx_);
        for(int j = 0; j < strList.count(); j++){
            QRegExp rx(this->pattern);
            if(!checkRegExp(rx))return;
            int pos = 0;
            QString str = strList[j];

            //Проверка, чтобы исключить вывод одной цитаты, в которой искомое слово повторяется,
            //несколько раз
            int check = 0;
            while((pos = rx.indexIn(str, pos)) != -1){
                pos += rx.matchedLength();
                check++;
                if(check > 1)continue;
                ss->addQuoteItem(cnt, str, ss->searchItems[i]);
                cnt++;
            }
        }

        strList.clear();
    }
}

//Вспомогательная функция для поиска хотя бы одного совпадения с ключевым словом
//в тексте. Возвращает число совпадений в тексте.
int SearchItemsMaker::findInOneText(int *c, QString txt, QString pattern)
{
    int cnt = 0;
    QRegExp rx(pattern);
    if(!checkRegExp(rx)) return 0;
    int pos = 0;
    while((pos = rx.indexIn(txt, pos)) != -1){
        pos += rx.matchedLength();
        *c += 1;
        cnt++;
    }

    return cnt;
}

bool SearchItemsMaker::checkRegExp(QRegExp rx)
{
    if(rx.isValid() && !rx.isEmpty() && !rx.exactMatch("")){
        return true;
    } else {
        return false;
    }
}
