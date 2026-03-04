#include <iostream>
using std::cout;
using std::endl;

#include "Queue.h"

int main()
{
    Queue intQueue;

    cout << "processing an integer Queue" << endl;

    for ( int i = 0; i < 5; i++ )
    {
        intQueue.enqueue( i );
        intQueue.printQueue();
    }

    int dequeueInteger;

    while ( !intQueue.isQueueEmpty() )
    {
        intQueue.dequeue( dequeueInteger );
        cout << dequeueInteger << " dequeued from queue" << endl;
        intQueue.printQueue();
    }

    return 0;
}

