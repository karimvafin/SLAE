//
// Created by Карим Вафин on 21.02.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include "my_project/dense/densematrix.hpp"
#include "my_project/utility/overloads.hpp"

TEST(DENSEMATRIX, DENSEMATRIX_HI)
{
    bool result = true;
    std::set<Triplet<int>> in = {{0, 0, 1}, {0, 1, 2}, {0, 2, 3},
                                 {3, 0, 4}, {1, 1, 5}, {1, 2, 6}};
    DenseMatrix<int> matrix(5, 7, in);

    matrix.swap(1, 2);
    matrix.deleteLastRow();

    std::cout << matrix;

    ASSERT_TRUE(result);
}
