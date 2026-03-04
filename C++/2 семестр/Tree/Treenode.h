#ifndef LISTNODE_H
#define LISTNODE_H

class Tree;
class TreeNode
{
   friend class Tree;

public:
   TreeNode( const   int& );
     int getData() const;
private:
     int data; // data
    TreeNode    *rightPtr;
    TreeNode    *leftPtr;
};

TreeNode   ::TreeNode( const   int&info )
    : data( info ), rightPtr( 0 ), leftPtr( 0 )
{ }

   int TreeNode   ::getData() const
{ 
   return data; 
}

#endif
