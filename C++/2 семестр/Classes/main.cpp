#include "address.h"
#include "classes.cpp"

void manual(Address *, int);
void random(Address *, int);
void print(Address *, int);

int main() {
    srand(time(NULL));
    setlocale(LC_ALL,"PL_pl.UTF-8");
    int q, n, f;
    do {
        cout<<endl<<"Введите количество адресов:"<<endl;
        cin>>n;


        Address *a = new Address[n];

        cout<<"Введите 0 для ручного ввода, иначе - любое другое число"<<endl;
        cin>>f;

        (f == 0) ? manual(a, n) : random(a, n);

        print(a, n);

        delete[] a;

        cout<<endl<<"Для завершения работы программы введите 0, иначе - любое другое число:"<<endl;
        cin>>q;
    } while (q != 0);
    return 0;
}
