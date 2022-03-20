#include "project/dense/densematrix.hpp"
#include "project/utility/overloads.hpp"
#include <project/utility/Norm.hpp>
#include <cmath>
#include <iostream>

int cron(int i, int j) {
    if (i != j)
        return 0;
    else
        return 1;
}

template<typename T>
std::pair<DenseMatrix<T>, DenseMatrix<T>> QR_decomposition_Householder(const DenseMatrix<T> &A) {
    int m = A.get_row_size();
    int n = A.get_col_size();

    std::vector<T> n_vec;
    std::vector<T> x_i(m);
    std::vector<T> e_i(m, 0);
    DenseMatrix<T> R(m, n);
    DenseMatrix<T> R_copy(m, n);
    DenseMatrix<T> Q_i(m, m);

    //Копируем А в R тут нужен копиконструктор
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            R(i, j) = A(i, j);
        }
    }

    //Q единичная(тут нужен конструктор единичных матриц
    DenseMatrix<T> Q(m, m, 0);
    DenseMatrix<T> Q_copy(m, m);
    for (int j = 0; j < m; ++j) {
        Q(j, j) = 1;
    }

    //Oдновременно получаем R и Q основной цикл
    for (int i = 0; i < n; ++i) {
        x_i = R.get_col(i);
        //понижаем размерность
        for (int k = 0; k < i; k++) {
            x_i.erase(x_i.begin());
        }
        //базисный вектор
        e_i[0] = static_cast<T>(1.);
        //вычисляем вектор нормали
        n_vec = x_i[0] / abs(x_i[0]) * norm(x_i, NormType::ThirdNorm) * e_i + x_i;

        //Заполняем матрицу Q_i
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                if (j >= i && k >= i) {
                    Q_i(j, k) = cron(j, k) - 2 / norm(n_vec, NormType::ThirdNorm) / norm(n_vec, NormType::ThirdNorm)
                                             * n_vec[j - i] * n_vec[k - i];
                } else if (j < i && k < i) {
                    Q_i(j, k) = cron(j, k);
                } else {
                    Q_i(j, k) = 0;
                }
            }
        }

        //R = Q_i * R;

        //Тут обязательно нужна копия R, подругому никак(опять нужен копиконструктор)
        for (int p = 0; p < m; p++) {
            for (int j = 0; j < n; j++) {
                R_copy(p, j) = R(p, j);
            }
        }
        //Если есть копия R, то можно ускорить перемножение вот так
        for (int j = i; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                R(j, k) = 0;
                for (int l = i; l < m; ++l) {
                    R(j, k) += Q_i(j, l) * R_copy(l, k);
                }
            }
        }


        //Q = Q * Q_i;

        //Тут обязательно нужна копия Q, подругому никак(опять нужен копиконструктор)
        for (int p = 0; p < m; p++) {
            for (int j = 0; j < m; j++) {
                Q_copy(p, j) = Q(p, j);
            }
        }
        //Если есть копия Q, то можно ускорить перемножение вот так
        for (int j = 0; j < m; ++j) {
            for (int k = i; k < m; ++k) {
                Q(j, k) = 0;
                for (int l = 0; l < m; ++l) {
                    Q(j, k) += Q_copy(j, l) * Q_i(l, k);
                }
            }
        }

        //понижаем размерность
        e_i.erase(e_i.begin());
    }
    std::pair<DenseMatrix<T>, DenseMatrix<T>> QR(Q, R);
    return QR;
}