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
    for (int k = 0; k < B_res.get_col_size(); ++k)
        B_res(k, k) = 1;
    //std::vector<DenseMatrix<T>> B_arr;
    //вектор матриц T вращений и потом и[ перемножить??

    T sin, cos;
    T upper, lower;
    //на каждом шаге у нас будет зануляться один столбец
    for(size_t step = 0; step < A.get_col_size(); ++step)
    {
        for (size_t i = step + 1; i < A.get_row_size(); ++i) //идем по строкам; они сравниваются как step и step + i
        {
            cos = A(step, step) / sqrt(A(step, step) * A(step, step) + A(i, step) * A(i, step));
            sin = A(i, step) / sqrt(A(step, step) * A(step, step) + A(i, step) * A(i, step));

            DenseMatrix<T> B(A.get_row_size(), A.get_col_size(), 0);
            for (int k = 0; k < B.get_col_size(); ++k)
                B(k, k) = 1;
            B(step, step) = cos;
            B(i, i) = cos;
            B(i, step) = -sin;
            B(step, i) = sin;

            for (size_t j = 0; j < B_res.get_row_size(); ++j)//идем по столбцам;
            {
                upper = cos * B_res(step, j) + sin * B_res(i, j);
                lower = -sin * B_res(step, j) + cos * B_res(i, j);

                if(fabs(lower) < tolerance)
                    lower = 0;
                B_res(step, j) = upper;
                B_res(i, j) = lower;
            }
            //B_arr.push_front(B);

            for (size_t j = step; j < A.get_row_size(); ++j)//идем по столбцам;
            {
                upper = cos * A(step, j) + sin * A(i, j);
                lower = -sin * A(step, j) + cos * A(i, j);

                if(fabs(lower) < tolerance)
                    lower = 0;
                A(step, j) = upper;
                A(i, j) = lower;
            }
        }
    }


    for (size_t i = 0; i < B_res.get_row_size(); ++i)
    {
        for (size_t j = 0; j < B_res.get_col_size(); ++j)
            Q(i, j) = B_res(j, i);
    }

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, A);
    return QR;
}

#endif //GIVENS_HPP