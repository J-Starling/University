#include "function.h"

Function::Function() {}

double Function::getValue(double x) const
{
    return 1;
}

Function Function::getDerivative() const
{
    return Function();
}

ostream& operator<<(ostream& output, const Function& function)
{
    return output;
}

istream& operator>>(istream& input, Function& function)
{
    return input;
}
