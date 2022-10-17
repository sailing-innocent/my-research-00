#pragma once
#ifndef HELLO_H_
#define HELLO_H_

#include "sail/common.h"
#include <iostream>
#include <string>

SAIL_NAMESPACE_BEGIN
std::string hello();

template<typename T>
T getT() {
    T some(0);
    return some;
}

SAIL_NAMESPACE_END

#endif
