#ifndef GIVENS_HPP
#define GIVENS_HPP

#include "project/utility/overloads.hpp"
#include "project/dense/densematrix.hpp"
#include <cmath>
#include <iostream>

#define tolerance 10e-15

template<typename T>
std::pair<DenseMatrix<T>, DenseMatrix<T>> GivensRotation(DenseMatrix<T>& A)
{
    DenseMatrix<T> Q = DenseMatrix<T>::unit_matrix(A.get_row_size());
    DenseMatrix<T> R(A);

    T sin, cos;
    T upper, lower;
    T tmp;
    T delta;

    for (size_t step = 0; step < R.get_col_size(); ++step)
    {
        for (size_t i = step + 1; i < R.get_row_size(); ++i)
        {
            delta = std::sqrt(R(step, step) * R(step, step) + R(i, step) * R(i, step));
            cos = R(step, step) / delta;
            sin = -R(i, step) / delta;

            for (size_t j = 0; j < Q.get_col_size(); ++j)
            {
                tmp = Q(step, j);
                Q(step, j) = cos * Q(step, j) - sin * Q(i, j);
                Q(i, j) = sin * tmp + cos * Q(i, j);
            }

            for (size_t j = step; j < R.get_col_size(); ++j)
            {
                tmp = R(step, j);
                R(step, j) = cos * R(step, j) - sin * R(i, j);
                R(i, j) = sin * tmp + cos * R(i, j);
                //if (std::abs(R(i, j)) < 1.5e-16) R(i, j) = 0;
            }
        }
    }

    for (size_t i = 0; i < Q.get_row_size(); ++i)
    {
        for (size_t j = i; j < Q.get_col_size(); ++j)
        {
            tmp = Q(i, j);
            Q(i, j) = Q(j, i);
            Q(j, i) = tmp;
        }
    }

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, R);
    return QR;
}

#endif //GIVENS_HPP