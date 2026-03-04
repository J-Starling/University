#include "mainwindow.h"
#include "dialog.h"
#include "randomdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Dialog *dialog = new Dialog();
    RandomDialog *randomDialog = new RandomDialog();

    QObject::connect(&w, SIGNAL(requestDialog()), dialog, SLOT(show()));
    QObject::connect(dialog, SIGNAL(dialogAccepted(int, bool)), &w, SLOT(handleDialogAccepted(int, bool)));

    QObject::connect(&w, SIGNAL(requestRandomDialog()), randomDialog, SLOT(show()));
    QObject::connect(randomDialog, SIGNAL(randomDialogAccepted(double, double)), &w, SLOT(fillMatrixRandomly(double, double)));

    w.show();

    return a.exec();
}
