#pragma once
#ifndef SAIL_ALGORITHM
#define SAIL_ALGORITHM

#include <vector>
#include "common.h"

SAIL_NAMESPACE_BEGIN

template<typename T>
class Node {
public:
    Node(T _val): value{_val} {}
    ~Node() {}
    T content() { return value; }
private:
    T value;
};

template<typename T>
class List {
public:
    List() {}
    ~List() {}
private:
    std::vector<Node<T>> nodes;
};


SAIL_NAMESPACE_END

#endif