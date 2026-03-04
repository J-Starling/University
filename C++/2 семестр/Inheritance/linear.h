#ifndef LINEAR_H
#define LINEAR_H

#include "constant.h"
#include <iostream>

using namespace std;

class Linear : public Constant
{
    friend ostream &operator<<(ostream &, const Linear &);
    friend istream &operator>>(istream &, Linear &);
public:
    Linear();
    Linear(double linear, double constant);
    double getValue(double) const;
    Constant getDerivative() const;
    void setValue(double, double);
protected:
    double linear;
};

#endif
