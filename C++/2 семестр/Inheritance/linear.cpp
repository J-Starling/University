#include "linear.h"

Linear::Linear(){linear = 1; constant = 0;}

Linear::Linear(double linear, double constant) : Constant(constant), linear{ linear } {}

double Linear::getValue(double x) const
{
    return linear * x + constant;
}

Constant Linear::getDerivative() const
{
    return Constant(linear);
}

void Linear::setValue(double n, double m)
{
    linear = n;
    constant = m;
}

ostream& operator<<(ostream& output, const Linear& c)
{
    double x;
    cout << "Вид линейной функции: y = " << c.linear << "*x + " << c.constant << endl;
    cout << "Введите x: ";
    cin >> x;
    output << "Значение линейной функции в точке " << x << ": y = " << c.getValue(x) << endl;
    return output;
}

istream& operator>>(istream& input, Linear& c)
{
    int choice;
    cout << "Как задать линейную функцию? (0 - вручную, 1 - рандомно)" << endl;
    do
    {
        input >> choice;
        if ((choice != 0) && (choice != 1))
            cout << "Введите 0 или 1: " << endl;

    } while ((choice != 0) && (choice != 1));

    switch (choice)
    {
    case 0:
        double a, b;
        cout << "Введите линейный коэффициент: " << endl;
        cin >> a;
        cout << "Введите свободный член: " << endl;
        cin >> b;
        c.setValue(a, b);
        break;

    case 1:
        double d, e;
        d = double(rand())/RAND_MAX*100;
        e = double(rand())/RAND_MAX*100;
        c.setValue(d, e);
        break;
    }

    return input;
}
