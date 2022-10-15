#pragma once
#ifndef SAIL_ALGORITHM_NODE_H_
#define SAIL_ALGORITHM_NODE_H_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

template<typename T>
class Node {
public:
    Node(T _val): value{_val} {}
    ~Node() {}
    T& content() { return value; }
private:
    T value;
};

SAIL_NAMESPACE_END

#endif
