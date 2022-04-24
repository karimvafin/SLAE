//
// Created by Карим Вафин on 11.03.2022.
//

#ifndef MY_PROJECT_QR_DECOMPOSITION_GRAM_SCHMIDT_HPP
#define MY_PROJECT_QR_DECOMPOSITION_GRAM_SCHMIDT_HPP

#include "project/dense/densematrix.hpp"
#include "project/utility/Norm.hpp"
#include "project/utility/overloads.hpp"

template <typename T>
std::pair<DenseMatrix<T>, DenseMatrix<T>> QR_decomposition_Gram_Schmidt(const DenseMatrix<T> &A)
{
    // orthogonalization
    DenseMatrix<T> Q(A.get_row_size(), A.get_row_size(), 0);
    DenseMatrix<T> R(A.get_row_size(), A.get_col_size(), 0);

    T norm_;
    T coef;
    std::vector<T> sum(A.get_row_size(), 0);
    std::vector<T> e_j;
    for (int i = 0; i < A.get_col_size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            e_j = Q.get_col(j);
            coef = ( A.get_col(i) * e_j ) / ( e_j * e_j );
            R(j, i) = coef;
            sum = sum + coef * e_j;
        }
        R(i, i) = 1;

        for (int k = 0; k < A.get_row_size(); k++)
            Q(k, i) = A(k, i) - sum[k];

        for (int k = 0; k < A.get_row_size(); k++)
            sum[k] = 0;
        for (int k = 0; k < A.get_row_size(); k++)
    }

    // add m - n vectors to basis
    std::vector<T> w_i(A.get_row_size());
    for (int i = A.get_col_size(); i < A.get_row_size(); i++)
    {
        for (int j = 0; j < A.get_row_size(); j++)
            if (i == j) {w_i[j] = 1;} else {w_i[j] = 0;}

        for (int j = 0; j < i; j++)
        {
            e_j = Q.get_col(j);
            sum = sum + ( w_i * e_j ) / ( e_j * e_j ) * e_j;
        }

        for (int k = 0; k < A.get_row_size(); k++)
            Q(k, i) = w_i[k] - sum[k];
    }

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, R);
    return QR;
}


#endif //MY_PROJECT_QR_DECOMPOSITION_GRAM_SCHMIDT_HPP