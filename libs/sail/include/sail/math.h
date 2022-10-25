#pragma once
/**
 * @file: include/sail/math.h
 * @author: sailing-innocent
 * @desp: The Math Header Library
 * @create: 2022-10-15
*/

// originally I will use double for most precisions

#ifndef SAIL_MATH_H_
#define SAIL_MATH_H_

#include <sail/common.h>
#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>


SAIL_NAMESPACE_BEGIN

#define MAX_ARRAY_BUFSZ 10000

enum SDataType {
    INT = 1;
    DOUBLE = 2;
    UINT8 = 3;
}

SAIL_NAMESPACE_END

#include <sail/math/vector.hpp>

#endif // SAIL_MATH_H