// Fig. 21.3: Listnode.h
// Template ListNode class definition.
#ifndef LISTNODE_H
#define LISTNODE_H

// forward declaration of class List required to announce that class 
// List exists so it can be used in the friend declaration at line 13
class List;
class ListNode 
{
   friend class List; // make List a friend

public:
   ListNode( const   int& ); // constructor
     int getData() const; // return data in node
private:
     int data; // data
   ListNode    *nextPtr; // next node in list
}; // end class ListNode

// constructor
ListNode   ::ListNode( const   int&info )
   : data( info ), nextPtr( 0 ) 
{ 
   // empty body
} // end ListNode constructor

// return copy of data in node
   int ListNode   ::getData() const
{ 
   return data; 
} // end function getData

#endif
