#pragma once
/**
 * @file: include/sail/math/vector.hpp
 * @author: sailing-innocent
 * @create: 2022-10-15
*/

#ifndef SAIL_MATH_VECTOR_H_
#define SAIL_MATH_VECTOR_H_

#include <sail/math.h>
#include <iostream>

SAIL_NAMESPACE_BEGIN

class Vector
{
public:
    Vector();
    Vector(std::vector<double> _vec, int _size);
    Vector(Vector& rhs);
    Vector& operator=(Vector& rhs);
    ~Vector();

    double operator[](int index);
    Vector operator+(const Vector& lhs, const Vector& rhs);
    int operator*(const Vector& lhs, const Vector& rhs); // innerproduct
    ostream& operator<<(ostream& os, Vector& vec);

    int size() { return mSize; }
    Vector& cross(const Vector& rhs);

private:
    int mSize = 0;
    std::vector<double> mValue ={};
};

SAIL_NAMESPACE_END

#endif