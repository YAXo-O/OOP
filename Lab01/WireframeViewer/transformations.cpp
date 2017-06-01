#include "transformations.h"
#include "matrix.h"
#include "int_standart.h"

void resetTransforms(transformations &tr)
{
    resetButPivot(tr);
    tr.pivotPoint = {0, 0, 0};
}

void resetButPivot(transformations &tr)
{
    tr.dx = tr.dy = tr.dz = 0;
    tr.dtx = tr.dty = tr.dtz = 0;
    tr.sx = tr.sy = tr.sz = 1;
    tr.bMove = tr.bScale = tr.bRotate = false;
    tr.bReset = false;
}
