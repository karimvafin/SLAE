//
// Created by Карим Вафин on 16.04.2022.
//

#ifndef MY_PROJECT_OPERATIONS_HPP
#define MY_PROJECT_OPERATIONS_HPP

#include <cmath>
#include <limits>

bool compare_double(double x, double y)
{
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

bool compare_floats(float x, float y)
{
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

#endif //MY_PROJECT_OPERATIONS_HPP
