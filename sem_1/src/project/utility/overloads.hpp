//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_OVERLOADS_HPP
#define SLAE_OVERLOADS_HPP
#include <iosfwd>
#include <vector>
#include "operations.cpp"

/***
 * Scalar product of two vectors
 * @tparam T template type
 * @param a first vector
 * @param b second vector
 * @return result of scalar product
 */
template<typename T>
T operator*(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        result[i] = a[i] * b[i];
    }
    return result;
}

/***
 * Subtraction of two vector
 * @tparam T template type
 * @param a first vector
 * @param b second vector
 * @return result of vector subtraction
 */
template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        result[i] = a[i] - b[i];
    }

    return result;
}

/***
 * Operator of vector and number multiplication
 * @tparam T template type
 * @param alpha number
 * @param b vector
 * @return vector alpha * b
 */
template <typename T>
std::vector<T> operator*(const T &alpha, const std::vector<T> &b)
{
    std::vector<T> result(b.size());
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = alpha * b[i];
    }
    return result;
}

template <typename T>
std::vector<T> operator*(const std::vector<T> &b, const T &alpha)
{
    std::vector<T> result(b.size());
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = alpha * b[i];
    }
    return result;
}

/***
 * Addition of two vectors
 * @tparam T template type
 * @param a first vector
 * @param b second vector
 * @return result of vector addition
 */
template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<T> result(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        result[i] = a[i] + b[i];
    }

    return result;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &b)
{
    for (auto &it : b)
    {
        os << it << " ";
    }

    return os;
}

/***
 * Comparison of two vectors
 * @tparam T template type
 * @param vec1 first vector
 * @param vec2 second vector
 * @return result of vector comparison
 */
template<typename T>
bool operator==(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    if (vec1.size() != vec2.size())
    {
        return false;
    }

    for (int i = 0; i < vec1.size(); ++i)
    {
        if (not is_equal(vec1[i], vec2[i]))
            return false;
    }

    return true;
}

#endif//SLAE_OVERLOADS_HPP
