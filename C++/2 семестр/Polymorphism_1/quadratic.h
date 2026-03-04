#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "linear.h"

class Quadratic : public Linear
{
public:
    Quadratic();
    Quadratic(double, double, double);
    virtual double getValue(double) const;
    virtual Function* getDerivative() const;
    virtual void print(ostream&) const;
    virtual void manualInput(istream&);
    virtual void randomInput();
private:
    double quadratic;
};

#endif
