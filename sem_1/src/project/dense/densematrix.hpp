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
class DenseMatrix
{
public:
    using elm_t = T;
    using idx_t = std::size_t;

private:

    std::vector<T> matrix_;
    idx_t row_size_, col_size_;

public:

    /***
     *
     * @param h
     * @param w
     */
    DenseMatrix(const idx_t &h, const idx_t& w)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
    }

    DenseMatrix(const DenseMatrix<T>& matrix)
    {
        row_size_ = matrix.get_row_size();
        col_size_ = matrix.get_col_size();
        matrix_.resize(row_size_ * col_size_);
        for (int j = 0; j < col_size_; j++)
        {
            for (int i = 0; i < row_size_; i++)
            {
                matrix_[i * col_size_ + j] = matrix(i, j);
            }
        }
    }

    /***
     *
     * @param h
     * @param w
     */
    DenseMatrix(const idx_t &h, const idx_t& w, const std::vector<T> &data)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
        for (int i = 0; i < data.size(); i++)
        {
            matrix_[i] = data.at(i);
        }
    }

    /***
     * Fills matrix with one value
     * @param h    -- row size
     * @param w    -- col size
     * @param fill -- value
     * @return dense matrix filled by value
     */
    DenseMatrix(const idx_t &h, const idx_t& w, T fill)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
        for (int i = 0; i < h * w; i++)
            matrix_[i] = fill;
    }

    /***
     * Unit matrix
     * @param h -- matrix size
     * @return dense unit matrix
     */
    static DenseMatrix<T> unit_matrix(const idx_t &h)
    {
        DenseMatrix<T> matrix(h, h, 0);
        for (int i = 0; i < h; i++) matrix(i, i) = 1;
        return matrix;
    }


    /***
     *
     * @param h
     * @param w
     * @param in
     */
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


    /***
     * Non-const access operator
     * @param i
     * @param j
     * @return (i, j) element
     */
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


    /***
     * Const access operator
     * @param i
     * @param j
     * @return
     */
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


    /***
     * Returns row size
     * @return row size
     */
    [[nodiscard]] const idx_t& get_row_size() const
    {
        return row_size_;
    }


    /***
     * Column size
     * @return column size
     */
    [[nodiscard]] const idx_t& get_col_size() const
    {
        return col_size_;
    }


    /***
     * Return matrix column with index i
     * @param i column index (i <= col_size, begins from 0)
     * @return vector -- matrix column
     */
    std::vector<T> get_col(unsigned i) const
    {
#ifndef NDEBUG
        if (i >= col_size_)
        {
            std::stringstream buff;
            buff << "Index exceeds matrix col_size! Received index: " << i << ". Matrix size: "
                 << row_size_ << "x" << col_size_ << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG
        std::vector<T> col(row_size_);

        for (unsigned j = 0; j < row_size_; j++)
            col[j] = matrix_[j * col_size_ + i];

        return col;
    }


    /***
     * Swaps 2 rows
     * @param first
     * @param second
     */
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


    /***
     * Deletes last row in matrix
     */
    void deleteLastRow()
    {
        matrix_.erase(matrix_.end() - col_size_, matrix_.end());
        row_size_--;
    }

};


/***
 * Matrix output
 * @tparam T
 * @param os
 * @param A
 * @return stream
 */
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

/***
 * Dense matrix multiplication
 * @tparam T
 * @param A
 * @param B
 * @return dense matrix -- result of multiplication
 */
template <typename T>
DenseMatrix<T> operator*(const DenseMatrix<T> &A, const DenseMatrix<T> &B)
{
    DenseMatrix<T> result(A.get_row_size(), B.get_col_size(), 0);

    for (int i = 0; i < A.get_row_size(); i++)
    {
        for (int j = 0; j < B.get_col_size(); j++)
        {
            for (int k = 0; k < A.get_col_size(); k++)
                result(i, j) += A(i, k) * B(k, j);
        }
    }

    return result;
}

#endif//SLAE_DENSEMATRIX_HPP
