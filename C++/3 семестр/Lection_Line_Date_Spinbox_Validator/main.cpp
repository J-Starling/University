#include "human.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Human h;

    h.setWindowTitle("Human");
    h.resize(230, 200);
    h.show();

    return a.exec();
}
