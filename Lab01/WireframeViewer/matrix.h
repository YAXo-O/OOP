#ifndef Matrix_H
#define Matrix_H

#include "int_standart.h"

struct matrix
{
    size_t rows = 4, cols = 4;
    float *data = nullptr;
};

matrix constructMatrix(size_t rows = 4, size_t cols = 4);
void destroyMatrix(matrix &m);

float &at(const matrix &m, size_t row, size_t col);
float get(const matrix &m, size_t row, size_t col);
void equalize(matrix &a, matrix &b);
void swap(matrix &a, matrix &b);

void loadIdentity(matrix &a);
matrix initIdentity();
void setMatrix(matrix &a, float fill);

matrix addMatrix(matrix a, const matrix &b);
matrix multiplyMatrix(const matrix &a, const matrix &b);
matrix scalarMultipy(matrix &a, float scalar);

#endif // Matrix_H
