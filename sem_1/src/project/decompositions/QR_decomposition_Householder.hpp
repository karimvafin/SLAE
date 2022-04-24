//
// Created by Карим Вафин on 06.04.2022.
//

#ifndef MY_PROJECT_QR_DECOMPOSITION_HOUSEHOLDER_HPP
#define MY_PROJECT_QR_DECOMPOSITION_HOUSEHOLDER_HPP

#include "project/dense/densematrix.hpp"
#include "project/utility/overloads.hpp"
#include <project/utility/Norm.hpp>
#include "project/utility/operations.hpp"
#include <cmath>

int kronecker(int i, int j)
{
    if( i != j) return 0;
    else return 1;
}

template<typename T>
std::pair<DenseMatrix <T>, DenseMatrix <T>> QR_decomposition_Householder(const DenseMatrix<T> &A)
{
    int m = A.get_row_size();
    int n = A.get_col_size();

    T alpha;
    T beta;
    std::vector<T> x_i(m);                // i column of matrix A m x n
    std::vector<T> n_i;
    DenseMatrix<T> R(A);                  // result matrix R m x n
    DenseMatrix<T> Q(m, m, 0);            // result matrix Q m x m

    for (int i = 0; i < m; i++) Q(i, i) = 1;

    for (int i = 0; i < n; ++i)
    {
        x_i = R.get_col(i);

        for (int k = 0; k < i; k++) x_i.erase(x_i.begin());

        n_i = x_i;
        if (!compare_double(abs(x_i[0]), 0))
            n_i[0] += x_i[0] / abs(x_i[0]) * norm(x_i, NormType::ThirdNorm);
        else
            n_i[0] += norm(x_i, NormType::ThirdNorm);

        // Q_i * R
        alpha = 2. / (n_i * n_i);
        for (int j = i; j < n; j++)
        {
            beta = 0;
            for (int k = i; k < m; k++)
                beta += R(k, j) * n_i[k - i];
            for (int k = i; k < m; k++)
                R(k, j) = R(k, j) - alpha * beta * n_i[k - i];
        }

        // Q_i * Q
        for (int j = 0; j < m; j++)
        {
            beta = 0;
            for (int k = i; k < m; k++)
                beta += Q(k, j) * n_i[k - i];
            for (int k = i; k < m; k++)
                Q(k, j) = Q(k, j) - alpha * beta * n_i[k - i];
        }
    }

    T tmp;
    for (int i = 0; i < m; ++i)
        for (int j = i; j < m; ++j)
        {
            tmp = Q(i, j);
            Q(i, j) = Q(j, i);
            Q(j, i) = tmp;
        }

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, R);
    return QR;
}

#endif //MY_PROJECT_QR_DECOMPOSITION_HOUSEHOLDER_HPP
