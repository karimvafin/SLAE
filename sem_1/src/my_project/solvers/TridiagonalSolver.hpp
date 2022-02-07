//
// Created by Карим Вафин on 05.02.2022.
//

#ifndef MY_PROJECT_TRIDIAGONALSOLVER_HPP
#define MY_PROJECT_TRIDIAGONALSOLVER_HPP

#include "my_project/matrix/ThreeDiagonalMatrix.hpp"
#include "my_project/SlaeBaseException.hpp"
#include <sstream>
#include <vector>

namespace Slae::Solvers
{
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col);

}  // namespace Slae::Solvers

#endif //MY_PROJECT_TRIDIAGONALSOLVER_HPP
