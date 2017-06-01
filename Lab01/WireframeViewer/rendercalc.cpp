#include <cstring>
#include "rendercalc.h"
#include "meshreader.h"
#include "int_standart.h"
#include "managertasks.h"
#include "applytransforms.h"
#include "graphfrommesh.h"

int_std getGraph(graph &g, command c, const argument &arg)
{
    static wireframe model = constructMesh();

    int_std status = status_unknown_command;
    switch(c)
    {
    case c_open:
        status = taskLoad(model, arg);
        break;

    case c_transform:
        status = taskTransform(arg.trans);
        break;

    case c_clean:
        status = taskClean(model);
        break;

    default:
        status = taskUnknown();
        break;
    }

    if(c == c_open || c == c_transform)
        graphFromMesh(g, model);

    return status;
}
