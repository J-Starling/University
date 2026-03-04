#include "events.h"
#include "qapplication.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Events w;
    w.resize(250, 130);
    w.show();
    return app.exec();
}
