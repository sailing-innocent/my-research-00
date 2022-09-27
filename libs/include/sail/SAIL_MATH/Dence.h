#include <sail/common>

SAIL_NAMESPACE_BEGIN

class MatrixXd {    
public:
    MatrixXd();
    ~MatrixXd();
    MatrixXd& Random(int m, int n);
    MatrixXd& Constant();
    MatrixXd& operator+(MatrixXd& a, MatrixXd& b);
    MatrixXd& operator*(MatrixXd& a, MatrixXd& b);
}; // CLASS MatrixXd END

class VectorXd {
public:
    VectorXd();
    ~VectorXd();
    instream& operator<<(int a);
    VectorXd& operator*(MatrixXd& A, VectorXd& x);
}


SAIL_NAMESPACE_END
