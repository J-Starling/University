#ifndef EMAILVALIDATOR_H
#define EMAILVALIDATOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QFile>
#include <QMessageBox>
#include <QSplitter>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFontDialog>

class EmailValidator : public QWidget
{
    Q_OBJECT
public:
    EmailValidator(QWidget *parent = nullptr);
    ~EmailValidator();
private slots:
    void processText();
    void clearText();
    void loadFromFile();
    void saveToFile();
    void showFontDialog();
private:
    QLabel* title;
    QTextEdit* leftText;
    QTextEdit* rightText;
    QPushButton* execute;
    QPushButton* clear;
    QMenuBar* menuBar;
    QMenu* menu;
    QAction* loadAction;
    QAction* saveAction;
    QAction* fontAction;

    QString replaceEmails(const QString&);
    bool isValidEmail(const QString&);
};
#endif
