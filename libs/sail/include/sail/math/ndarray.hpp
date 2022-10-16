#pragma once
/**
 * @file: include/sail/math/ndarray.hpp
 * @author: sailing-innocent
 * @create: 2022-10-16
 * @desp: the header file for n-dimension array similiar to those in numpy
*/

#ifndef SAIL_MATH_NDARRAY_H_
#define SAIL_MATH_NDARRAY_H_

#include <sail/math.h>

SAIL_NAMESPACE_BEGIN

class NDArray {
public:
    NDArray() {}
    int ndim() { return mNDim; }
    std::vector<int> { return mShape; }
    int size() { return mSize; }
    const char* dtype() { return mDType; }
    const int itemsize() { return mItemSize; }
    std::vector<uint8_t>& data() { return buffer;};
private:
    int mNDim;
    std::vector<int> mShape;
    int mSize;
    char* mDType = "";
    int mItemSize;
    std::vector<uint8_t> buffer;
};

SAIL_NAMESPACE_END

#endif // SAIL_MATH_NDARRAY_H_

