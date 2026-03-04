#include "human.h"
#include "qlabel.h"

Human::Human(QWidget *parent): QWidget(parent) {
    l = new QLineEdit;
    d = new QDateEdit;
    s = new QSpinBox;
    b = new QPushButton("Check");

    QLabel* s1 = new QLabel("Name:");
    QLabel* s2 = new QLabel("Date:");
    QLabel* s3 = new QLabel("Age:");

    QRegularExpressionValidator* v = new QRegularExpressionValidator(QRegularExpression("^[A-Z][a-zA-Z -]*$"));
    l->setValidator(v);

    d->setDate(QDate::currentDate().addYears(-20));
    d->setMinimumDate(QDate::currentDate().addYears(-150));
    d->setMaximumDate(QDate::currentDate());
    d->setDisplayFormat("dd.MM.yyyy");

    s->setMinimum(1);
    s->setMaximum(150);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(s1);
    layout->addWidget(l);
    layout->addWidget(s2);
    layout->addWidget(d);
    layout->addWidget(s3);
    layout->addWidget(s);
    layout->addWidget(b);
    setLayout(layout);

    QObject::connect(b, SIGNAL(clicked()), this, SLOT(check()));
}

Human::~Human() {}

void Human::check() {
    int age = s->value();
    QDate date = d->date();
    QDate current = QDate::currentDate();
    int year = current.year() - date.year();

    if (date.month() > current.month() || (date.month() == current.month() && date.day() > current.day())) {
        year--;
    }

    if (age == year) {
        QMessageBox m;
        m.setWindowTitle("Match");
        m.setText("Age matches birth date");
        m.exec();
    } else {
        QMessageBox m;
        m.setWindowTitle("Mismatch");
        m.setText("Data mismatch!\n\nEntered age: " + QString::number(age) +"\nCalculated age: " + QString::number(year));
        m.exec();
    }
}
