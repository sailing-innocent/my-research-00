# Eigen Source Learning

Eigen 库源码学习，估计是一个漫长的过程，计划用时一年时间

We can start with the testing part to get an insight of how API is running.

in test/array_of_string.cpp, it only include main.h

## Index

Eigen/Engin include Dense include Sparse
Eigen/Dense include Core LU Cholesky QR SVD Geometry Eigenvalues
Eigen/Core

## array_of_string
- Dep: main.h
- Use: `Array<std::string,1,Dynamic> ArrayXs`
---> src/core/Array.h

### main.h

some debugging and testing tools

### src/core/Array.h

The Array class is very similat to the Matrix class, It provides general-purpose one- and two- dimentional arrays. The difference is mainly the API, array coefficient-wise operations and matrix more linear algebra

412行，大量用模板，看不太懂
