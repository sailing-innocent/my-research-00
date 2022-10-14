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
    List();
    List(List<T>& rhs);
    List<T>& operator=(List<T>& rhs);
    ~List();
    std::vector<Node<T>> getNodes();
    bool addNode(Node<T>& node);
private:
    std::vector<Node<T>> nodes;
};

template<typename T>
class Array {
public:
    Array();
    Array(Array<T>& rhs);
    Array<T>& operator=(Array<T>& rhs);
    ~Array();
private:
    std::array<Node<T>, SAIL_ARRAY_MAX> nodes;
};

SAIL_NAMESPACE_END

#endif