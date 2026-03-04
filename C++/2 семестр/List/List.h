// Fig. 21.4: List.h
// Template List class definition.
#ifndef LIST_H
#define LIST_H

#include <iostream>
using std::cout;

#include "Listnode.h" // ListNode class definition


class List 
{
public:
   List(); // constructor
   ~List(); // destructor
   void insertAtFront( const int& );
   void insertAtBack( const int& );
   bool removeFromFront( int& );
   bool removeFromBack( int& );
   bool isEmpty() const;
   void print() const;
private:
   ListNode *firstPtr;
   ListNode *lastPtr;

   ListNode *getNewNode( const int& );
};

List::List()
   : firstPtr( 0 ), lastPtr( 0 ) 
{ }

List::~List()
{
   if ( !isEmpty() )
   {    
      cout << "Destroying nodes ...\n";

      ListNode *currentPtr = firstPtr;
      ListNode *tempPtr;

      while ( currentPtr != 0 )
      {  
         tempPtr = currentPtr;
         cout << tempPtr->data << '\n';
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      }
   }

   cout << "All nodes destroyed\n\n";
}

void List::insertAtFront( const int&value )
{
   ListNode *newPtr = getNewNode( value ); // new node

   if ( isEmpty() ) // List is empty
      firstPtr = lastPtr = newPtr; // new list has only one node
   else // List is not empty
   {
      newPtr->nextPtr = firstPtr; // point new node to previous 1st node
      firstPtr = newPtr; // aim firstPtr at new node
   } // end else
} // end function insertAtFront

// insert node at back of list
void List::insertAtBack( const int&value )
{
   ListNode *newPtr = getNewNode( value ); // new node

   if ( isEmpty() ) // List is empty
      firstPtr = lastPtr = newPtr; // new list has only one node
   else // List is not empty
   {
      lastPtr->nextPtr = newPtr; // update previous last node
      lastPtr = newPtr; // new last node
   } // end else
} // end function insertAtBack

// delete node from front of list
bool List::removeFromFront( int&value )
{
   if ( isEmpty() ) // List is empty
      return false; // delete unsuccessful
   else 
   {
      ListNode *tempPtr = firstPtr; // hold tempPtr to delete

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0; // no nodes remain after removal
      else
         firstPtr = firstPtr->nextPtr; // point to previous 2nd node

      value = tempPtr->data; // return data being removed
      delete tempPtr; // reclaim previous front node
      return true; // delete successful
   } // end else
} // end function removeFromFront

// delete node from back of list
bool List::removeFromBack( int&value )
{
   if ( isEmpty() ) // List is empty
      return false; // delete unsuccessful
   else 
   {
      ListNode *tempPtr = lastPtr; // hold tempPtr to delete

      if ( firstPtr == lastPtr ) // List has one element
         firstPtr = lastPtr = 0; // no nodes remain after removal
      else 
      {
         ListNode *currentPtr = firstPtr;

         // locate second-to-last element            
         while ( currentPtr->nextPtr != lastPtr )    
            currentPtr = currentPtr->nextPtr; // move to next node

         lastPtr = currentPtr; // remove last node
         currentPtr->nextPtr = 0; // this is now the last node
      } // end else

      value = tempPtr->data; // return value from old last node
      delete tempPtr; // reclaim former last node
      return true; // delete successful
   } // end else
} // end function removeFromBack

// is List empty?
bool List::isEmpty() const
{ 
   return firstPtr == 0; 
} // end function isEmpty

// return pointer to newly allocated node
ListNode *List::getNewNode(
   const int&value )
{
   return new ListNode( value );
} // end function getNewNode

// display contents of List
void List::print() const
{
   if ( isEmpty() ) // List is empty
   {
      cout << "The list is empty\n\n";
      return;
   } // end if

   ListNode *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) // get element data
   {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;
   } // end while

   cout << "\n\n";
} // end function print

#endif
