//
// Created by Карим Вафин on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALMATRIX_HPP
#define MY_PROJECT_THREEDIAGONALMATRIX_HPP

#include "project/SlaeBaseException.hpp"

#include <array>
#include <vector>
#include <sstream>
#include <string>

namespace Slae::Matrix
{
    class ThreeDiagonalMatrix
    {
    public:

        /*** @brief ThreeDiagonalMatrix class constructor
         * Creates three-diagonal matrix with size 'size'
         *
         * @param size -- matrix size
        */
        explicit ThreeDiagonalMatrix(unsigned size);

        /*** @brief ThreeDiagonalMatrix class static 'constructor'
         * Creates three-diagonal matrix with size 'size' and fill it by zeros
         *
         * @param size -- matrix size
         *
         * @return zero-filled size-sized ThreeDiagonalMatrix
        */
        static ThreeDiagonalMatrix Zero(unsigned size);

        /*** @brief ThreeDiagonalMatrix class operator ()
         * Returns &(i, j) element of three-diagonal matrix; i -- row, j belongs to {0, 1, 2}
         *
         * @param i -- row
         * @param j -- one of diagonal elements in a row i; j belongs to {0, 1, 2}
         *
         * @throw SlaeBaseExceptionCpp if i > matrix row-size or j > 2
        */
        double & operator()(int i, int j);

        /*** @brief ThreeDiagonalMatrix class const operator ()
         * Returns const &(i, j) element of three-diagonal matrix; i -- row, j belongs to {0, 1, 2}
         *
         * @param i -- row
         * @param j -- one of diagonal elements in a row i; j belongs to {0, 1, 2}
         *
         * @throw SlaeBaseExceptionCpp if i > matrix row-size or j > 2
        */
        [[nodiscard]] const double & operator()(int i, int j) const;

        /*** @brief ThreeDiagonalMatrix class method
         *
         * @return matrix row-size
         *
        */
        [[nodiscard]] unsigned int rows() const noexcept;

    private:
        std::vector<std::array<double, 3>> data_;

    };

}  // namespace Slae::Matrix

#endif //MY_PROJECT_THREEDIAGONALMATRIX_HPP
