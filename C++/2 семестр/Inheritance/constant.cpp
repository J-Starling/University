#include "constant.h"

Constant::Constant(){constant = 0;}

Constant::Constant(double n){constant = n;}

void Constant::setValue(double n){constant = n;}

ostream &operator<<(ostream &output, const Constant& c){
    output << "Значение константы: y = " << c.constant << endl;
    return output;
}

istream &operator>>(istream &input, Constant& c){
    int choice;
    cout << "Как задать константу? (0 - вручную, 1 - рандомно)" << endl;
    do
    {
        input >> choice;
        if ((choice != 0) && (choice != 1))
            cout << "Введите 0 или 1: " << endl;

    } while ((choice != 0) && (choice != 1));

    switch (choice)
    {
    case 0:
        double d;
        cout << "Введите константу: " << endl;
        cin >> d;
        c.setValue(d);
        break;

    case 1:
        c.setValue(double(rand())/RAND_MAX*100);
        break;
    }

    return input;
}
