#ifndef TABLES_H
#define TABLES_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QTableWidget>
#include <QTabWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void requestRandomDialog();
    void requestDialog();

public slots:
    void updateTables();
    void processMatrix();
    void fillMatrixRandomly(double min, double max);
    void handleDialogAccepted(int size, bool manualInput);
    void showRandomDialog();

private slots:
    void onDialogAction();

private:
    void setupTableHeaders(QTableWidget *table, int rows, int cols);
    void fillMatrixManually();
    bool isSymmetric() const;
    void sortColumns(bool ascending);

    QMenu *menu;
    QMenuBar *menuBar;
    QAction *dialogAction;
    QAction *processAction;
    QTableWidget *originalTable;
    QTableWidget *resultTable;
    QTabWidget *tabWidget;
    int currentSize;
    bool manualInputMode;
};

#endif
