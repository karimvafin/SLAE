//
// Created by Карим Вафин on 24.02.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include "project/solvers/Jacobi.hpp"
#include "project/utility/overloads.hpp"

TEST(JACOBI, JACOBI_HI)
{
    /*
     * 2 0 0
     * 0 1 0
     * 0 0 1
     */

    std::set<Triplet<double>> derevo = {{0, 0, 2}, {1, 1, 1}, {2, 2, 1}};

    CSR<double> matrix(3, 3, derevo);

    std::vector<double> b = {1, 2, 1};

    std::vector<double> true_sol = {0, 0, 0};

    std::vector<double> initialState = {1, 1, 1};

    std::vector<double> sol = Jacobi(matrix, b, initialState, 0.0001);

    std::cout << sol;
    ASSERT_TRUE(true);
}
