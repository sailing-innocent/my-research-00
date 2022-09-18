# eigen library

- main page: https://eigen.tuxfamily.org/
- doc page: [Eigen: Main Page](https://eigen.tuxfamily.org/dox/)

eigen is a header-only template library. So we don't need to compile before using it. The CMakeLists.txt system in source code is just used for documentation and test cases.

尝试编译了一下，电脑直接崩了。果然还是配置太低了wwww。

使用eigen的方法比想象中容易得多。

新建一个空文件夹，照例写歌test.cc

```cpp
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

int main() 
{
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
    return 0;
}
```

并新建一个CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.18)
project(eigenTest)
include_directories("../../dependencies/eigen")
add_executable(test01 test.cc)

```

然后惯例编译运行，就可以了

## Quick Reference Guide

The Eigen Library is divided in a Core module and several additional modules. Each module has a corresponding header file which has to be included in order to see the module.

- Core: #include<Eigen/Core> Matrix and Array classes, basic linear algebra (including triangular and selfadjoint products), array manipulation
- Geometry: #include <Eigen/Geometry> Transform, Translation, Scaling, Rotation2D and 3D rotations (Quaternion, AngleAxis)
- LU: #include <Eigen/LU> Inverse, determinant, LU decompositions with solvers ( FullPivLU, PartialPivLU)
- Cholesky: #include <Eigen/Cholesky> LLT and LDLT Cholesky factorization with solver
- Householder: #include <Eigen/Householder> Householder transformations
- SVD: #include <Eigen/SVD> SVD decomposition with solver (JacobiSVD, BDVSVD)
- QR: #include <Eigen/QR> QR decomposition with solver (HouseholderQR, ColPivHouseholderQR, FullPivHouseholderQR)
- EigenValues: #include <Eigen/Eigenvalues> EigenSolver SelfAdjointEigenSolver ComplexEigenSolver
- Sparse: #include <Eigen/Sparse> SparseMatrix SparseVector Quick
- Dense: #include <Eigen/Dense> Core Geometry LU Cholesky SVD QR EigenValues header file （except for Sparse)
- Eigen: All of Above

Array & Matrix

```cc
MatrixXf: Matrix<float, Dynamic, Dynamic>
VectorXd: Matrix<double, Dynamic>
RowVectorXi: Matrix<int, 1, Dynamic>
Matrix3f: Matrix<float,3,3>
Vector4f: Matrix<float,4,1>
ArrayXXf: Array<float, Dynamic, Dynamic>
ArrayXd: Array<double, Dynamic, 1>
RowArrayXi: Array<int,1,Dynamic>
Array33f: Array<float, 3, 3> 
Array4f: Array<float,4,1>

```

Runtime Info
