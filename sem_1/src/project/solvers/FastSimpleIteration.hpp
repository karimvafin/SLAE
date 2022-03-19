//
// Created by Карим Вафин on 07.03.2022.
//

#ifndef MY_PROJECT_FASTSIMPLEITERATION_HPP
#define MY_PROJECT_FASTSIMPLEITERATION_HPP

#include "project/SlaeBaseException.hpp"
#include "../sparse/CSR.hpp"
#include "project/utility/Norm.hpp"
#include "project/utility/overloads.hpp"
#include "project/Chebyshev/Chebyshev.h"
#include <cmath>

template<typename T, int powOf2>
std::vector<T> FastSimpleIteration(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState,
                                   std::pair<T, T> &borders)
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

    ChebyshevPolynomial<T, powOf2> pol;
    std::vector<T> tao_roots = pol.CalculateRoots(borders);
    std::vector<T> currentState = initialState;
    std::vector<T> r = A * currentState - b;

    for (int i = 0; i < pow(2, powOf2); i++)
    {
        currentState = currentState - 1 / tao_roots[i] * r;
        r = A * currentState - b;
    }

    return currentState;
}

#endif //MY_PROJECT_FASTSIMPLEITERATION_HPP
