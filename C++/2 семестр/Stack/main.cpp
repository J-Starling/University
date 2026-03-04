#include "Stack.h"
#include <locale.h>
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL,"PL_pl.UTF-8");
    Stack stack1, stack2;
    int choice = 0;
    int num;
    while(choice != 18){
    {
        cout << "\n\nМеню операций:\n";
        cout << "1. Проверка на пустоту\n";
        cout << "2. Удалить дублирующиеся элементы\n";
        cout << "3. Скопировать один стек в другой\n";
        cout << "4. Добавить элемент в начало стека\n";
        cout << "5. Добавить элемент после вершины\n";
        cout << "6. Изменить элемент в стеке\n";
        cout << "7. Удалить конкретный элемент\n";
        cout << "8. Извлечь верхний элемент и показать его\n";
        cout << "9. Очистить стек\n";
        cout << "10. Получить длину стека\n";
        cout << "11. Отсортировать стек\n";
        cout << "12. Вывести содержимое стека\n";
        cout << "13. Инвертировать порядок элементов в стеке\n";
        cout << "14. Объединить два стека (+=)\n";
        cout << "15. Слить два стека (объединить)\n";
        cout << "16. Показать текущее состояние стека (длина и вершина)\n";
        cout << "17. Применить декремент ко всему стеку\n";
        cout << "18. Выход\n";

        cout << "Выберите операцию: ";
        cin >> choice;

        switch(choice)
        {
        case 1: // проверка на пустоту
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.isStackEmpty();
            else stack2.isStackEmpty();
            break;

        case 2: // удаление повторяющихся элементов
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if(num == 1) stack1.deleteDoppelgangers();
            else stack2.deleteDoppelgangers();
            break;

        case 3: // копирование одного стека в другой
            cout << "Копировать первый стек во второй - 0; второй стек в первый - 1" << endl;
            cin >> num;
            if (num == 0) stack2.copyStack(stack1);
            else stack1.copyStack(stack2);
            break;

        case 4: // вставка элемента в начало стека
            cout << "Введите элемент для вставки в начало стека: ";
            int val;
            cin >> val;
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if(num == 1) stack1.insertAtFront(val);
            else stack2.insertAtFront(val);
            break;

        case 5: // вставка элемента после вершины
            cout << "Введите элемент для вставки после вершины: ";
            cin >> val;
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if(num == 1) stack1.insertAfter(val);
            else stack2.insertAfter(val);
            break;

        case 6: // замена значения элемента
            cout << "Введите старое значение: ";
            int oldVal;
            cin >> oldVal;
            cout << "Введите новое значение: ";
            int newVal;
            cin >> newVal;
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.changeElement(oldVal, newVal);
            else stack2.changeElement(oldVal, newVal);
            break;

        case 7: // удаление конкретного элемента
            cout << "Введите значение для удаления: ";
            cin >> val;
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.deleteElement(val);
            else stack2.deleteElement(val);
            break;

        case 8: // убрать верхний элемент
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.removeElement();
            else stack2.removeElement();
            break;

        case 9: // очистка стека
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.removeStack();
            else stack2.removeStack();
            break;

        case 10: // получение длины стека
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) cout << "Длина стека №1: " << stack1.lengthOfStack() << endl;
            else cout << "Длина стека №2: " << stack2.lengthOfStack() << endl;
            break;

        case 11: // сортировка стека
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.sortStack();
            else stack2.sortStack();
            break;

        case 12: // вывод содержимого стека
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.printStack();
            else stack2.printStack();
            break;

        case 13: // инверсия порядка элементов
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if (num == 1) stack1.invertStack();
            else stack2.invertStack();
            break;

        case 14: // сложение двух стеков
            cout << "Прибавить первый стек ко второму - 0; прибавить второй стек к первому - 1" << endl;
            cin >> num;
            if (num == 1) stack1 += stack2;
            else stack2 += stack1;
            break;

        case 15: // слияние двух стеков
            cout << "Слить первый стек со вторым - 0; слить второй стек с первым - 1" << endl;
            cin >> num;
            if (num == 0) stack1.mergeStack(stack2);
            else stack2.mergeStack(stack1);
            break;

        case 16: // текущее состояние стека
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if(num == 1) stack1.stateOfStack();
            else stack2.stateOfStack();
            break;

        case 17: // применить декремент ко всему стеку
            cout << "Укажите номер стека (1/2): ";
            cin >> num;
            if(num == 1) stack1--;
            else stack2--;
            break;

        case 18:
            break;

        default:
            cout << "Ошибка выбора команды. Повторите ввод." << endl;
        }
    }
    }
    return 0;
}
