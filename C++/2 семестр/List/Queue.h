#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"

class Queue : private List
{
public:

    void enqueue( const    int &data )
    {
        insertAtBack( data );
    }

    bool dequeue(    int &data )
    {
        return removeFromFront( data );
    }

    bool isQueueEmpty() const
    {
        return isEmpty();
    }

    void printQueue() const
    {
        print();
    }
};

#endif // QUEUE_H
