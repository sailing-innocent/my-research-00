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

template<typename T>
class ListNode : public Node<T>{
public:
    ListNode():Node<T>() {} ;
    ListNode(ListNode<T>& rhs):Node<T>(rhs) { setNext(rhs.getNet()); setPrev(rhs.getPrev()); }
    ListNode(T _val): Node<T>(_val) {}
    ListNode<T>& operator=(ListNode<T>& rhs);
    ~ListNode() {};
    ListNode<T>& getNext() { return next; }
    ListNode<T>& getPrev() { return prev; }
    bool setNext(ListNode<T>& node ) { next = node; return true; }
    bool setPrev(ListNode<T>& node ) { prev = node; return true; }
private:
    ListNode<T>& prev();
    ListNode<T>& next();
};

template<typename T>
ListNode<T>& operator=(ListNode<T>& rhs) 
{ 
    content = rhs.content(); 
    setNext(rhs.getNet()); 
    setPrev(rhs.getPrev()); 
    return *this; 
}


/*
template<typename T>
class List {
public:
    List();
    List(List<T>& rhs);
    List<T>& operator=(List<T>& rhs);
    ~List();
    std::vector<sail::Node<T>> getNodes() { return nodes; };
    bool addNode(sail::Node<T>& node);
    int getSize() { return size; }
    Node<T>& operator[](int index) { return nodes[i]; }
private:
    int size = 0;
    ListNode<T>& head();
    std::vector<sail::Node<T>> nodes = {};
};

template<typename T>
List<T>::List() {}

template<typename T>
bool List<T>::addNode(sail::Node<T>& node) {
    nodes.push_back(node);
    size++;
    return true;
}

template<typename T>
List<T>::List(List<T>& rhs) {
    for (auto item: rhs.getNodes()) {
        addNode(item);
    }
}

template<typename T>
List<T>& List<T>::operator=(List<T>& rhs) {
    List lst<T>(rhs);
    return lst;
}

template<typename T>
List<T>::~List(){}

*/

SAIL_NAMESPACE_END

#endif
