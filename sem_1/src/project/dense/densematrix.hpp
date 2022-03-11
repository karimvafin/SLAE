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

    std::vector<T> matrix_;
    idx_t row_size_, col_size_;

public:
    DenseMatrix(const idx_t &h, const idx_t& w)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
    }

    DenseMatrix(const idx_t &h, const idx_t& w, const std::set<Triplet<T>>& in)
    {
        row_size_ = h;
        col_size_ = w;
        if (in.size() > h * w)
        {
            std::stringstream buff;
            buff << "Set size exceeds matrix size! Set size: " << in.size() << ". Matrix size: "
                 << h * w << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        std::vector<T> vec(h * w, static_cast<T>(0));
        matrix_ = vec;
        for (auto &elem : in)
        {
            matrix_[elem.i * col_size_ + elem.j] = elem.value;
        }

    }

    elm_t& operator()(const idx_t& i, const idx_t& j)
    {
#ifndef NDEBUG
        if (i * col_size_ + j > matrix_.size())
        {
            std::stringstream buff;
            buff << "Index exceeds matrix size! Received index: " << i << "x" << j << ". Matrix size: "
                 << row_size_ << "x" << col_size_ << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG
        return matrix_[i * col_size_ + j];
    }

    const elm_t& operator()(const idx_t& i, const idx_t& j) const
    {
#ifndef NDEBUG
        if (i * col_size_ + j > matrix_.size())
        {
            std::stringstream buff;
            buff << "Index exceeds matrix size! Received index: " << i << "x" << j << ". Matrix size: "
                 << row_size_ << "x" << col_size_ << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG
        return matrix_[i * col_size_ + j];
    }

    [[nodiscard]] const idx_t& get_row_size() const
    {
        return row_size_;
    }

    [[nodiscard]] const idx_t& get_col_size() const
    {
        return col_size_;
    }

    void swap(const idx_t& first, const idx_t& second)
    {
        if (first == second)
        {
            std::stringstream buff;
            buff << "Index equal! Received index: " << first << " and " << second << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        if (first > row_size_ || second > row_size_)
        {
            std::stringstream buff;
            buff << "Index exceeds matrix row size! Received indexes: " << first << " and " << second
                 << ". Matrix size: " << row_size_ << "x" << col_size_ << ". File: " << __FILE__
                 << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        std::vector<T> tmp(col_size_);

        for (int i = 0; i < col_size_; ++i)
        {
            tmp[i] = matrix_[(first - 1) * col_size_ + i];
        }

        for (int i = 0; i < col_size_; ++i)
        {
            matrix_[(first - 1) * col_size_ + i] = matrix_[(second - 1) * col_size_ + i];
        }

        for (int i = 0; i < col_size_; ++i)
        {
            matrix_[(second - 1) * col_size_ + i] = tmp[i];
        }

    }

    void deleteLastRow()
    {
        matrix_.erase(matrix_.end() - col_size_, matrix_.end());
        row_size_--;
    }

};

template<typename T>
std::ostream &operator<<(std::ostream &os, const DenseMatrix<T> &A)
{
    for (int i = 0; i < A.get_row_size(); ++i)
    {
        for (int j = 0; j < A.get_col_size(); ++j)
            os << A(i, j) << " ";
        os << std::endl;
    }

    return os;
}

#endif//SLAE_DENSEMATRIX_HPP
