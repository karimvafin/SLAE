//
// Created by Карим Вафин on 07.03.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include "project/solvers/GaussSeidel.hpp"
#include "project/utility/overloads.hpp"

TEST(GAUSSSEIDEL, GAUSSSEIDEL_HI)
{
    /*
     * 2 0 0
     * 0 1 0
     * 0 0 1
     */
    std::cout<<"Something";
    std::set<Triplet<double>> derevo = {{0, 0, 2}, {1, 1, 1}, {2, 2, 1}};

    CSR<double> matrix(3, 3, derevo);

    std::vector<double> b = {1, 2, 1};

    std::vector<double> true_sol = {0, 0, 0};

    std::vector<double> initialState = {1, 0, 0};

    std::vector<double> sol = GaussSeidel(matrix, b, initialState, 0.0001);
    std::cout<<"Something";
    std::cout << sol;
    ASSERT_TRUE(true);
}
