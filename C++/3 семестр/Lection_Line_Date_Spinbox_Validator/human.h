#ifndef HUMAN_H
#define HUMAN_H

#include <QMessageBox>
#include <QDateEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>

class Human : public QWidget
{
    Q_OBJECT
public:
    Human(QWidget *parent = nullptr);
    ~Human();
private:
    QLineEdit* l;
    QSpinBox* s;
    QPushButton* b;
    QDateEdit* d;
public slots:
    void check();
};
#endif
