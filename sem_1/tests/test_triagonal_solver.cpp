//
// Created by Карим Вафин on 06.02.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include "my_project/solvers/TridiagonalSolver.hpp"
#include "my_project/utility/overloads.hpp"

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

    std::vector<double> sol = Slae::Solvers::solveThreeDiagonal(matrix, col);

    bool result;

    std::vector<double> true_sol = {5, 0, 5};

    if (sol == true_sol)
        result = true;
    else
        result = false;

    ASSERT_TRUE(result);
}

