#include "quadratic.h"
#include <locale.h>
#include <fstream>

int main()
{
    srand((unsigned int)time(nullptr));
    setlocale(LC_ALL, "PL_pl.UTF-8");
    bool flag = false;
    while (!flag)
    {
        int choice;
        cout << "Меню:" << endl << "1.Выбрать функцию" << endl << "2.Ввести функцию из файла" << endl << "3.Записать функцию в файл" << endl << "4.Выход" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
        {
            int fChoice, iChoice;
            cout << "Выберите функцию:" << endl << "1.Константа" << endl << "2.Линейная функция" << endl << "3.Квадратичная функция" << endl;
            cin >> fChoice;
            Function* f = nullptr;
            switch(fChoice)
            {
            case 1:
                f = new Constant();
                break;
            case 2:
                f = new Linear();
                break;
            case 3:
                f = new Quadratic();
                break;
            default:
                cerr << "Неверный выбор" << endl;;
                continue;
            }
            cout << "Ввод вручную (0) или случайный ввод (1)?" << endl;
            cin >> iChoice;
            if(iChoice == 0)
                cin >> *(f);
            else
                f->randomInput();
            cout << *f << endl;
            auto derivative = f->getDerivative();
            cout << "Производная: " << endl << (*derivative) << endl;
            break;
        }
        case 2:
        {
            ifstream infile("a.txt");
            string type;
            infile >> type;
            Function* f = nullptr;
            if(type == "Константа")
                f = new Constant();
            else if(type == "Линейная")
                f = new Linear();
            else if(type == "Квадратичная")
                f = new Quadratic();
            else
            {
                cerr << "Неправильный тип функции в файле" << endl;
                break;
            }
            f->readFromFile(infile);
            infile.close();
            cout << *f << endl;
            auto derivative = f->getDerivative();
            cout << "Производная: " << endl << (*derivative) << endl;
            break;
        }
        case 3:
        {
            ofstream outfile("b.txt");
            int fChoice, iChoice;
            cout << "Выберите функцию:" << endl << "1.Константа" << endl << "2.Линейная функция" << endl << "3.Квадратичная функция" << endl;
            cin >> fChoice;
            Function* f = nullptr;
            switch(fChoice)
            {
            case 1:
                f = new Constant();
                break;
            case 2:
                f = new Linear();
                break;
            case 3:
                f = new Quadratic();
                break;
            default:
                cerr << "Неверный выбор" << endl;
                continue;
            }
            cout << "Ввод вручную (0) или случайный ввод (1)?" << endl;
            cin >> iChoice;
            if(iChoice == 0)
                cin >> *(f);
            else
                f->randomInput();
            f->writeToFile(outfile);
            outfile.close();
            cout << "Данные успешно сохранены в файл" << endl;
            break;
        }
        case 4:
            flag = true;
            break;
        default:
            cout << "Ошибка выбора." << endl;
        }
    }
    return 0;
}
