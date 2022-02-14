//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_OVERLOADS_HPP
#define SLAE_OVERLOADS_HPP
#include <iosfwd>
#include <vector>
#include "operations.cpp"
/***
 * Умножение числа на вектор
 * @tparam T Тип числа
 * @param k Число
 * @param b Вектор
 * @return Результат умножения
 */
template<typename T>
std::vector<T> operator*(const T &k, const std::vector<T> &b);

/***
 * Умножение вектора на число
 * @tparam T Тип числа
 * @param b Вектор
 * @param k Число
 * @return Результат умножения
 */
template<typename T>
std::vector<T> operator*(const std::vector<T> &b, const T &k);

/***
 * Скалярное перемножение векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат скалярного перемножения
 */
template<typename T>
T operator*(const std::vector<T> &a, const std::vector<T> &b);

/***
 * Вычитание двух векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат вычитания векторов
 */
template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b);

/***
 * Сложение двух векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат сложения векторов
 */
template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b);

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
 * Сравнение двух векторов
 * @tparam T Тип элементов векторов
 * @param vec1 Первый вектор
 * @param vec2 Второй вектор
 * @return Результат сравнения векторов
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
