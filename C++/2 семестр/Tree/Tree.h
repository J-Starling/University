#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>
using std::cout;

#include "Treenode.h"


class Tree
{
public:
    Tree();
    void insertNode( const int& );
    void preOrder () const;
    void postOrder () const;
    void inOrder () const;
private:
    TreeNode *rootPtr;
    void insertNodeHelper( TreeNode **, const int& );
    void preOrderHelper (TreeNode *) const;
    void postOrderHelper (TreeNode *) const;
    void inOrderHelper (TreeNode *) const;
};

Tree::Tree()
    : rootPtr( 0 )
{ }

void Tree::insertNode( const int&value )
{
    insertNodeHelper( &rootPtr, value);
}

void Tree::insertNodeHelper (TreeNode **ptr, const int &value){
    if (*ptr == 0) {
        *ptr = new TreeNode (value);
        assert (*ptr != 0);
    }
    else
        if (value < (*ptr)->data)
        insertNodeHelper( & ((*ptr) ->leftPtr), value);
    else
        if (value> (*ptr)->data)
        insertNodeHelper (& ((*ptr)->rightPtr), value);
    else
        cout << value << "дубль" << std::endl;
}

void Tree::preOrder () const
{ preOrderHelper (rootPtr); }

void Tree::preOrderHelper (TreeNode *ptr) const
{
    if (ptr != 0) {
        cout << ptr->data << ' ';
        preOrderHelper (ptr->leftPtr);
        preOrderHelper (ptr->rightPtr);
    }
}

void Tree::postOrder () const
{ postOrderHelper (rootPtr); }

void Tree::postOrderHelper (TreeNode *ptr) const
{
    if (ptr != 0) {
        postOrderHelper (ptr->leftPtr);
        postOrderHelper (ptr->rightPtr);
        cout << ptr->data << ' ';
    }
}

void Tree::inOrder () const
{ inOrderHelper (rootPtr); }

void Tree::inOrderHelper (TreeNode *ptr) const
{
    if (ptr != 0) {
        inOrderHelper (ptr->leftPtr);
        cout << ptr->data << ' ';
        inOrderHelper (ptr->rightPtr);
    }
}

#endif

