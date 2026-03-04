#include "Stack.h"
#include <iostream>

using namespace std;

Stack::Stack()
{
    firstPtr = nullptr;
    lastPtr = nullptr;
}

Stack::~Stack()
{
    if (!isEmpty())
    {
        StackNode *currentPtr = firstPtr;
        StackNode *tempPtr;
        while (currentPtr != nullptr)
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
    }
}

// Бурлакова Дарья:

bool Stack::isEmpty() const
{
    return firstPtr == 0;
}

bool Stack::isStackEmpty() const
{
    if (isEmpty()) {cout << "Стек пуст" << endl;}
    return isEmpty();
}

void Stack::copyStack(const Stack &b)
{
    if(!b.isStackEmpty())
    {
        cout << "Копирование стека" << endl;
        StackNode *currentB = b.firstPtr;
        StackNode *previousA = nullptr;
        while(currentB != nullptr)
        {
            StackNode *newNode = new StackNode(currentB->data);
            if(previousA == nullptr)
            {
                firstPtr = newNode;
            }
            else
            {
                previousA->nextPtr = newNode;
            }
            previousA = newNode;
            currentB = currentB->nextPtr;
        }
        lastPtr = previousA;
    }
}

// Немчинова Анастасия:

void Stack::printStack() const
{
    if (!isStackEmpty())
    {
        StackNode *currentPtr = firstPtr;
        cout << "Стек: ";
        while (currentPtr != nullptr)
        {
            cout << currentPtr->data << ' ';
            currentPtr = currentPtr->nextPtr;
        }
        cout << endl << endl;
    }
}

void Stack::removeStack()
{
    if (!isStackEmpty())
    {
        StackNode *currentPtr = firstPtr;
        StackNode *tempPtr;
        while(currentPtr != nullptr)
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
        firstPtr = lastPtr = nullptr;
        cout << "Стек убран" << endl;
    }
}

// Шубин Григорий:

int Stack::lengthOfStack() const
{
    int count = 0;
    StackNode *currentPtr = firstPtr;
    while (currentPtr != nullptr)
    {
        count++;
        currentPtr = currentPtr->nextPtr;
    }
    return count;
}

void Stack::stateOfStack() const
{
    if (!isStackEmpty())
        cout << "Длина стека: " << lengthOfStack() << ", вершина стека: " << firstPtr->data << endl;
}

// Захарова Елизавета:

Stack& operator--(Stack &stack, int)
{
    if (!stack.isStackEmpty())
    {
        StackNode *currentPtr = stack.firstPtr;
        while (currentPtr != nullptr)
        {
            currentPtr->data--;
            currentPtr = currentPtr->nextPtr;
        }
    }
    return stack;
}

Stack& operator+=(Stack &a, const Stack &b)
{
    StackNode* currA = a.firstPtr;
    StackNode* currB = b.firstPtr;

    while(currA != nullptr && currB != nullptr)
    {
        currA->data += currB->data;
        currA = currA->nextPtr;
        currB = currB->nextPtr;
    }
    return a;
}

// Попов Всеволод:

StackNode *Stack::getNewNode(const int &value)
{
    return new StackNode(value);
}

void Stack::insertAtFront(const int &value)
{
    StackNode *newPtr = getNewNode(value);
    if (isEmpty())
        firstPtr = lastPtr = newPtr;
    else
    {
        newPtr->nextPtr = firstPtr;
        firstPtr = newPtr;
    }
}

void Stack::insertAfter(const int &value)
{
    if (!isEmpty())
    {
        StackNode *newNode = getNewNode(value);
        newNode->nextPtr = firstPtr->nextPtr;
        firstPtr->nextPtr = newNode;
        if (lastPtr == firstPtr)
            lastPtr = newNode;
        }
    else insertAtFront(value);

}

// Кирюхина Виктория:

void Stack::deleteDoppelgangers()
{
    if (!isStackEmpty())
    {
        StackNode *current = firstPtr;
        StackNode *innerCurrent;
        StackNode *prevInner;
        while (current != nullptr)
        {
            int val = current->data;
            innerCurrent = current->nextPtr;
            prevInner = current;
            while (innerCurrent != nullptr)
            {
                if (val == innerCurrent->data)
                {
                    prevInner->nextPtr = innerCurrent->nextPtr;
                    delete innerCurrent;
                    innerCurrent = prevInner->nextPtr;
                }
                else
                {
                    prevInner = innerCurrent;
                    innerCurrent = innerCurrent->nextPtr;
                }
            }
            current = current->nextPtr;
        }
    }
}

void Stack::removeElement()
{
    if (isStackEmpty())
        cout << "Нельзя убрать элемент из пустого стека" << endl;
    else
    {
        StackNode *tempPtr = firstPtr;
        if ( firstPtr == lastPtr )
            firstPtr = lastPtr = nullptr;
        else
            firstPtr = firstPtr->nextPtr;
        cout << "Будет убран элемент: " << tempPtr->data << endl;
        delete tempPtr;
    }
}

// Журавлёв Арсений:

void Stack::changeElement(const int & a, const int & b)
{
    if (isStackEmpty())
        cout << "Нельзя поменять элемент в пустом стеке" << endl;
    else
    {
        StackNode *currentPtr = firstPtr;
        int f = 0;
        while (currentPtr != nullptr)
        {
            if (currentPtr->data == a)
            {
                currentPtr->data = b;
                f = 1;
                break;
            }
            currentPtr = currentPtr->nextPtr;
        }
        if (f == 0)
            cout << "Элемент не найден в стеке" << endl;
    }
}

void Stack::deleteElement(const int &value)
{
    if (!isStackEmpty())
    {
        StackNode *current = firstPtr;
        StackNode *prev = nullptr;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (prev == nullptr)
                {
                    firstPtr = current->nextPtr;
                    if (firstPtr == nullptr)
                        lastPtr = nullptr;
                }
                else
                {
                    prev->nextPtr = current->nextPtr;
                    if (current == lastPtr)
                        lastPtr = prev;
                }

                delete current;
                cout << "Элемент удалён" << endl;
                return;
            }
            prev = current;
            current = current->nextPtr;
        }
        cout << "Элемент не найден в стеке" << endl;
    }
}

// Аксёнов Дмитрий:

void Stack::invertStack()
{
    if (!isStackEmpty())
    {
        StackNode *prev = nullptr;
        StackNode *current = firstPtr;
        StackNode *next = nullptr;
        while (current != nullptr)
        {
            next = current->nextPtr;
            current->nextPtr = prev;
            prev = current;
            current = next;
        }
        firstPtr = prev;
        lastPtr = nullptr;
    }
}

void Stack::mergeStack(const Stack &b)
{
    if (b.isEmpty())
    {
        cout << "Второй стек пуст" << endl;
    }
    else
    {
        StackNode *PtrB = b.firstPtr;
        while (PtrB != nullptr)
        {
            insertAtFront(PtrB->data);
            PtrB = PtrB->nextPtr;
        }
    }
}

void Stack::sortStack()
{
    if (!isStackEmpty())
    {
        cout << "Сортировать стек по убыванию или возрастанию? (0 - по убыванию, 1 - по возрастанию)" << endl;
        int choice;
        cin >> choice;
        StackNode* start = firstPtr;
        while(start != nullptr)
        {
            StackNode* bestNode = start;
            StackNode* current = start->nextPtr;
            while(current != nullptr)
            {
                if ((choice == 1 && current->data < bestNode->data) || (choice == 0 && current->data > bestNode->data))
                {
                    bestNode = current;
                }
                current = current->nextPtr;
            }
            swap(bestNode->data, start->data);
            start = start->nextPtr;
        }
    }
}
