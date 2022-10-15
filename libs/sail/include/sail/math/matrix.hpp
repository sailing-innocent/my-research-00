#pragma once
/**
 * @file：include/sail/math/matrix.hpp
 * @author: sailing-innocent
 * @create: 2022-10-15
*/

#ifndef SAIL_MATH_MATRIX_H_
#define SAIL_MATH_MATRIX_H_

#include <sail/math.h>
#include <iostream>

SAIL_NAMESPACE_BEGIN


// an n \times m double matrix
class Matrix {
public:
    Matrix();
    Matrix(std::vector<std::vector<double>> _mat, int _n, int _m);
    Matrix(Matrix& rhs);
    Matrix& operator=(Matrix& rhs);
    ~Vector();

    Vector& operator[](int index); // return the ith rows
    // How can i implement [][2] ?
    Matrix& opeartor*(const Matrix& lhs, const Matrix& rhs); // mat product
    int n() { return mRows; }
    int m() { return mCols; }

private:
    int n = 0;
    int m = 0;
    std::vector<std::vector<double>> mValue = {}
};

// TODO: Mat_C: the complex expansion // maybe in complex lib

SAIL_NAMESPACE_END

#endif
