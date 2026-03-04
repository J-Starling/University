#ifndef EVENTS_H
#define EVENTS_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>

class Events : public QLabel {
public:
    Events(QWidget* pwgt = 0);
protected:
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent(QMouseEvent* pe);
    virtual void resizeEvent(QResizeEvent* pe);

    void dumpEvent(QMouseEvent* pe, const QString& strMessage);
    QString modifiersInfo(QMouseEvent* pe);
    QString buttonsInfo(QMouseEvent* pe);
    bool flag;
};

#endif
