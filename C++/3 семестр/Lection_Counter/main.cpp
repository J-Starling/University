#include <QDebug>
#include "counter.h"
#include "qapplication.h"
#include "qlabel.h"
#include "qpushbutton.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel label("0");
    QPushButton cmd("Add");
    Counter counter;

    label.show();
    cmd.show();

    QObject::connect(&cmd, SIGNAL(clicked()), &counter, SLOT(slotInc()));
    QObject::connect(&counter, SIGNAL(changeValue(int)), &label, SLOT(setNum(int)));
    QObject::connect(&counter, SIGNAL(goodbye()), &app, SLOT(quit()));

    qDebug() << "Class name: " << Qt::endl << counter.metaObject()->className();
    qDebug() << "Parent: " << Qt::endl << counter.parent();

    return app.exec();
}
