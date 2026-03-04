#ifndef STACK_H
#define STACK_H

#include "Stacknode.h"

class Stack
{
    friend Stack& operator--(Stack &, int);
    friend Stack& operator+=(Stack &, const Stack &);
public:
    Stack();
    ~Stack();
    bool isStackEmpty() const;
    void copyStack(const Stack &);
    void printStack() const;
    void removeStack();
    int lengthOfStack() const;
    void stateOfStack() const;
    void insertAtFront(const int &);
    void insertAfter(const int &);
    void removeElement();
    void deleteElement(const int &);
    void deleteDoppelgangers();
    void changeElement(const int &, const int &);
    void invertStack();
    void mergeStack(const Stack &);
    void sortStack();
private:
    StackNode *firstPtr;
    StackNode *lastPtr;
    StackNode *getNewNode(const int &);
    bool isEmpty() const;
};

#endif
