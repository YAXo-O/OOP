#ifndef TRANSFORMOPERATIONS_H
#define TRANSFORMOPERATIONS_H

#include "matrix.h"
#include "transformations.h"

// Эти функции производят действия над матрицей трансформаций
matrix &getMatrix();
void move(const transformations &trans);
void rotX(const transformations &trans);
void rotY(const transformations &trans);
void rotZ(const transformations &trans);
void scale(const  transformations &trans);
void shift(const point3d &shift_rate);


#endif // TRANSFORMOPERATIONS_H
