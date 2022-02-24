//
// Created by Карим Вафин on 14.02.2022.
//
#include <cmath>
#include <limits>

bool is_equal(double x, double y)
{
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

bool is_equal(float x, float y)
{
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}
