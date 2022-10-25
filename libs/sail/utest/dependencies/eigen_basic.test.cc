#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

#define MATRIX_SIZE 100

TEST(SAIL_TEST_DEPS, EIGEN_BASIC)
{
    Matrix<float,2,3> matrix_f23;
    Vector3d vec_d3; // same as Matrix<float,3,1> 
    Matrix3d matrix_d33 = Matrix3d::Zero(); // Init as zeros
    // Matrix3d matrix_d33 = Matrix3d::Random();
    // can use dynamic
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;

    // Or simpler
    MatrixXd matrix_x;

    matrix_f23 << 1, 2, 3, 4, 5, 6;
    EXPECT_EQ(matrix_f23(1,2), 6);
}

TEST(SAIL_TEST_DEPS, EIGEN_BASICS_SOLVER)
{
    Matrix3d matrix_d33;
    matrix_d33 << 1, 0, 0, 0, 2, 0, 0, 0, 3;
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_d33.transpose() * matrix_d33);
    Vector3d eigen_values = eigen_solver.eigenvalues();
    Matrix3d eigen_vectors = eigen_solver.eigenvectors();
    // std::cout << "Eigen Values = \n" << eigen_values << std::endl;
    // std::cout << "Eigen Vectors = \n" << eigen_vectors << std::endl;
}

TEST(SAIL_TEST_DEPS, EIGEN_BASICS_EQUATION)
{
    /*
    Matrix2d matrix_d22;
    matrix_d22 << 1, 2, 3, 1;
    Vector2d v_d2;
    v_d2 << 5, 5;
    Vector2d x = matrix_d22.inverse() * v_d2;
    */
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_dNN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_dNN = matrix_dNN.transpose() * matrix_dNN;
    Matrix<double, MATRIX_SIZE, 1> v_dN = MatrixXd::Random(MATRIX_SIZE, 1);

    Matrix<double, MATRIX_SIZE, 1> x = matrix_dNN.inverse() * v_dN;
}

TEST(SAIL_TEST_DEPS, EIGEN_BASICS_QR)
{    
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_dNN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_dNN = matrix_dNN.transpose() * matrix_dNN;
    Matrix<double, MATRIX_SIZE, 1> v_dN = MatrixXd::Random(MATRIX_SIZE, 1);

    Matrix<double, MATRIX_SIZE, 1> x = matrix_dNN.colPivHouseholderQr().solve(v_dN);
}


TEST(SAIL_TEST_DEPS, EIGEN_BASICS_CHOLESKY)
{    
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_dNN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_dNN = matrix_dNN.transpose() * matrix_dNN;
    Matrix<double, MATRIX_SIZE, 1> v_dN = MatrixXd::Random(MATRIX_SIZE, 1);

    Matrix<double, MATRIX_SIZE, 1> x = matrix_dNN.ldlt().solve(v_dN);
}