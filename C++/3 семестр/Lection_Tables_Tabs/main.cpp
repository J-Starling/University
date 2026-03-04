#include "tables.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tables w;
    w.resize(900,400);
    w.show();
    return a.exec();
}
