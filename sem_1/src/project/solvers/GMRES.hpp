//
// Created by Карим Вафин on 09.04.2022.
//

#ifndef MY_PROJECT_GMRES_HPP
#define MY_PROJECT_GMRES_HPP

#include "project/dense/densematrix.hpp"
#include "project/sparse/CSR.hpp"
#include "project/utility/Norm.hpp"
#include "project/utility/overloads.hpp"
#include "project/solvers/ReverseGauss.hpp"
#include <cmath>

void KrylovSubspace(DenseMatrix<double>& V, DenseMatrix<double>& H, const CSR<double>& A, const int& k)
{
    V.write_col(A * V.get_col(k), k + 1);
    for (int i = 0; i < k + 1; i++)
    {
        H(i, k) = V.get_col(i) * V.get_col(k + 1);
        V.write_col(V.get_col(k + 1) - H(i, k) * V.get_col(i), k + 1);
    }
    H(k + 1, k) = norm(V.get_col(k + 1), NormType::ThirdNorm);
    V.write_col(1. / H(k + 1, k) * V.get_col(k + 1), k + 1);
}

void GivensRotation(std::vector<std::pair<double, double>>& cs, DenseMatrix<double>& H, std::vector<double>& z,
                    const int& k)
{
    double cos;
    double sin;
    double alpha;
    double beta;
    for (int i = 0; i < k; i++)
    {
        beta = H(i, k);
        H(i, k) = H(i, k) * cs[i].first - H(i + 1, k) * cs[i].second;
        H(i + 1, k) = beta * cs[i].second + H(i + 1, k) * cs[i].first;
    }

    alpha = std::sqrt(H(k, k) * H(k, k) + H(k + 1, k) * H(k + 1, k));
    cos = H(k, k) / alpha;
    sin = - H(k + 1, k) / std::sqrt(H(k, k) * H(k, k) + H(k + 1, k) * H(k + 1, k));

    std::pair<double, double> a(cos, sin);
    cs[k] = a;
    beta = H(k, k);
    H(k, k) = H(k, k) * cos - H(k + 1, k) * sin;
    H(k + 1, k) = beta * sin + H(k + 1, k) * cos;

    beta = z[k];
    z[k] = z[k] * cos - z[k + 1] * sin;
    z[k + 1] = beta * sin + z[k + 1] * cos;
}


std::vector<double> GMRES(const CSR<double>& A, const std::vector<double>& b, const std::vector<double> &initialState,
                          const double &tolerance)
{
    int m = A.get_row_size();
    std::vector<double> r = A * initialState - b;
    std::vector<double> currentState = initialState;
    DenseMatrix<double> V(m, m + 1);
    DenseMatrix<double> H(m + 1, m);
    std::vector<std::pair<double, double>> cs(m + 1);
    std::vector<double> z(m + 1);

    bool finished = false;
    double alpha;

    while (!finished)
    {
        alpha = norm(r, NormType::ThirdNorm);
        for (int i = 1; i < m + 1; i++)
            z[i] = 0;
        z[0] = alpha;
        V.write_col(1. / alpha * r, 0);
        for (int i = 1; i < m + 1; i++)
        {
            KrylovSubspace(V, H, A, i - 1);
            GivensRotation(cs, H, z, i - 1);
            if (std::abs(z[i]) < tolerance)
            {
                std::vector<double> y = ReverseGauss(H, z, i);
                for (int j = 0; j < i; j++)
                    currentState = currentState -  y[j] * V.get_col(j);
                finished = true;
                break;
            }
        }
        if (!finished)
        {
            std::vector<double> y = ReverseGauss(H, z, m);
            for (int j = 0; j < m; j++)
                currentState = currentState -  y[j] * V.get_col(j);
        }
        r = A * currentState - b;
    }

    return currentState;
}

#endif //MY_PROJECT_GMRES_HPP
