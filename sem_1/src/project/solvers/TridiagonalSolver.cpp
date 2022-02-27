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

        std::vector<std::array<double, 2>> params(n - 1);

        params[0][0] = - matrix(0, 2) / matrix(0, 1);
        params[0][1] = col.at(0) / matrix(0, 1);

        for (int i = 1; i < col.size() - 1; i++)
        {
            params[i][0] = - matrix(i, 2) / (matrix(i, 0) * params[i - 1][0] + matrix(i, 1));
            params[i][1] = (col[i] - matrix(i, 0) * params[i - 1][1]) /
                    (matrix(i, 0) * params[i - 1][0] + matrix(i, 1));
        }

        result[n - 1] = (col[n - 1] - matrix(n - 1, 0) * params[n - 2][1]) /
                (matrix(n - 1, 0) * params[n - 2][0] + matrix(n - 1, 1));

        for (int i = n - 2; i >= 0; i--)
        {
            result[i] = params[i][0] * result[i + 1] + params[i][1];
        }

        return result;
    }
}