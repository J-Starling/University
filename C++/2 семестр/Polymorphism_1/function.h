#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

using namespace std;

class Function
{
    friend ostream& operator<<(ostream&, const Function&);
    friend istream& operator>>(istream&, Function&);
public:
    virtual double getValue(double) const = 0;
    virtual Function* getDerivative() const = 0;
    virtual void print(ostream&) const = 0;
    virtual void manualInput(istream&) = 0;
    virtual void randomInput() = 0;
};

#endif
