//
// Created by Карим Вафин on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALMATRIX_HPP
#define MY_PROJECT_THREEDIAGONALMATRIX_HPP

#include "my_project/SlaeBaseException.hpp"

#include <array>
#include <vector>
#include <sstream>
#include <string>

namespace Slae::Matrix
{
    class ThreeDiagonalMatrix
    {
    public:
        explicit ThreeDiagonalMatrix(unsigned size);

        static ThreeDiagonalMatrix Zero(unsigned size);

        double & operator()(int i, int j);

        [[nodiscard]] const double & operator()(int i, int j) const;

        [[nodiscard]] unsigned int rows() const noexcept;

    private:
        std::vector<std::array<double, 3>> data_;

    };

}  // namespace Slae::Matrix

#endif //MY_PROJECT_THREEDIAGONALMATRIX_HPP
