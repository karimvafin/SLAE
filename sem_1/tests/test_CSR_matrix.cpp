//
// Created by Карим Вафин on 14.02.2022.
//

#include "gtest/gtest.h"
#include "project/sparse/CSR.hpp"
#include "project/utility/overloads.hpp"

TEST(CSRMATRIX, CSRMATRIX_HI)
{
    // 3x3
    std::set<Triplet<double>> fill = {{0, 0, 1}, {0, 1, 1}, {0, 2, 1}};
    CSR<double> CSR_matrix_1(3, 3, fill);
    std::cout << CSR_matrix_1 << std::endl;

    // 5x5
    CSR<double> CSR_matrix_2(5, 5, fill);
    std::cout << CSR_matrix_2 << std::endl;

    // 10x10
    CSR<double> CSR_matrix_3(10, 10, fill);
    std::cout << CSR_matrix_3 << std::endl;

    // 20x20
    CSR<double> CSR_matrix_4(15, 15, fill);
    std::cout << CSR_matrix_4 << std::endl;

    ASSERT_TRUE(true);
}

