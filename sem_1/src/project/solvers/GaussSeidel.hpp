//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_GAUSSSEIDEL_HPP
#define SLAE_GAUSSSEIDEL_HPP

#include <project/utility/Norm.hpp>
#include "../sparse/CSR.hpp"
#include "project/utility/overloads.hpp"
#include <iostream>
#include <fstream>


template <typename T>
std::vector<T> GaussSeidelIteration(const CSR<T> &A, const std::vector<T> &b, std::vector<T> initialState)
{
    T sum;
    for (int i = 0; i < A.get_row_size(); ++i)
    {
        sum = static_cast<T>(0);
        int skip = A.rows_[i];
        int count = A.rows_[i + 1] - skip;
        for (int k = skip; k < skip + count; ++k)
        {
            if (A.cols_[k] != i) sum += A.values_[k] * initialState[i];
        }

        initialState[i] = (b[i] - sum) / A(i, i);
    }

    return initialState;
}


template<typename T>
std::vector<T> GaussSeidel(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState, const T &tolerance)
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

    std::vector<T> r = A * initialState - b;
    std::vector<T> currentState = initialState;

    T sum;
    while (norm(r, NormType::ThirdNorm) > tolerance)
    {
        currentState = GaussSeidelIteration(A, b, currentState);
        r = A * currentState - b;
    }

    return currentState;
}


template<typename T>
std::vector<T> FastGaussSeidel(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState,
                               T rho, const T &tolerance)
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

    std::vector<T> prevState = initialState;
    std::vector<T> currentState = GaussSeidelIteration(A, b, initialState);
    std::vector<T> nextState = currentState;
    std::vector<T> r = A * nextState - b;

    T sum;
    T mu0 = static_cast<T>(1.);
    T mu1 = static_cast<T>(1.) / rho;
    T mu2 = static_cast<T>(2.) / rho * mu1 - mu0;
    std::cout << norm(r, NormType::ThirdNorm) << std::endl;
    while (norm(r, NormType::ThirdNorm) > tolerance)
    {
        std::cout << norm(r, NormType::ThirdNorm) << std::endl;
        nextState = static_cast<T>(2.) * mu1 / rho / mu2 * GaussSeidelIteration(A, b, currentState) - mu0 / mu2 * prevState;
        prevState = currentState;
        currentState = nextState;
        mu0 = mu1;
        mu1 = mu2;
        mu2 = static_cast<T>(2.) / rho * mu1 - mu0;
        r = A * currentState - b;

    }

    return nextState;
}

#endif//SLAE_GAUSSSEIDEL_HPP
