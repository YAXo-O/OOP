#include "objparser.h"
#include "returncodes.h"
#include "objloadregexp.h"

int_std parseOBJ(wireframe &mesh, char *line)
{
    int_std i = 0;
    size_t state = initState;

    while(state != finalState && state != errorState)
        switch(state)
        {
        case initState:
            state = processInitState(i, line);
            break;

        case vertState:
            state = processVertState(mesh, i, line);
            break;

        case edgeState:
            state = processEdgeState(mesh, i, line);
            break;
        }

    if(state == errorState)
    {
        destroyMesh(mesh);
        return read_failure;
    }
    else
        return read_ok;
}
