//
// Created by Карим Вафин on 05.02.2022.
//

#include "ThreeDiagonalMatrix.hpp"

using std::array;
using std::vector;

namespace Slae::Matrix
{
    ThreeDiagonalMatrix::ThreeDiagonalMatrix(unsigned int size) : data_(size) {}

    ThreeDiagonalMatrix ThreeDiagonalMatrix::Zero(unsigned int size)
    {
        ThreeDiagonalMatrix result(size);
        for (auto& string: result.data_)
        {
            string = {0., 0., 0.};
        }

        return result;
    }

    double & ThreeDiagonalMatrix::operator()(int i, int j)
    {
#ifndef NDEBUG
        if (i >= data_.size())
        {
            std::stringstream buff;
            buff << "Index i exceeds matrix size! Received index: " << i << ". Matrix size: "
                 << data_.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw SlaeBaseExceptionCpp(buff.str());
        }

        if (j > 2)
        {
            std::stringstream buff;
            buff << "Index j must belong to {0, 1, 2}! Received index: " << i << ". Matrix size: "
                 << data_.size() << data_.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw SlaeBaseExceptionCpp(buff.str());
        }
#endif
        return data_[i][j];
    }

    const double & ThreeDiagonalMatrix::operator()(int i, int j) const
    {
#ifndef NDEBUG
        if (i >= data_.size())
        {
            std::stringstream buff;
            buff << "Index i exceeds matrix size! Received index: " << i << ". Matrix size: "
                 << data_.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw SlaeBaseExceptionCpp(buff.str());
        }

        if (j > 2)
        {
            std::stringstream buff;
            buff << "Index j must belong to {0, 1, 2}! Received index: " << i << ". Matrix size: "
                 << data_.size() << data_.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw SlaeBaseExceptionCpp(buff.str());
        }
#endif
        return data_[i][j];
    }

    unsigned int ThreeDiagonalMatrix::rows() const noexcept
    {
        return data_.size();
    }
}