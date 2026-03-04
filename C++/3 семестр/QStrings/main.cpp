#include "emailvalidator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmailValidator validator;

    validator.resize(800, 500);
    validator.show();

    return app.exec();
}
