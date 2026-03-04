#include "randomdialog.h"
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

RandomDialog::RandomDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Random Values Range");
    setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *minLayout = new QHBoxLayout();
    minLayout->addWidget(new QLabel("Min Value:"));
    minSpinBox = new QSpinBox();
    minSpinBox->setRange(-100, 100);
    minSpinBox->setValue(0);
    minLayout->addWidget(minSpinBox);
    minLayout->addStretch();
    mainLayout->addLayout(minLayout);

    QHBoxLayout *maxLayout = new QHBoxLayout();
    maxLayout->addWidget(new QLabel("Max Value:"));
    maxSpinBox = new QSpinBox();
    maxSpinBox->setRange(-100, 100);
    maxSpinBox->setValue(100);
    maxLayout->addWidget(maxSpinBox);
    maxLayout->addStretch();
    mainLayout->addLayout(maxLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void RandomDialog::setMinValue(double value)
{
    minSpinBox->setValue(static_cast<int>(value));
}

void RandomDialog::setMaxValue(double value)
{
    maxSpinBox->setValue(static_cast<int>(value));
}

void RandomDialog::onAccepted()
{
    emit randomDialogAccepted(minSpinBox->value(), maxSpinBox->value());
    accept();
}
