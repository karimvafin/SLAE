//
// Created by Карим Вафин on 26.03.2022.
//

#ifndef MY_PROJECT_CONJUGATEGRADIENTS_HPP
#define MY_PROJECT_CONJUGATEGRADIENTS_HPP

#include "project/SlaeBaseException.hpp"
#include "../sparse/CSR.hpp"
#include "project/utility/Norm.hpp"
#include "project/utility/overloads.hpp"

template<typename T>
std::vector<T> ConjugateGradients(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState, const T &tolerance)
{
#ifndef NDEBUG
    if (A.get_row_size() != b.size())
    {
        std::stringstream buff;
        buff << "Matrix and column dimensions are not equal! Matrix size: " << A.get_row_size() << "x" << A.get_col_size()
             << ". Column size: "<< b.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;

        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }

    if (A.get_row_size() != A.get_col_size())
    {
        std::stringstream buff;
        buff << "Matrix dimensions are not equal! Matrix size: " << A.get_row_size() << "x" << A.get_col_size()
             << ". File: " << __FILE__ << ". Line: " << __LINE__;

        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }

    if (initialState.size() != b.size())
    {
        std::stringstream buff;
        buff << "Vector of constant terms and initial state vector dimensions are not equal! Vector b size: "
             << b.size() << ". Initial state column size: "<< initialState.size() << ". File: "
             << __FILE__ << ". Line: " << __LINE__;

        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
#endif //NDEBUG

    std::vector<T> currentState = initialState;
    std::vector<T> nextState = currentState;
    std::vector<T> r = A * currentState - b;
    std::vector<T> next_r;
    std::vector<T> d = r;
    T beta;

    bool finished = is_equal(norm(r, NormType::ThirdNorm), 0);

    T alpha;

    while (not finished)
    {
        alpha = (r * r) / (d * (A * d));
        nextState = currentState - alpha * d;
        next_r = A * nextState - b;
        if (is_equal(norm(next_r, NormType::ThirdNorm), 0)) finished = true;
        else
        {
            beta = (next_r * next_r) / (r * r);
            d = next_r + beta * d;
            finished = (norm(next_r, NormType::ThirdNorm) < tolerance);
            currentState = nextState;
            r = next_r;
        }
    }

    return nextState;
}

#endif //MY_PROJECT_CONJUGATEGRADIENTS_HPP
