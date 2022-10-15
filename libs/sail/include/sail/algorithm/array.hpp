#pragma once
#ifndef SAIL_ALGORITHM_ARRAY_H_
#define SAIL_ALGORITHM_ARRAY_H_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

template<typename T>
class Array {
public:
    Array();
    Array(sail::Node<T>* pNodes, int countNodes);
    Array(Array<T>& rhs);
    Array<T>& operator=(Array<T>& rhs);
    ~Array();
    int getSize(){return size;}
    Node<T>& operator[](int index) {return nodes[index];}
private:
    int size = 0;
    std::array<Node<T>, SAIL_ARRAY_MAX> nodes;
};

template<typename T>
Array<T>::Array() {}

template<typename T>
Array<T>::Array(sail::Node<T>* pNodes, int countNodes)
{
    for (auto i = 0; i < countNodes; i++) {
        nodes[i] = *(pNodes+i);
        size++;
    }
}

template<typename T>
Array<T>::Array(sail::Array<T>& rhs) {
    int sz = rhs.getSize();
    for (auto i = 0; i < sz; i++) {
        nodes[i] = rhs[i];
    }
    size = sz;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>& rhs)
{
    int sz = rhs.getSize();
    for (auto i = 0; i < sz; i++) {
        nodes[i] = rhs[i];
    }
    size = sz;
}

template<typename T>
Array<T>::~Array() {}


SAIL_NAMESPACE_END

#endif