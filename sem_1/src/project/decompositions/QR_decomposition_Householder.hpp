//
// Created by Карим Вафин on 06.04.2022.
//

#ifndef MY_PROJECT_QR_DECOMPOSITION_HOUSEHOLDER_HPP
#define MY_PROJECT_QR_DECOMPOSITION_HOUSEHOLDER_HPP

#include "project/dense/densematrix.hpp"
#include "project/utility/overloads.hpp"
#include <project/utility/Norm.hpp>
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

    T Q_ks;
    T x_i_norm;                           // surface vector
    std::vector<T> x_i(m);                // i column of matrix A
    std::vector<T> e_i(m, 0);             // basis vector
    DenseMatrix<T> R(A);                  // result matrix R
    DenseMatrix<T> Q(m, m, 0);            // result matrix Q
    DenseMatrix<T> R_next(m, n, 0);       // tmp matrix for multiplication
    DenseMatrix<T> Q_next(m, m, 0);       // tmp matrix for multiplication

    for (int i = 0; i < m; i++) Q(i, i) = 1;

    for (int i = 0; i < n; ++i)
    {
        x_i = R.get_col(i);

        for (int k = 0; k < i; k++) x_i.erase(x_i.begin());

        e_i[0] = static_cast<T>(1.);
        x_i = x_i[0] / abs(x_i[0]) * norm(x_i, NormType::ThirdNorm) * e_i + x_i;

        // multiplication Q_i * A and Q_i * Q
        for (int j = 0; j < m; j++)
            for (int k = i; k < m; k++)
            {
                R_next(k, j) = 0;
                Q_next(k, j) = 0;
                for (int s = 0; s < m - i; s++)
                {
                    Q_ks = kronecker(k - i, s) - 2. * x_i[k - i] * x_i[s] / (x_i * x_i);
                    if (j >= i && j < n) R_next(k, j) += Q_ks * R(s + i, j);
                    Q_next(k, j) += Q_ks * Q(s + i, j);
                }
            }

        for (int j = 0; j < m; j++)
            for (int k = i; k < m; k++)
            {
                if (j >= i && j < n) R(k, j) = R_next(k, j);
                Q(k, j) = Q_next(k, j);
            }

        e_i.erase(e_i.begin());
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
