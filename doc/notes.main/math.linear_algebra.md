# Linear Algebra

This note collects the numerical solutions for linear algebra problems

## STL

## boost

## Eigen
//LINK TO DEPLOYMENT

### Matrix
you can just use `MatrixXd m(2,2)` to create a $2 \times 2 $ matrix
Other Tools
- `MatrixXd::Random()` with random values between -1 and 1
- `MatrixXd::Constant(int m, int n, float initValue)` 
- `v << 1,2,3;` comma-initialization in Advanced Intialization

in Eigen, all matrices and vectors are objects of the Matrix template class. Vectors are just special cases of matrices, with either 1 row or 1 column.

`Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime`
`typedef Matrix<float, 4, 4> Matrix4f`
`typedef Matrix<float, 3, 1> Vector3f`
`typedef Matrix<int, 1, 2> RowVector2i`

And we can use Dynamic template to infer nums that will check at compiling time.

A default constructor is always available, never performs any dynamic memory allocation and never initailizes the matrix coefficients.

Resizing: 
the `resize()` method is a no-operation if the actual matrix size doesn't change; otherwise it is destructuive; 

addition and subtraction

binary operator +
binary operator -
unary operator -
compound operator +=
compound operator -=

Scalar Multipulation and division

In Eigen, arithmetic operators suchas operator+ donot performa any compuations by themselves, they just return an "expression object" describing the computation to be performed. The actually computation performed later.

Thus, you should not be afraid of using relatively large expressions.

Transpostion and Conjugation

`a.transpose() // a.conjugate() // a.adjoint()`

for basic arithmetic operators, transpose and adjoint simply return a proxy object without doing the actual transposition. So donot use `a = a.transpose()` to avoid unexpected results. (aliasing issue)

but use transposeInPlace() method

Multiplation /hello/matmani.cc
Dot Product and Cross Product: /hello/dotncross.cc

Reduction Methods: sum prod mean minCoeff maxCoeff trace

### Array
`typedef Array<float,Dynamic,1> ArrayXf`
`typedef Array<float,3,1> Array3f`
`typedef Array<double, Dynamic, Dynamic> ArrayXXd`
`typedef Array<double,3,3> Array33d`

## numpy
