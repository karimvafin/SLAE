//
// Created by Карим Вафин on 16.04.2022.
//

#ifndef MY_PROJECT_LEASTSQUARES_HPP
#define MY_PROJECT_LEASTSQUARES_HPP

#include "project/Generators/MatrixGenerator.hpp"
#include "project/decompositions/QR_decomposition_Givens.hpp"
#include "project/decompositions/QR_decomposition_Householder.hpp"
#include "project/solvers/ReverseGauss.hpp"
#include <cmath>

template <typename T>
std::vector<T> LeastSquares(const std::vector<T>& X, const std::vector<T>& Y, const int& power)
{
    DenseMatrix<T> A(X.size(), power + 1);
    for (int i = 0; i < power; i++)
        for (int j = 0; j < X.size(); j++)
            A(j, i) = std::pow(X[j], power - i);
    for (int i = 0; i < X.size(); i++)
        A(i, power) = 1;

    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR = QR_decomposition_Householder(A);
    std::vector<T> b = QR.first.transpose() * Y;

    for (int i = 0; i < X.size() - power - 1; i++)
    {
        QR.second.deleteLastRow();
        b.pop_back();
    }

    std::vector<T> sol = ReverseGauss(QR.second, b);

    return sol;
}
#endif //MY_PROJECT_LEASTSQUARES_HPP
