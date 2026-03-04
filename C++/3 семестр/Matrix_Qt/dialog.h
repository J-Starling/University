#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QSpinBox;
class QCheckBox;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);

    bool isManualInput() const;
    int getMatrixSize() const;

signals:
    void dialogAccepted(int size, bool manualInput);

private slots:
    void onAccepted();

private:
    QSpinBox *sizeSpinBox;
    QCheckBox *manualInputCheckBox;
};

#endif
