#pragma once
#ifndef SAIL_ALGORITHM_NODE_H_
#define SAIL_ALGORITHM_NODE_H_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

template <typename T>
class Node {
public:
    Node() = default;
    Node(T _content): mContent(_content) {}
    const Node<T>& operator=(const Node<T>& rhs) {
        this->mContent = rhs.content();
        return *this;
    }
    const T& content() const { return mContent; }
    bool setContent(const T& _content) { mContent = _content; return true; }
protected:
    T mContent;
};

SAIL_NAMESPACE_END

#endif
