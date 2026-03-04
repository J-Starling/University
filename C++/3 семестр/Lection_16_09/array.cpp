#include "array.h"
#include <stdexcept>

template <typename T>
Array<T>::Array() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    capacity = 5;
    totalArraysCreated++;
}

template <typename T>
Array<T>::Array(int a) {
    head = nullptr;
    tail = nullptr;
    size = 0;
    capacity = a;
    totalArraysCreated++;
}

template <typename T>
void Array<T>::clear() {
    ArrayNode<T>* current = head;
    while (current != nullptr) {
        ArrayNode<T>* next = current->next;
        delete current;
        current = next;
        totalElements--;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
Array<T>::~Array() {
    clear();
}

template <typename T>
Array<T>::Array(const Array<T>& other) {
    head = nullptr;
    tail = nullptr;
    size = 0;
    capacity = other.capacity;
    ArrayNode<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
    totalArraysCreated++;
}

template <typename T>
int Array<T>::getSize() const {
    return size;
}

template <typename T>
int Array<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void Array<T>::resize(int newCapacity) {
    if (newCapacity < size) {
        throw std::invalid_argument("New capacity cannot be less than current size");
    }
    capacity = newCapacity;
}

template <typename T>
void Array<T>::push_back(const T& value) {
    ArrayNode<T>* newNode = new ArrayNode<T>(value);

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
    totalElements++;

    if (size >= capacity) {
        resize(capacity + 1);
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        clear();
        capacity = other.capacity;
        ArrayNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    ArrayNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

template <typename T>
int Array<T>::getTotalArraysCreated() {
    return totalArraysCreated;
}

template <typename T>
int Array<T>::getTotalElements() {
    return totalElements;
}

template class Array<int>;
template class Array<double>;
template class Array<std::string>;
template class Array<char>;
