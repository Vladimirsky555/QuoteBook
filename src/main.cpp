#include "search/searchwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchWindow w;
    w.showMaximized();

    return a.exec();
}
