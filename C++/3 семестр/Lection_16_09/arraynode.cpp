#include "arraynode.h"
#include <string>

template <typename T>
ArrayNode<T>::ArrayNode(const T& value) {
    data = value;
    next = nullptr;
}

template class ArrayNode<int>;
template class ArrayNode<double>;
template class ArrayNode<std::string>;
template class ArrayNode<char>;
