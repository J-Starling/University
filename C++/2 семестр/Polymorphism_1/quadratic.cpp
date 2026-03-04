#include "quadratic.h"

Quadratic::Quadratic(): Linear(0, 0), quadratic(0) {}

Quadratic::Quadratic(double n, double m, double k): Linear(m, k), quadratic(n) {}

double Quadratic::getValue(double x) const
{
    return quadratic * x * x + linear * x + constant;
}

Function* Quadratic::getDerivative() const
{
    return new Linear(2*quadratic, linear);
}

void Quadratic::print(ostream& out) const
{
    out << "Квадратичная функция: y = " << quadratic << " * x^2 + " << linear << " * x + " << constant << "\n";
}

void Quadratic::manualInput(istream& input)
{
    cout << "Введите квадратичный коэффициент:\n";
    input >> quadratic;
    Linear::manualInput(input);
}

void Quadratic::randomInput()
{
    quadratic = (double)rand() / RAND_MAX * 100.0;
    Linear::randomInput();
}
