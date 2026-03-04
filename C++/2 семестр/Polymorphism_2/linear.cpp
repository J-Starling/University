#include "linear.h"

Linear::Linear(): Constant(), linear(0) {}

Linear::Linear(double n, double m): Constant(m), linear(n) {}

double Linear::getValue(double x) const
{
    return linear * x + constant;
}

Function* Linear::getDerivative() const
{
    return new Constant(linear);
}

void Linear::print(ostream& out) const
{
    out << "Линейная функция: y = " << linear << " * x + " << constant << "\n";
}

void Linear::manualInput(istream& input)
{
    cout << "Введите линейный коэффициент:\n";
    input >> linear;
    Constant::manualInput(input);
}

void Linear::randomInput()
{
    linear = (double)rand() / RAND_MAX * 100.0;
    Constant::randomInput();
}

void Linear::readFromFile(ifstream &file)
{
    file >> linear;
    Constant::readFromFile(file);
}

void Linear::writeToFile(ofstream &file) const
{
    file << *this << endl;
    file << "Производная:" << endl;
    file << *getDerivative() << endl;
}
