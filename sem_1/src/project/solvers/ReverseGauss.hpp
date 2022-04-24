//
// Created by Карим Вафин on 16.04.2022.
//

#ifndef MY_PROJECT_REVERSEGAUSS_HPP
#define MY_PROJECT_REVERSEGAUSS_HPP

#include "project/dense/densematrix.hpp"
#include "project/utility/overloads.hpp"

template <typename T>
std::vector<T> ReverseGauss(const DenseMatrix<T>& R, const std::vector<T>& b, const int& n)
{
    std::vector<T> sol(n, 0);

    for (int i = 0; i < n; i++)
    {
        sol[n - i - 1] = b[n - i - 1];
        for (int k = n - 1; k > n - i - 1; k--)
            sol[n - i - 1] -=  R(n - i - 1, k) * sol[k];
        sol[n - i - 1] /= R(n - i - 1, n - i - 1);
    }

    return sol;
}
#endif //MY_PROJECT_REVERSEGAUSS_HPP
