#include "transformoperations.h"

matrix &getMatrix()
{
    static matrix tMatrix = initIdentity();

    return tMatrix;
}

void move(const transformations &trans)
{
    matrix transform = constructMatrix();
    loadIdentity(transform);

    at(transform, 3, 0) = trans.dx;
    at(transform, 3, 1) = trans.dy;
    at(transform, 3, 2) = trans.dz;

    matrix tmp = multiplyMatrix(getMatrix(), transform);
    swap(getMatrix(), tmp);
    destroyMatrix(tmp);

    destroyMatrix(transform);
}

void rotX(const transformations &trans)
{
    shift(reverse(trans.pivotPoint));

    matrix transform = constructMatrix();
    loadIdentity(transform);

    float cosa = cos(trans.dtx);
    float sina = sin(trans.dtx);

    at(transform, 1, 1) = cosa;
    at(transform, 1, 2) = sina;
    at(transform, 2, 1) = -sina;
    at(transform, 2, 2) = cosa;

    matrix tmp = multiplyMatrix(getMatrix(), transform);
    swap(getMatrix(), tmp);
    destroyMatrix(transform);
    shift(trans.pivotPoint);

    destroyMatrix(tmp);
}

void rotY(const transformations &trans)
{
    shift(reverse(trans.pivotPoint));

    matrix transform = constructMatrix();
    loadIdentity(transform);

    float cosa = cos(trans.dty);
    float sina = sin(trans.dty);

    at(transform, 0, 0) = cosa;
    at(transform, 0, 2) = -sina;
    at(transform, 2, 0) = sina;
    at(transform, 2, 2) = cosa;

    matrix tmp = multiplyMatrix(getMatrix(), transform);
    swap(getMatrix(), tmp);
    destroyMatrix(transform);
    shift(trans.pivotPoint);

    destroyMatrix(tmp);
}

void rotZ(const transformations &trans)
{
    shift(reverse(trans.pivotPoint));

    matrix transform = constructMatrix();
    loadIdentity(transform);

    float cosa = cos(trans.dtz);
    float sina = sin(trans.dtz);

    at(transform, 0, 0) = cosa;
    at(transform, 0, 1) = sina;
    at(transform, 1, 0) = -sina;
    at(transform, 1, 1) = cosa;

    matrix tmp = multiplyMatrix(getMatrix(), transform);
    swap(getMatrix(), tmp);
    destroyMatrix(transform);
    shift(trans.pivotPoint);

    destroyMatrix(tmp);
}

void scale(const transformations &trans)
{
    shift(reverse(trans.pivotPoint));

    matrix transform = constructMatrix();
    loadIdentity(transform);

    at(transform, 0, 0) = trans.sx;
    at(transform, 1, 1) = trans.sy;
    at(transform, 2, 2) = trans.sz;

    matrix tmp = multiplyMatrix(getMatrix(), transform);
    swap(getMatrix(), tmp);
    destroyMatrix(transform);
    shift(trans.pivotPoint);

    destroyMatrix(tmp);
}

// shift сдвигает на вектор для поворота/масштабирования
void shift(const point3d &shift_vec)
{
    transformations tr;
    tr.dx = shift_vec.x;
    tr.dy = shift_vec.y;
    tr.dz = shift_vec.z;

    move(tr);
}
