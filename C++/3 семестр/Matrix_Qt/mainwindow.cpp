/*Дана матрица. Если она симметрична относительно побочной оси, сформировать матрицу новую матрицу перестановкой столбцов исходной так,
чтобы элементы последней строки были расположены по убыванию, иначе - по возрастанию.*/

#include "mainwindow.h"
#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), currentSize(5), manualInputMode(false)
{
    menuBar = new QMenuBar(this);
    menu = new QMenu("Menu", this);

    dialogAction = new QAction("Settings", this);
    processAction = new QAction("Process Matrix", this);

    menu->addAction(dialogAction);
    menu->addAction(processAction);
    menuBar->addMenu(menu);

    originalTable = new QTableWidget(currentSize, currentSize);
    originalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resultTable = new QTableWidget(currentSize, currentSize);
    resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tabWidget = new QTabWidget(this);
    tabWidget->addTab(originalTable, "Original Matrix");
    tabWidget->addTab(resultTable, "Result Matrix");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    connect(dialogAction, SIGNAL(triggered()), this, SLOT(onDialogAction()));
    connect(processAction, SIGNAL(triggered()), this, SLOT(processMatrix()));

    updateTables();
}

void MainWindow::onDialogAction()
{
    originalTable->clearContents();
    resultTable->clearContents();
    emit requestDialog();
}

void MainWindow::updateTables()
{
    originalTable->setRowCount(currentSize);
    originalTable->setColumnCount(currentSize);
    resultTable->setRowCount(currentSize);
    resultTable->setColumnCount(currentSize);

    setupTableHeaders(originalTable, currentSize, currentSize);
    setupTableHeaders(resultTable, currentSize, currentSize);
}

void MainWindow::setupTableHeaders(QTableWidget *table, int rows, int cols)
{
    QStringList rowHeaders, colHeaders;

    for (int i = 0; i < rows; ++i) {
        rowHeaders << QString("Row %1").arg(i + 1);
    }
    table->setVerticalHeaderLabels(rowHeaders);

    for (int i = 0; i < cols; ++i) {
        colHeaders << QString("Col %1").arg(i + 1);
    }
    table->setHorizontalHeaderLabels(colHeaders);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::fillMatrixManually()
{
    originalTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    QMessageBox::information(this, "Manual Input", "You can now manually edit values in the original matrix table.");
}

void MainWindow::fillMatrixRandomly(double min, double max)
{
    if (min > max) std::swap(min, max);
    originalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QRandomGenerator* generator = QRandomGenerator::global();

    for (int i = 0; i < currentSize; ++i) {
        for (int j = 0; j < currentSize; ++j) {
            double randomValue = min + generator->generateDouble() * (max - min);
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(randomValue, 'f', 2));
            originalTable->setItem(i, j, item);
        }
    }
}

bool MainWindow::isSymmetric() const
{
    for (int i = 0; i < currentSize; ++i) {
        for (int j = 0; j < currentSize - i - 1; ++j) {
            QTableWidgetItem* item1 = originalTable->item(i, j);
            QTableWidgetItem* item2 = originalTable->item(currentSize - j - 1, currentSize - i - 1);

            if (!item1 || !item2) {
                return false;
            }

            double val1 = item1->text().toDouble();
            double val2 = item2->text().toDouble();

            if (qAbs(val1 - val2) > 0.001f) {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::sortColumns(bool ascending)
{
    for (int i = 0; i < currentSize; ++i) {
        for (int j = 0; j < currentSize; ++j) {
            QTableWidgetItem *item = originalTable->item(i, j);
            if (item) {
                QTableWidgetItem *newItem = new QTableWidgetItem(*item);
                resultTable->setItem(i, j, newItem);
            }
        }
    }

    for (int i = 0; i < currentSize - 1; ++i) {
        for (int j = 0; j < currentSize - i - 1; ++j) {
            QTableWidgetItem* item1 = resultTable->item(currentSize - 1, j);
            QTableWidgetItem* item2 = resultTable->item(currentSize - 1, j + 1);

            if (!item1 || !item2) continue;

            double val1 = item1->text().toDouble();
            double val2 = item2->text().toDouble();

            bool shouldSwap = ascending ? (val1 > val2) : (val1 < val2);

            if (shouldSwap) {
                for (int k = 0; k < currentSize; ++k) {
                    QTableWidgetItem *temp = resultTable->takeItem(k, j);
                    resultTable->setItem(k, j, resultTable->takeItem(k, j + 1));
                    resultTable->setItem(k, j + 1, temp);
                }
            }
        }
    }
}

void MainWindow::processMatrix()
{
    for (int i = 0; i < currentSize; ++i) {
        for (int j = 0; j < currentSize; ++j) {
            if (!originalTable->item(i, j)) {
                QMessageBox::warning(this, "Error", "Please fill all matrix cells before processing.");
                return;
            }
        }
    }

    bool symmetric = isSymmetric();

    if (symmetric) {
        sortColumns(false);
    } else {
        sortColumns(true);
    }

    tabWidget->setCurrentIndex(1);

    QString message = symmetric ?
                          "Matrix is symmetric. Columns sorted in descending order based on last row." :
                          "Matrix is not symmetric. Columns sorted in ascending order based on last row.";

    QMessageBox::information(this, "Processing Complete", message);
}

void MainWindow::handleDialogAccepted(int size, bool manualInput)
{
    currentSize = size;
    manualInputMode = manualInput;
    updateTables();

    if (manualInputMode) {
        fillMatrixManually();
    } else {
        showRandomDialog();
    }
}

void MainWindow::showRandomDialog()
{
    emit requestRandomDialog();
}

MainWindow::~MainWindow() {}
