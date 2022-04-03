#ifndef GIVENS_HPP
#define GIVENS_HPP

#include "../sem_1/src/project/utility/overloads.hpp"
#include "../sem_1/src/project/dense/densematrix.hpp"
#include <cmath>

#define tolerance 10e-15

template<typename T>
std::pair<DenseMatrix<T>, DenseMatrix<T>> GivensRotation(DenseMatrix<T>& A)
{
    DenseMatrix<T> Q(A.get_row_size(), A.get_row_size(), 0);
    DenseMatrix<T> B_res(A.get_row_size(), A.get_col_size(), 0);
    DenseMatrix<T> R = A;
    //R = A;

    for (int k = 0; k < B_res.get_col_size(); ++k)
        B_res(k, k) = 1;

    T sin, cos;
    T upper, lower;

    for(size_t step = 0; step < R.get_col_size(); ++step)
    {
        for (size_t i = step + 1; i < R.get_row_size(); ++i)
        {
            cos = R(step, step) / sqrt(R(step, step) * R(step, step) + R(i, step) * R(i, step));
            sin = R(i, step) / sqrt(R(step, step) * R(step, step) + R(i, step) * R(i, step));

            DenseMatrix<T> B(R.get_row_size(), R.get_col_size(), 0);
            for (int k = 0; k < B.get_col_size(); ++k)
                B(k, k) = 1;
            B(step, step) = cos;
            B(i, i) = cos;
            B(i, step) = -sin;
            B(step, i) = sin;

            for (size_t j = 0; j < B_res.get_row_size(); ++j)//multiplying
            {
                upper = cos * B_res(step, j) + sin * B_res(i, j);
                lower = -sin * B_res(step, j) + cos * B_res(i, j);

                B_res(step, j) = upper;
                B_res(i, j) = lower;
            }

            for (size_t j = step; j < R.get_row_size(); ++j)
            {
                upper = cos * R(step, j) + sin * R(i, j);
                lower = -sin * R(step, j) + cos * R(i, j);

                if(fabs(lower) < tolerance)
                    lower = 0;
                R(step, j) = upper;
                R(i, j) = lower;
            }
        }
    }


    for (size_t i = 0; i < B_res.get_row_size(); ++i)
    {
        for (size_t j = 0; j < B_res.get_col_size(); ++j)
            Q(i, j) = B_res(j, i);
    }

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, R);
    return QR;
}

#endif //GIVENS_HPP