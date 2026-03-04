#ifndef RANDOMDIALOG_H
#define RANDOMDIALOG_H

#include <QDialog>

class QSpinBox;

class RandomDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RandomDialog(QWidget *parent = nullptr);

    void setMinValue(double value);
    void setMaxValue(double value);

signals:
    void randomDialogAccepted(double min, double max);

private slots:
    void onAccepted();

private:
    QSpinBox *minSpinBox;
    QSpinBox *maxSpinBox;
};

#endif
