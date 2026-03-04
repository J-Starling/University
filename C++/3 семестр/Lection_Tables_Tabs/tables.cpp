#include "tables.h"

tables::tables(QWidget *parent) : QWidget(parent), currentDimension(5)
{
    dim = new QComboBox(this);
    dim->addItem("3x3", 3);
    dim->addItem("4x4", 4);
    dim->addItem("5x5", 5);
    dim->addItem("6x6", 6);
    dim->addItem("7x7", 7);
    dim->addItem("8x8", 8);
    dim->setCurrentIndex(2);

    QLabel *dimensionLabel = new QLabel("Matrix dimension:", this);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(dimensionLabel);
    controlLayout->addWidget(dim);

    QGroupBox *controlGroup = new QGroupBox("Settings", this);
    controlGroup->setLayout(controlLayout);

    t1 = new QTableWidget(currentDimension, currentDimension);
    t2 = new QTableWidget(currentDimension, currentDimension);
    tab = new QTabWidget(this);

    tab->addTab(t1, QPixmap("matrix.jpg"), "Matrix");
    tab->addTab(t2, QPixmap("t_matrix.jpg"), "Transposed Matrix");

    updateTables();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(controlGroup);
    mainLayout->addWidget(tab);
    setLayout(mainLayout);

    connect(dim, SIGNAL(currentIndexChanged(int)), this, SLOT(onDimensionChanged(int)));
}

void tables::onDimensionChanged(int index)
{
    currentDimension = dim->itemData(index).toInt();
    updateTables();
}

void tables::updateTables()
{
    t1->setRowCount(currentDimension);
    t1->setColumnCount(currentDimension);
    t2->setRowCount(currentDimension);
    t2->setColumnCount(currentDimension);

    setupTableHeaders(t1, currentDimension);
    setupTableHeaders(t2, currentDimension);

    QRandomGenerator* gen = QRandomGenerator::global();
    QTableWidgetItem *t = nullptr;

    for (int i = 0; i < currentDimension; ++i) {
        for (int j = 0; j < currentDimension; ++j) {
            int randomValue = gen->bounded(100);

            t = new QTableWidgetItem(QString::number(randomValue));
            t1->setItem(i, j, t);

            t = new QTableWidgetItem(QString::number(randomValue));
            t2->setItem(j, i, t);
        }
    }
}

void tables::setupTableHeaders(QTableWidget *table, int size)
{
    QStringList headers;
    for (int i = 0; i < size; ++i) {
        headers << QString(QChar('A' + i));
    }
    table->setHorizontalHeaderLabels(headers);
    table->setVerticalHeaderLabels(headers);
}

tables::~tables() {}
