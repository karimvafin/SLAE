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

    /* @brief Tridiagonal matrix algorithm
     * Solves SLAE with three-diagonal matrix. You can learn more about the method here: https://ru.wikipedia.org/wiki/
     *
     * @param matrix -- three-diagonal matrix
     * @param col    -- column of constant terms
     *
     * @throw SlaeBaseExceptionCpp is thrown if matrix and column dimensions are not equal
     *
     * Returns n-size solution vector
    */
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col);

}  // namespace Slae::Solvers

#endif //MY_PROJECT_TRIDIAGONALSOLVER_HPP
