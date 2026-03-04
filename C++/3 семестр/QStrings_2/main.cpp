#include "emailvalidator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmailValidator validator;

    validator.show();

    return app.exec();
}
