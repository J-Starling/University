#include "events.h"

Events::Events(QWidget* pwgt) : QLabel(pwgt)
{
    setAlignment(Qt::AlignCenter);
    setText("Mouse interactions or resize events\n(Press a mouse button or resize the window)");
    flag = false;
}

void Events::mousePressEvent(QMouseEvent* pe)
{
    dumpEvent(pe, "Mouse Pressed");
}

void Events::mouseReleaseEvent(QMouseEvent* pe)
{
    dumpEvent(pe, "Mouse Released");
}

void Events::mouseMoveEvent(QMouseEvent* pe)
{
    dumpEvent(pe, "Mouse Is Moving");
}

void Events::resizeEvent(QResizeEvent* pe)
{
    if (!flag){
        flag = true;
    } else setText(QString("Resized") + "\n width()=" + QString::number(pe->size().width()) + "\n height()=" + QString::number(pe->size().height()));
}

void Events::dumpEvent(QMouseEvent* pe, const QString& strMsg)
{
    setText(strMsg
            + "\n buttons()=" + buttonsInfo(pe)
            + "\n x()=" + QString::number(pe->x())
            + "\n y()=" + QString::number(pe->y())
            + "\n globalX()=" + QString::number(pe->globalX())
            + "\n globalY()=" + QString::number(pe->globalY())
            + "\n modifiers()=" + modifiersInfo(pe)
            );
}

QString Events::modifiersInfo(QMouseEvent* pe)
{
    QString strModifiers;

    if(pe->modifiers() & Qt::ShiftModifier) {
        strModifiers += "Shift ";
    }

    if(pe->modifiers() & Qt::ControlModifier) {
        strModifiers += "Control ";
    }

    if(pe->modifiers() & Qt::AltModifier) {
        strModifiers += "Alt";
    }

    return strModifiers;
}

QString Events::buttonsInfo(QMouseEvent* pe)
{
    QString strButtons;

    if(pe->buttons() & Qt::LeftButton) {
        strButtons += "Left ";
    }

    if(pe->buttons() & Qt::RightButton) {
        strButtons += "Right ";
    }

    if(pe->buttons() & Qt::MiddleButton) {
        strButtons += "Middle";
    }

    return strButtons;
}
