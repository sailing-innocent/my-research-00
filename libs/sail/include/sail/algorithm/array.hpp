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
    int getSize(){return mSize;}
    Node<T>& operator[](int index) {return mNodes[index];}
private:
    int mSize = 0;
    std::array<Node<T>, SAIL_ARRAY_MAX> mNodes;
};

template<typename T>
Array<T>::Array() {}

template<typename T>
Array<T>::Array(sail::Node<T>* pNodes, int countNodes)
{
    for (auto i = 0; i < countNodes; i++) {
        mNodes[i] = *(pNodes+i);
        mSize++;
    }
}

template<typename T>
Array<T>::Array(sail::Array<T>& rhs) {
    int sz = rhs.getSize();
    for (auto i = 0; i < sz; i++) {
        mNodes[i] = rhs[i];
    }
    mSize = sz;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>& rhs)
{
    int sz = rhs.getSize();
    for (auto i = 0; i < sz; i++) {
        mNodes[i] = rhs[i];
    }
    mSize = sz;
}

template<typename T>
Array<T>::~Array() {}


SAIL_NAMESPACE_END

#endif