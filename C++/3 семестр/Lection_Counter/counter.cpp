#include "counter.h"

Counter::Counter(): QObject(), value(0) {}

void Counter::slotInc()
{
    emit changeValue(++value);

    if (value == 5)
    {
        emit goodbye();
    }
}
