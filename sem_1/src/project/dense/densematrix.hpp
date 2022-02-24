//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_DENSEMATRIX_HPP
#define SLAE_DENSEMATRIX_HPP
#include <vector>
#include <set>
#include "../utility/Triplet.hpp"
#include "project/SlaeBaseException.hpp"

template<typename T>
class DenseMatrix{
public:
    using elm_t = T;
    using idx_t = std::size_t;

private:

    std::vector<T> matrix;
    idx_t H, W;

public:
    DenseMatrix(const idx_t &h, const idx_t& w)
    {
        H = h;
        W = w;
        matrix.resize(h * w);
    }

    DenseMatrix(const idx_t &h, const idx_t& w, const std::set<Triplet<T>>& in)
    {
        H = h;
        W = w;
        if (in.size() > h * w)
        {
            std::stringstream buff;
            buff << "Set size exceeds matrix size! Set size: " << in.size() << ". Matrix size: "
                 << h * w << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        std::vector<T> vec(h * w, static_cast<T>(0));
        matrix = vec;
        for (auto &elem : in)
        {
            matrix[elem.i * W + elem.j] = elem.value;
        }

    }

    elm_t& operator()(const idx_t& i, const idx_t& j)
    {
#ifndef NDEBUG
        if (i * W + j > matrix.size())
        {
            std::stringstream buff;
            buff << "Index exceeds matrix size! Received index: " << i << "x" << j << ". Matrix size: "
                 << H << "x" << W << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG
        return matrix[i * W + j];
    }

    const elm_t& operator()(const idx_t& i, const idx_t& j) const
    {
#ifndef NDEBUG
        if (i * W + j > matrix.size())
        {
            std::stringstream buff;
            buff << "Index exceeds matrix size! Received index: " << i << "x" << j << ". Matrix size: "
                 << H << "x" << W << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG
        return matrix[i * W + j];
    }

    [[nodiscard]] const idx_t& sizeH() const
    {
        return H;
    }

    [[nodiscard]] const idx_t& sizeW() const
    {
        return W;
    }

    void swap(const idx_t& first, const idx_t& second)
    {
        if (first == second)
        {
            std::stringstream buff;
            buff << "Index equal! Received index: " << first << " and " << second << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        if (first > H || second > H)
        {
            std::stringstream buff;
            buff << "Index exceeds matrix row size! Received indexes: " << first << " and " << second
                 << ". Matrix size: " << H << "x" << W << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        std::vector<T> tmp(W);

        for (int i = 0; i < W; ++i)
        {
            tmp[i] = matrix[(first - 1) * W + i];
        }

        for (int i = 0; i < W; ++i)
        {
            matrix[(first - 1) * W + i] = matrix[(second - 1) * W + i];
        }

        for (int i = 0; i < W; ++i)
        {
            matrix[(second - 1) * W + i] = tmp[i];
        }

    }

    void deleteLastRow()
    {
        matrix.erase(matrix.end() - W, matrix.end());
        H--;
    }

};

template<typename T>
std::ostream &operator<<(std::ostream &os, const DenseMatrix<T> &A)
{
    for (int i = 0; i < A.sizeH(); ++i)
    {
        for (int j = 0; j < A.sizeW(); ++j)
            os << A(i, j) << " ";
        os << std::endl;
    }

    return os;
}

#endif//SLAE_DENSEMATRIX_HPP
