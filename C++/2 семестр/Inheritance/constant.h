#ifndef CONSTANT_H
#define CONSTANT_H

#include "function.h"
#include <iostream>

using namespace std;

class Constant : public Function
{
    friend ostream &operator<<(ostream &, const Constant &);
    friend istream &operator>>(istream &, Constant &);
public:
    Constant();
    Constant(double);
    double getValue() const { return constant; };
    Constant getDerivative() const { return Constant(0); };
    void setValue(double);
protected:
    double constant;
};

#endif
