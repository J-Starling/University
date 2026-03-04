#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "linear.h"

class Quadratic : public Linear
{
    friend ostream &operator<<(ostream &, const Quadratic &);
    friend istream &operator>>(istream &, Quadratic &);
public:
    Quadratic();
    Quadratic(double quad, double lin, double con);
    double getValue(double) const;
    Linear getDerivative() const;
    void setValue(double, double, double);
protected:
    double quad;
};

#endif
