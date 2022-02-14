//
// Created by petrov on 12.02.2022.
//

#ifndef SOLE2022_CSR_HPP
#define SOLE2022_CSR_HPP

#include <vector>
#include <iosfwd>
#include <set>
#include "my_project/utility/Triplet.hpp"

template<typename T>
class CSR {
public:
    using elm_t = T;          // Тип данных элементов матрицы
    using idx_t = std::size_t;// Тип индекса

private:
    const idx_t H, W;         //Размеры матрицы
    std::vector<elm_t> values;//Вектор значений (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> cols;  // Вектор номеров столбцов, соответствующих значениям (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> rows;  // Вектор индексации строк размера H+1, первый элемент = 0 в качестве запирающего

public:
    /***
     * Конструктор разреженной матрицы по готовым векторам с внутренней структурой
     * @param h число строк
     * @param w число столбцов
     * @param v вектор ненулевых значений
     * @param c вектор индексации столбцов
     * @param r вектор индексации строк
     */
    CSR(const idx_t &h, const idx_t &w, const std::vector<T>& v,const std::vector<T>& c, const std::vector<T>& r): H(h), W(w)
    {
        values = v;
        cols = c;
        rows = r;
    }

    /***
     * Конструктор разреженной матрицы по сету из Triplet
     * @param h число строк
     * @param w число столбцов
     */
    CSR(const idx_t &h, const idx_t &w, const std::set<Triplet<elm_t>>& in): H(h), W(w)
    {
        values.resize(in.size());
        cols.resize(in.size());
        rows.resize(h + 1, 0);
        int countInRow = 0;
        int currRow = 0;
        auto it = in.begin();
        for (idx_t k = 0; k < in.size(); ++k)
        {
            while (currRow < it->i)
            {
                rows[currRow + 1] = rows[currRow] + countInRow;
                ++currRow;
                countInRow = 0;
            }
            values[k] = it->value;
            cols[k] = it->j;
            ++countInRow;
            it = std::next(it);
        }
        for (++currRow; currRow <= H; ++currRow)
        {
            rows[currRow] = in.size();
        }
    }

    /***
     * Оператор получения элемента матрицы по индексам
     * @param i Номер строки
     * @param j Номер столбца
     * @return Значение элемента в позиции (i, j)
     */
    const elm_t &operator()(idx_t const i, idx_t const j) const
    {
        // найти количество не нулей на данной строке
        // пропускаем количество элементов до этой строке
        // итерируемся и сравниваем столбец

        idx_t skip = this->rows[i];
        for (idx_t k = skip; k < this->rows[i + 1]; ++k)
        {
            if (this->cols[k] == j)
                return this->values[k];
        }
        return static_cast<elm_t>(0);
    }

    /***
     * Оператор умножения матрицы на вектор
     * @param b Вектор, на который умножается матрица
     * @return Вектор - результат перемножения
     */
    std::vector<elm_t> operator*(const std::vector<elm_t> &b) const
    {
        std::vector<elm_t> result(this->H);
        for (idx_t i = 0; i < H; ++i)
        {
            idx_t skip = this->rows[i];
            idx_t count = this->rows[i + 1] - skip;
            for (idx_t k = skip; k < skip + count; ++k)
            {
                result[i] += values[k] * b[cols[k]];
            }
        }

        return result;
    }

    [[nodiscard]] idx_t getW() const
    {
        return W;
    }

    [[nodiscard]] idx_t getH() const
    {
        return H;
    }
};

/***
 * Оператор умножения матрицы на вектор
 * @param b Вектор, на который умножается матрица
 * @return Вектор - результат перемножения
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const CSR<T> &A)
{
    for (int i = 0; i < A.getH(); ++i)
    {
        for (int j = 0; j < A.getW(); ++j)
            os << A(i, j) << " ";
        os << std::endl;
    }

    return os;
}

#endif//SOLE2022_CSR_HPP
