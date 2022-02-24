//
// Created by Карим Вафин on 14.02.2022.
//

#include "gtest/gtest.h"
#include "my_project/sparse/CSR.hpp"
#include "my_project/utility/overloads.hpp"

TEST(CSRMATRIX, CSRMATRIX_HI)
{

    /*
     * 2 0 3
     * 0 1 0
     * 0 0 1
     */
    Triplet<double> elem1 = {0, 0, 2};
    Triplet<double> elem2 = {0, 2, 3};
    Triplet<double> elem3 = {1, 1, 1};
    Triplet<double> elem4 = {2, 2, 1};

    std::set<Triplet<double>> derevo = {{0, 0, 1}, {2, 1, 5}};

    CSR<double> matrix(3, 3, derevo);

    std::vector<double> b = {1, 2, 1};

    std::vector<double> true_sol = {5, 2, 1};

    std::cout << matrix;
    /*
    bool res;

    if (true_sol == matrix * b)
        res = true;
    else
        res = false;

    ASSERT_TRUE(res);*/

}

