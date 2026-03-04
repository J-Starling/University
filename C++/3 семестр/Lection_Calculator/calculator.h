#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QGridLayout>
#include <QPushButton>
#include <QRegularExpression>

class QLCDNumber;
class QPushButton;

class Calculator : public QWidget {
    Q_OBJECT
private:
    QLCDNumber* m_plcd;
    QStack<QString> m_stk;
    QString m_strDisplay;

public:
    Calculator(QWidget* pwqt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();

public slots:
    void slotButtonClicked();
};
