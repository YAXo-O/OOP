#include <iostream>
#include "matrix.h"

matrix constructMatrix(size_t rows, size_t cols)
{
    matrix m;

    m.cols = cols;
    m.rows = rows;

    m.data = new float[cols*rows];
    if(!m.data)
        m.rows = m.cols = 0;

    return m;
}

void destroyMatrix(matrix &m)
{
    delete[] m.data;
    m.data = nullptr;
    m.cols = m.rows = 0;
}

float &at(const matrix &m, size_t row, size_t col)
{
    return m.data[row*m.cols + col];
}

float get(const matrix &m, size_t row, size_t col)
{
    return m.data[row*m.cols + col];
}

matrix addMatrix(matrix a, const matrix &b)
{
    for(size_t i = 0; i < a.rows*a.cols; i++)
        a.data[i] += b.data[i];

    return a;
}

matrix multiplyMatrix(const matrix &a, const matrix &b)
{
    matrix c = constructMatrix(a.rows, b.cols);
    setMatrix(c, 0);

    for(size_t i = 0; i < a.rows; i++)
        for(size_t j = 0; j < b.cols; j++)
            for(size_t r = 0; r < a.cols; r++)
                at(c, i, j) += get(a, i, r)*get(b, r, j);

    return c;
}

matrix scalarMultipy(matrix a, float scalar)
{
    for(size_t i = 0; i < a.rows*a.cols; i++)
        a.data[i] *= scalar;

    return a;
}

void equalize(matrix &a, matrix &b)
{

    delete[] a.data;
    a.cols = b.cols;
    a.rows = b.rows;
    a.data = new float[a.cols*a.rows];
    std::copy(b.data, b.data + b.cols*b.rows, a.data);
}

void loadIdentity(matrix &a)
{
    for(size_t i = 0; i < a.rows; i++)
        for(size_t j = 0; j < a.cols; j++)
        {
            if(i == j)
                at(a, i, j) = 1;
            else
                at(a, i, j) = 0;
        }
}

void setMatrix(matrix &a, float fill)
{
    if(a.data == nullptr)
        return;

    for(size_t i = 0; i < a.rows*a.cols; i++)
        a.data[i] = fill;
}

void swap(matrix &a, matrix &b)
{
    float *data = a.data;
    a.data = b.data;
    b.data = data;

    size_t row = a.rows;
    a.rows = b.rows;
    b.rows = row;

    size_t col = a.cols;
    a.cols = b.cols;
    b.cols = col;
}

matrix initIdentity()
{
    matrix m = constructMatrix();
    loadIdentity(m);

    return m;
}
