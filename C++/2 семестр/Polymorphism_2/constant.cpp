#include "constant.h"

Constant::Constant(): Function(), constant(0) {}

Constant::Constant(double a): Function(), constant(a) {}

double Constant::getValue(double x) const
{
    return constant;
}

Function* Constant::getDerivative() const
{
    return new Constant(0);
}

void Constant::print(ostream& output) const
{
    output << "Константа: y = " << constant << endl;
}

void Constant::manualInput(istream& input)
{
    cout << "Введите значение константы:\n";
    input >> constant;
}

void Constant::randomInput()
{
    constant = (double)rand() / RAND_MAX * 100.0;
}

void Constant::readFromFile(ifstream &file)
{
    file >> constant;
}

void Constant::writeToFile(ofstream &file) const
{
    file << *this << endl;
    file << "Производная:" << endl;
    file << *getDerivative() << endl;
}
