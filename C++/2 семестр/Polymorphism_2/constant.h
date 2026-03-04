#ifndef CONSTANT_H
#define CONSTANT_H

#include "function.h"

class Constant : public Function
{
public:
    Constant();
    Constant(double);
    virtual double getValue(double) const;
    virtual Function* getDerivative() const;
    virtual void print(ostream&) const;
    virtual void manualInput(istream&);
    virtual void randomInput();
    virtual void readFromFile(ifstream&);
    virtual void writeToFile(ofstream&) const;
protected:
    double constant;
};

#endif
