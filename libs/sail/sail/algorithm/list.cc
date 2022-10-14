#include "sail/algorithm.h"

SAIL_NAMESPACE_BEGIN

template<typename T>
List<T>::List() {
    nodes = [];
}

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
std::vector<Node<T>> List<T>::getNodes() {
    return nodes;
}

template<typename T>
bool addNode(Node<T>& node) {
    nodes.push_back(node);
    return true;
}

SAIL_NAMESPACE_END
