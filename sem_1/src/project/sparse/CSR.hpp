//
// Created by petrov on 12.02.2022.
//

#ifndef SOLE2022_CSR_HPP
#define SOLE2022_CSR_HPP

#include <vector>
#include <iostream>
#include <set>
#include "project/utility/Triplet.hpp"
#include <sstream>
#include "project/SlaeBaseException.hpp"

template<typename T>
class CSR
{
public:
    using elm_t = T;           // type of matrix element
    using idx_t = std::size_t; // index type

private:
    const idx_t row_size_, col_size_; // matrix dimensions
    std::vector<elm_t> values_;       // vector of non-zero values
    std::vector<idx_t> cols_;         // vector of non-zero element column-index
    std::vector<idx_t> rows_;         // vector of amounts of non-zero elements from the beginning of the matrix to the end of row

    template<typename TT>
    friend std::vector<TT> Jacobi(const CSR<TT> &A, const std::vector<TT> &b, const std::vector<TT> &initialState, const TT &tolerance);

public:

    /***
     * Constructor of CSR matrix with prepared vectors of values, columns and rows (CSR format)
     * @param row_size number of rows in matrix
     * @param col_size number of columns in matrix
     * @param values vector of non-zero matrix elements
     * @param columns vector of non-zero element column-index
     * @param rows
     */
    CSR(const idx_t &row_size, const idx_t &col_size, const std::vector<T>& values, const std::vector<T>& columns,
        const std::vector<T>& rows): row_size_(row_size), col_size_(col_size)
    {
        values_ = values;
        cols_ = columns;
        rows_ = rows;
    }

    /***
     * Constructor of CSR matrix via set of Triplets (Triplet: (i, j, value)); i, j begin from 0
     * @param row_size number of rows in matrix
     * @param col_size number of columns in matrix
     */
    CSR(const idx_t &row_size, const idx_t &col_size, const std::set<Triplet<elm_t>>& in):
    row_size_(row_size), col_size_(col_size)
    {
        values_.resize(in.size());
        cols_.resize(in.size());
        rows_.resize(row_size + 1, 0);

        int countInRow = 0;
        int currRow = 0;
        auto it = in.begin();

        for (idx_t k = 0; k < in.size(); ++k)
        {
            values_[k] = it->value;
            cols_[k] = it->j;
            while (currRow < it->i)
            {
                rows_[currRow + 1] = rows_[currRow] + countInRow;
                ++currRow;
                countInRow = 0;
            }
            ++countInRow;
            it = std::next(it);
        }

        for (++currRow; currRow <= row_size_; ++currRow)
        {
            rows_[currRow] = in.size();
        }
    }

    /***
     * Operator to get (i, j) element of matrix
     * @param i row number (begins from 0)
     * @param j column number (begins from 0)
     * @return (i, j) element of matrix
     */
    const elm_t &operator()(idx_t const i, idx_t const j) const
    {
        idx_t skip = rows_[i];
        for (idx_t k = skip; k < rows_[i + 1]; ++k)
        {
            if (cols_[k] == j)
                return values_[k];
        }
        return static_cast<elm_t>(0);
    }

    /***
     * Operator of matrix and column multiplication
     * @param b column to multiplicate
     * @return result-vector of multiplication
     */
    std::vector<elm_t> operator*(const std::vector<elm_t> &b) const
    {
#ifndef NDEBUG
        if (col_size_ != b.size())
        {
            std::stringstream buff;
            buff << "Matrix and column dimensions are not equal! Matrix size: " << row_size_<< "x" << col_size_
            << ". Column size: " << b.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;
            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG
        std::vector<elm_t> result(col_size_);
        for (idx_t i = 0; i < col_size_; ++i)
        {
            idx_t skip = rows_[i];
            idx_t count = rows_[i + 1] - skip;
            for (idx_t k = skip; k < skip + count; ++k)
            {
                result[i] += values_[k] * b[cols_[k]];
            }
        }

        return result;
    }

    [[nodiscard]] idx_t get_col_size() const
    {
        return col_size_;
    }

    [[nodiscard]] idx_t get_row_size() const
    {
        return row_size_;
    }
};

/***
 * CSR matrix output operator
 * @param os output stream
 * @param matrix
 * @return ostream
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const CSR<T> &matrix)
{
    for (int i = 0; i < matrix.get_row_size(); ++i)
    {
        for (int j = 0; j < matrix.get_col_size(); ++j)
            os << matrix(i, j) << " ";
        os << std::endl;
    }

    return os;
}

#endif//SOLE2022_CSR_HPP
