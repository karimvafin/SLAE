#ifndef GIVENS_HPP
#define GIVENS_HPP

#include "../sem_1/src/project/utility/overloads.hpp"
#include "../sem_1/src/project/dense/densematrix.hpp"

template<typename T>
std::pair<DenseMatrix<T>, DenseMatrix<T>> GivensRotation(DenseMatrix<T>& A)
{
    DenseMatrix<T> Q(A.get_row_size(), A.get_row_size(), 0);
    //DenseMatrix<T> R(A.get_row_size(), A.get_col_size(), 0);
    std::vector<DenseMatrix<T>> B_arr;
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
            B(step, step) = B(i, i) = cos;
            B(i, step) = -sin;
            B(step, i) = sin;

            B_arr.push_front(B);

            for (size_t j = step + 1; j < A.get_row_size(); ++j)//идем по столбцам;
            {
                upper = cos * A(step, j) + sin * A(i, j);
                lower = -sin * A(step, j) + cos * A(i, j);

                //if(Tabs(lower) < tolerance<T>)
                //    lower = 0;
                A(step, j) = upper;
                A(i, j) = lower;
            }
        }
    }

    DenseMatrix<T> B_res(A.get_row_size(), A.get_col_size(), 0);
    for(int i = 0; i < B_arr.size(); ++i)
        B_res *= B_arr[i];

    for (size_t i = 0; i < A.get_row_size(); ++i)
    {
        for (size_t j = 0; j < A.get_col_size(); ++j)
            Q(i, j) = A(j, i);
    }

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, A);
    return QR;
}

#endif //GIVENS_HPP