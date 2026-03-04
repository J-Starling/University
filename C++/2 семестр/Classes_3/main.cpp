#include "address.h"
#include "developer.h"

#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    setlocale(LC_ALL,"PL_pl.UTF-8");
    char q = 'N';
    int f;

    do{
        Developer dev;
        cin >> dev;
        cout << dev << endl;

        cout << "Выберите метод сортировки адресов по номеру квартиры: " << endl;
        cout << "1 - Быстрая сортировка" << endl;
        cout << "2 - Шейкерная сортировка" << endl;
        cout << "0 - Без сортировки" << endl << endl;

        cin >> f;
        if (f == 1) {
            dev.QuickSort(0, dev.getCount()-1);
        } else if (f == 2) {
            dev.ShakerSort();
        }

        cout << "Отсортированные адреса: " << endl << endl;
        cout << dev << endl;

        dev.increase();
        dev.add();

        cout << "Хотите повторить? (Y/N): ";
        cin >> q;
        cin.ignore();
    }while (q == 'y' || q == 'Y');

    return 0;
}
