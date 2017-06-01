#ifndef APPLYTRANSFORMS_H
#define APPLYTRANSFORMS_H

#include "transformations.h"

point3d transform(point3d p); // Преобразует точку в вектор, домножает на матрицу трансформаций и возвращает новую точку

void updateMatrix(const transformations &trans);


#endif // APPLYTRANSFORMS_H
