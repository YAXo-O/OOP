#include "applytransforms.h"
#include "transformoperations.h"

point3d transform(point3d p)
{
    matrix coordMatrix = constructMatrix(1, 4);

    at(coordMatrix, 0, 0) = p.x;
    at(coordMatrix, 0, 1) = p.y;
    at(coordMatrix, 0, 2) = p.z;
    at(coordMatrix, 0, 3) = 1;

    matrix tmp = multiplyMatrix(coordMatrix, getMatrix());
    destroyMatrix(coordMatrix);

    p.x = at(tmp, 0, 0);
    p.y = at(tmp, 0, 1);
    p.z = at(tmp, 0, 2);

    destroyMatrix(tmp);

    return p;
}


void updateMatrix(const transformations &trans)
{

    if(trans.bReset)
        loadIdentity(getMatrix());

    if(trans.bMove)
        move(trans);
    if(trans.bRotate)
    {
        if(trans.dtx)
            rotX(trans);
        if(trans.dty)
            rotY(trans);
        if(trans.dtz)
            rotZ(trans);
    }
    if(trans.bScale)
        scale(trans);
}
