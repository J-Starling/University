#ifndef LINEAR_H
#define LINEAR_H

#include "constant.h"

class Linear : public Constant
{
public:
    Linear();
    Linear(double, double);
    virtual double getValue(double) const;
    virtual Function* getDerivative() const;
    virtual void print(ostream&) const;
    virtual void manualInput(istream&);
    virtual void randomInput();
    virtual void readFromFile(ifstream&);
    virtual void writeToFile(ofstream&) const;
protected:
    double linear;
};

#endif
