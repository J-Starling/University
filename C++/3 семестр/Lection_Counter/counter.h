#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
public:
    Counter();
private:
    int value;
public slots:
    void slotInc();
signals:
    void goodbye();
    void changeValue(int);
};

#endif
