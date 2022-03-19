//
// Created by Карим Вафин on 19.03.2022.
//

#include "gtest/gtest.h"
#include "project/solvers/SteepestGradientDescent.hpp"
#include "project/solvers/FastSimpleIteration.hpp"

TEST(SGD, SGD_HI)
{
    int task = 2;
    if (task == 1)
    {
        std::set<Triplet<double>> s = {{0, 0, 10}, {1, 1, 10}, {1, 0, -9},
                                       {0, 1, -9}};


        CSR<double> A(2, 2, s);
        std::cout << A << std::endl;

        std::vector<double> b = {-4, 15};

        std::vector<double> x_01 = {0, 0};
        std::vector<double> x_02 = {-0.4, 0};
        std::vector<double> x_03 = {10., 0};
        std::vector<double> x_04 = {11., 0};
        std::vector<double> x_05 = {5.1, 6.2};
        std::pair<double, double> borders(1., 19.);

        std::vector<double> sol = FastSimpleIteration<double, 7>(A, b, x_02, borders);
        //std::vector<double> sol = SGD<double>(A, b, x_01, 1e-12);
    }

    if (task == 2)
    {
        std::set<Triplet<double>> s = {{0, 0, 10}, {0, 1, -18}, {0, 2, 2},
                                       {1, 0, -18}, {1, 1, 40}, {1, 2, -1},
                                       {2, 0, 2}, {2, 1, -1}, {2, 2, 3}};
        CSR<double> A(3, 3, s);
        std::cout << A << std::endl;

        std::vector<double> b = {-12, 47, 8};

        std::vector<double> x_01 = {0, 0, 0};
        std::vector<double> x_02 = {15.09, 7.66, -6.56};
        std::vector<double> x_03 = {11.77, 6.42, -4.28};
        std::vector<double> x_04 = {4.46, 2.25, 1.85};

        std::pair<double, double> borders(0.706, 48.498);

        //std::vector<double> sol = FastSimpleIteration<double, 7>(A, b, x_04, borders);
        std::vector<double> sol = SGD<double>(A, b, x_04, 1e-13);

    }

    ASSERT_TRUE(true);
}
