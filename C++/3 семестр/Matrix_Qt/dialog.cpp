#include "dialog.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Matrix Settings");
    setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Matrix Size:"));
    sizeSpinBox = new QSpinBox();
    sizeSpinBox->setRange(2, 10);
    sizeSpinBox->setValue(5);
    sizeLayout->addWidget(sizeSpinBox);
    sizeLayout->addStretch();
    mainLayout->addLayout(sizeLayout);

    manualInputCheckBox = new QCheckBox("Manual Input");
    mainLayout->addWidget(manualInputCheckBox);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

bool Dialog::isManualInput() const
{
    return manualInputCheckBox->isChecked();
}

int Dialog::getMatrixSize() const
{
    return sizeSpinBox->value();
}

void Dialog::onAccepted()
{
    emit dialogAccepted(sizeSpinBox->value(), manualInputCheckBox->isChecked());
    accept();
}
