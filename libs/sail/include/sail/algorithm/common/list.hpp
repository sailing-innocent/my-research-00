#pragma once
/**
 * FILE:include/sail/algorith/list.hpp
 * AUTHOR:sailing-innocent
 * CREATE:2022-10-15
 * DESP: the template linked list library for SAIL
 * DONE: //TODO: Finish SALI linked list library
*/

#ifndef SAIL_ALGORITHM_LIST_T_
#define SAIL_ALGORITHM_LIST_T_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

template <typename T>
class ListNode: public Node<T>
{
public:
    ListNode() {}
    ListNode(T _content): Node(_content) {}
    const ListNode<T>& prev() const { return *mpPrev; }
    const ListNode<T>& next() const { return *mpNext; }
    bool setPrev(ListNode<T>& _prev) { mpPrev = &_prev; return true; }
    bool setNext(ListNode<T>& _next) { mpNext = &_next; return true; }
protected:
    ListNode<T>* mpPrev = nullptr;
    ListNode<T>* mpNext = nullptr;
};

template <typename T>
class LinkList: public Node<std::vector<ListNode<T>>>
{
public:
    LinkList() = default;
    LinkList(std::vector<ListNode<T>>& vec)
    {
        setContent(vec);
    }
    bool setContent(std::vector<ListNode<T>>& vec);
};

template<typename T>
bool LinkList<T>::setContent(std::vector<ListNode<T>>& vec) {
    size_t len = vec.size();
    mContent.resize(len);
    std::cout << "constructing linklist of size " << len << std::endl;
    if (len < 2) { 
        return true; 
    }
    for (auto i = 0; i < len; i++) {
        mContent[i].setContent(vec[i].content());
    }
    for (auto i = 0; i < len; i++) {
        if ( i == 0 ) {
            mContent[i].setNext(mContent[i+1]);
        } else if ( i == len-1 ) {
            mContent[i].setPrev(mContent[i-1]);
        } else {
            mContent[i].setNext(mContent[i+1]);
            mContent[i].setPrev(mContent[i-1]);
        }
    }
    return true;
}

SAIL_NAMESPACE_END

#endif // SAIL_ALGORITHM_LIST_T_
