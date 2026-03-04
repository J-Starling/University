#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

using namespace std;

class Function
{
    friend ostream& operator<<(ostream&, const Function&);
    friend istream& operator>>(istream&, Function&);
public:
    Function();
    double getValue(double) const;
    Function getDerivative() const;
};

#endif
