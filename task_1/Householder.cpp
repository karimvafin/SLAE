#include "sem_1/src/project/dense/densematrix.hpp"
#include "project/utility/overloads.hpp"
#include <project/utility/Norm.hpp>
#include <cmath>

template<typename T>
std::pair<DenseMatrix < T>, DenseMatrix <T>> QR_decomposition_Householder(const DenseMatrix <T> &A) {
    int n = A.get_size()
    vector <vector<T>> n(n);
    vector <T> x_i(n);
    vector <T> n_i(n);
    vector <T> e_i(n, 0);

    for (int i = 0; i < n; ++i) {
        x_i = A.column(i);
        e_i[i] = 1;
        n_i = x_i[i] / abs(x[i] * norm(x_i, NormType::ThirdNorm)) * e_i + x_i;
        //if(){}else{}
    }
}