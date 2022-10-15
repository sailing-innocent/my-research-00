#pragma once
#ifndef SAIL_ALGORITHM_NODE_H_
#define SAIL_ALGORITHM_NODE_H_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

template<typename T>
class Node {
public:
    Node(T _content): mContent(_content} {}
    ~Node() {}
    T& content() { return mContent; }
private:
    T mContent;
};

SAIL_NAMESPACE_END

#endif
