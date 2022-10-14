#pragma once
#ifndef SAIL_ALGORITHM_LIST_T_
#define SAIL_ALGORITHM_LIST_T_

#include <sail/algorithm.h>

SAIL_NAMESPACE_BEGIN

template<typename T>
class List {
public:
    List();
    List(List<T>& rhs);
    List<T>& operator=(List<T>& rhs);
    ~List();
    std::vector<sail::Node<T>> getNodes();
    bool addNode(sail::Node<T>& node);
private:
    std::vector<sail::Node<T>> nodes;
};

template<typename T>
List<T>::List() {}

template<typename T>
List<T>::List(List<T>& rhs) {
    // Copy Constructor
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

template<typename T>
std::vector<sail::Node<T>> List<T>::getNodes() {
    return nodes;
}

template<typename T>
bool List<T>::addNode(sail::Node<T>& node) {
    nodes.push_back(node);
    return true;
}

SAIL_NAMESPACE_END

#endif