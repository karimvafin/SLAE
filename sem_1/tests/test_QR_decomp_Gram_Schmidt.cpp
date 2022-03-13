//
// Created by Карим Вафин on 12.03.2022.
//

#include "gtest/gtest.h"
#include "project/decompositions/QR_decomposition_Gram_Schmidt.hpp"

TEST(QR123, QR123_HI)
{
    std::cout << "1... 2... 3..." << std::endl;
    std::vector<double> elms = {3., 2., 3., 4., 5., 6., 10., 20., 35., 0, 3.5, 13, 12, 1, 56, 4, 3, 2, 4, 5, 6, 7, 23, 4, 5,2, 4, 5, 4};
    DenseMatrix<double> matrix(9, 5, elms);

    std::cout << "Start" << std::endl;

    std::pair<DenseMatrix<double>, DenseMatrix<double>> QR = QR_decomposition_Gram_Schmidt(matrix);

    std::cout << "Matrix A:" << std::endl << matrix << std::endl << std::endl;
    std::cout << "Matrix Q:" << std::endl << QR.first << std::endl << std::endl;
    std::cout << "Matrix R:" << std::endl << QR.second << std::endl << std::endl;



    std::cout << "Matrix Q * R:" << std::endl << QR.first * QR.second << std::endl << std::endl;
ASSERT_TRUE(true);
}