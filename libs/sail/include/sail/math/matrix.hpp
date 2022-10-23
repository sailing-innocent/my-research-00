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
    Matrix(std::vector<double> value, int _rows, int _cols);
    Matrix(Matrix& rhs);
    Matrix& operator=(Matrix& rhs);
    ~Matrix();

    std::vector<double>& operator[](int index);
    Matrix& operator[](); // mat[][1] to return its 1 st column
    const std::vector<double>& operator[](int index);

    Matrix& opeartor*(const Matrix& lhs, const Matrix& rhs); // mat product
    int n() { return mRows; }
    int m() { return mCols; }

private:
    int mRows = 0;
    int mCols = 0;
    std::vector<double> mValue = {}
};

SAIL_NAMESPACE_END

#endif
