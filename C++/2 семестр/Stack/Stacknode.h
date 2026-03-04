#ifndef STACKNODE_H
#define STACKNODE_H

class Stack;

class StackNode
{
    friend class Stack;
    friend Stack& operator--(Stack &, int);
    friend Stack& operator+=(Stack &, const Stack &);
public:
    StackNode(const int &);
private:
    int data;
    StackNode *nextPtr;
};

#endif
