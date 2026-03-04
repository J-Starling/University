#ifndef TABLES_H
#define TABLES_H

#include <QWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QLayout>
#include <QLabel>
#include <QTabWidget>
#include <QRandomGenerator>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGroupBox>

class tables : public QWidget
{
    Q_OBJECT

public:
    tables(QWidget *parent = nullptr);
    ~tables();

private slots:
    void onDimensionChanged(int index);

private:
    void updateTables();
    void setupTableHeaders(QTableWidget *table, int size);
    QString getColumnName(int index);

    QTabWidget *tab;
    QTableWidget *t1;
    QTableWidget *t2;
    QComboBox *dim;
    int currentDimension;
};
#endif
