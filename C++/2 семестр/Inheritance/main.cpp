#include "constant.h"
#include "linear.h"
#include "quadratic.h"
#include <locale.h>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    setlocale(LC_ALL,"PL_pl.UTF-8");
    bool f = false;
    while (!f)
    {
        int choice;
        cout << "Выберите функцию:" << endl;
        cout << "1. Константа" << endl;
        cout << "2. Линейная функция" << endl;
        cout << "3. Квадратичная функция" << endl;
        cout << "4. Выход" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Constant c;
            cin >> c;
            cout << c;
            cout << "Производная:" << endl;
            cout << c.getDerivative();
            break;
        }
        case 2:
        {
            Linear l;
            cin >> l;
            cout << l;
            cout << "Производная:" << endl;
            cout << l.getDerivative();
            break;
        }
        case 3:
        {
            Quadratic q;
            cin >> q;
            cout << q;
            cout << "Производная:" << endl;
            cout << q.getDerivative();
            break;
        }
        case 4:
            f = true;
            break;
        default:
            cout << "Ошибка выбора." << endl;
        }
    }

    return 0;
}
