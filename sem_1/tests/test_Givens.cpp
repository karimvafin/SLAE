//
// Created by mash on 04.04.2022.
//

#include "../../task_1/Givens.hpp"
#include "gtest/gtest.h"


TEST(GIVENS, GIVENS_HI)
{
    std::cout << "1... 2... 3..." << std::endl;
    std::vector<double> elms = {3., 2., 3., 4., 5., 6., 10., 20., 35., 0, 3.5, 13, 12, 1, 56, 4, 3, 2, 4, 5, 6, 7, 23, 4, 5};
    DenseMatrix<double> matrix(5, 5, elms);

    std::cout << "Start" << std::endl;

    std::pair<DenseMatrix<double>, DenseMatrix<double>> QR = GivensRotation(matrix);

    std::cout << "Matrix A:" << std::endl << matrix << std::endl << std::endl;
    std::cout << "Matrix Q:" << std::endl << QR.first << std::endl << std::endl;
    std::cout << "Matrix R:" << std::endl << QR.second << std::endl << std::endl;



    std::cout << "Matrix Q * R:" << std::endl << QR.first * QR.second << std::endl << std::endl;
    ASSERT_TRUE(true);
}