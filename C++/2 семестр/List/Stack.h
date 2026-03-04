#ifndef STACK_H
#define STACK_H

#include "List.h"


class Stack : private List
{
public:

   void push( const    int &data )
   { 
      insertAtFront( data ); 
   }

   bool pop(    int &data )
   { 
      return removeFromFront( data ); 
   }

   bool isStackEmpty() const
   { 
      return isEmpty(); 
   }

   void printStack() const 
   { 
      print(); 
   }
};

#endif
