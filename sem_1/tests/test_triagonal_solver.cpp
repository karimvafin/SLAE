//
// Created by Карим Вафин on 06.02.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include "my_project/solvers/TridiagonalSolver.hpp"

TEST(TRIDIAGONALSOLVER, TRIDIAGONALSOLVER_HI)
{
    Slae::Matrix::ThreeDiagonalMatrix matrix = Slae::Matrix::ThreeDiagonalMatrix::Zero(3);

// handmade example

    // matrix
    matrix(0, 1)  = 1;
    matrix(0, 2)  = 2;
    matrix(1, 0)  = 1;
    matrix(1, 1)  = 1;
    matrix(1, 2)  = 1;
    matrix(2, 0)  = 1;
    matrix(2, 1)  = 1;

    // column
    std::vector<double> col = {5, 10, 5};

//

    std::vector<double> solution = Slae::Solvers::solveThreeDiagonal(matrix, col);

    for (auto &it : solution)
    {
        std::cout << it << " ";
    }
}

