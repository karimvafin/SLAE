
#include "../sem_1/src/project/dense/densematrix.hpp"

template<typename T>
void GivensRotation(DenseMatrix<T>& A, std::vector<T>& b)
{
    T sin, cos;
    T upper, lower;
    T b_upper, b_lower;
    for(size_t i = 0; i < A.sizeW(); ++i)
    {
        cos = A(i, i) / sqrt(A(i, i) * A(i, i) + A(i + 1, i) * A(i + 1), i));
        sin = A(i + 1, i) / sqrt(A(i, i) * A(i , i) + A(i + 1, i) * A(i + 1, i));
        b_upper = cos * b[i] + sin * b[i + 1];
        b_lower = - sin * b[i] + cos * b[i + 1];
        b[i] = b_upper;
        b[i + 1] = b_lower;
        
        for(size_t j = 0; j < A.sizeW(); ++j)
        {
            upper = cos * A(i, j) + sin * A(i + 1, j);
            lower = - sin * A(i, j) + cos * A(i + 1, j);
            if(Tabs(lower) < tolerance<T>)
                lower = 0;
            A(i, j) = upper;
            A(i + 1, j) = lower;
        }
    }
}