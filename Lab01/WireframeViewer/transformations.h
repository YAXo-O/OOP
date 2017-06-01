#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <cmath>
#include "point3d.h"
#include "matrix.h"

const float degToRad = M_PI/180;

struct transformations
{
    bool bReset; // Сбросить все трансформации?

    float dx, dy, dz; // Смещение
    bool bMove;

    float dtx, dty, dtz; // Углы поворота, в радианах
    bool bRotate;

    float sx, sy, sz; // Коэффициенты масштабирования
    bool bScale;

    point3d pivotPoint; // Опорная точка - относительно неё вращение и масштабирование
};


void resetTransforms(transformations &tr);
void resetButPivot(transformations &tr); // Сбросить всё кроме опорной точки

#endif // TRANSFORMATIONS_H
