#include "quadratic.h"

Quadratic::Quadratic(){quad = 0; linear = 0; constant = 0;}

Quadratic::Quadratic(double quad, double lin, double con) : Linear(lin, con), quad{quad} {}

double Quadratic::getValue(double x) const
{
    return quad*x*x + linear*x + constant;
}

Linear Quadratic::getDerivative() const
{
    return Linear(2*quad, linear);
}

void Quadratic::setValue(double q, double l, double c)
{
    quad = q;
    linear = l;
    constant = c;
}

ostream& operator<<(ostream& output, const Quadratic& c)
{
    double x;
    cout << "Квадратичная функция: y = " << c.quad << "*x^2 + "
         << c.linear << "*x + " << c.constant << endl;
    cout << "Введите x: ";
    cin >> x;
    output << "Значение квадратичной функции в точке " << x << ": y = " << c.getValue(x) << endl;
    return output;
}

istream& operator>>(istream& input, Quadratic& c)
{
    int choice;
    cout << "Как задать квадратичную функцию? (0 - вручную, 1 - рандомно)" << endl;
    do
    {
        input >> choice;
        if((choice != 0) && (choice != 1))
            cout << "Введите 0 или 1: " << endl;
    } while((choice != 0) && (choice != 1));

    switch(choice)
    {
    case 0:
        double a, b, d;
        cout << "Введите коэффициент при x^2: " << endl;
        cin >> a;
        cout << "Введите линейный коэффициент: " << endl;
        cin >> b;
        cout << "Введите свободный член: " << endl;
        cin >> d;
        c.setValue(a,b,d);
        break;

    case 1:
        double e, f, g;
        e = double(rand()) / RAND_MAX * 100;
        f = double(rand()) / RAND_MAX * 100;
        g = double(rand()) / RAND_MAX * 100;
        c.setValue(e,f,g);
        break;
    }
    return input;
}
