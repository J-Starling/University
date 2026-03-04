#include "quadratic.h"
#include <locale.h>

int main()
{
    srand((unsigned int)time(nullptr));
    setlocale(LC_ALL, "PL_pl.UTF-8");
    bool f = false;
    while (!f)
    {
        int choice, n;
        cout << "Выберите функцию:" << endl << "1. Константа" << endl << "2. Линейная функция" << endl << "3. Квадратичная функция" << endl << "4. Выход" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Constant c;
            cout << "Ввести вручную (0) или случайно (1)?" << endl;
            cin >> n;
            if (n == 0) cin >> c;
            else c.randomInput();
            cout << c;
            auto derivative = c.getDerivative();
            cout << "Производная: " << endl << (*derivative) << endl;
            break;
        }
        case 2:
        {
            Linear l;
            cout << "Ввести вручную (0) или случайно (1)?" << endl;
            cin >> n;
            if (n == 0) cin >> l;
            else l.randomInput();
            cout << l;
            auto derivative = l.getDerivative();
            cout << "Производная: " << endl << (*derivative) << endl;
            break;
        }
        case 3:
        {
            Quadratic q;
            cout << "Ввести вручную (0) или случайно (1)?" << endl;
            cin >> n;
            if (n == 0) cin >> q;
            else q.randomInput();
            cout << q;
            auto derivative = q.getDerivative();
            cout << "Производная: " << endl << (*derivative) << endl;
            break;
        }
        case 4:
            f = true;
            break;
        default:
            cout << "Ошибка выбора" << endl;
        }
    }
    return 0;
}
