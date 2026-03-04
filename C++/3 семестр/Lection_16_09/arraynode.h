#ifndef ARRAYNODE_H
#define ARRAYNODE_H

template <typename T>
class Array;

template <typename T>
class ArrayNode {
public:
    friend class Array<T>;
    ArrayNode(const T&);
    ~ArrayNode() {}

private:
    T data;
    ArrayNode<T>* next;
};

#endif
