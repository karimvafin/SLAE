//
// Created by Карим Вафин on 05.02.2022.
//

#include "TridiagonalSolver.hpp"

namespace Slae::Solvers
{
    std::vector<double> solveThreeDiagonal(const Slae::Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col)
    {
        if (matrix.rows() != col.size())
        {
            std::stringstream buff;
            buff << "Matrix and column dimensions are not equal! Matrix size: " << matrix.rows() << ". Column size: "
                 << col.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;
            throw SlaeBaseExceptionCpp(buff.str());
        }

        int n = col.size();

        std::vector<double> result(n);
        std::vector<double> gamma(n - 1);
        std::vector<double> betta(n - 1);

        gamma.at(0) = - matrix(0, 2) / matrix(0, 1);
        betta.at(0) = col.at(0) / matrix(0, 1);

        for (int i = 1; i < col.size() - 1; i++)
        {
            gamma.at(i) = - matrix(i, 2) / (matrix(i, 0) * gamma.at(i - 1) + matrix(i, 1));
            betta.at(i) = (col.at(i) - matrix(i, 0) * betta.at(i - 1)) /
                    (matrix(i, 0) * gamma.at(i - 1) + matrix(i, 1));
        }

        result.at(n - 1) = (col.at(n - 1) - matrix(n - 1, 0) * betta.at(n - 2)) /
                (matrix(n - 1, 0) * gamma.at(n - 2) + matrix(n - 1, 1));

        for (int i = n - 2; i >= 0; i--)
        {
            result.at(i) = gamma.at(i) * result.at(i + 1) + betta.at(i);
        }

        return result;
    }
}