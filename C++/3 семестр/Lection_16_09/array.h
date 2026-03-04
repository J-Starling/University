#ifndef ARRAY_H
#define ARRAY_H

#include "arraynode.h"

template <typename T>
class Array {
public:
    Array();
    Array(int);
    Array(const Array<T>&);
    ~Array();

    void clear();
    int getSize() const;
    int getCapacity() const;
    void push_back(const T&);
    void resize(int);

    Array<T>& operator=(const Array<T>&);
    const T& operator[](int) const;

    static int getTotalArraysCreated();
    static int getTotalElements();

private:
    ArrayNode<T>* head;
    ArrayNode<T>* tail;
    int size;
    int capacity;

    static int totalArraysCreated;
    static int totalElements;
};

template <typename T>
int Array<T>::totalArraysCreated = 0;

template <typename T>
int Array<T>::totalElements = 0;

#endif
