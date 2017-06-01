#include "objloadregexp.h"
#include "pointfromfile.h"
#include "linemanagment.h"

int_std processInitState(int_std &i, const char *line)
{
    if(line[i] == '#')
        return finalState;

    if(line[i] == ' ' || line[i] == '\t')
    {
        i++;
        return initState;
    }

    if(line[i] == 'v')
    {
        i++;
        return vertState;
    }

    if(line[i] == 'f')
    {
        i++;
        return edgeState;
    }

    if(line[i] == '\0' || line[i] == '\n')
        return finalState;

    if(line[i] == 'g')
        return finalState;

    return errorState;
}

int_std processVertState(wireframe &mesh, int_std &i, const char *line)
{
    if(line[i] == ' ' || line[i] == '\t')
    {
        i++;
        return vertState;
    }

    if(line[i] == 'p')
        return finalState;

    addVert(mesh, getPoint(i, line));

    return finalState;
}

int_std processEdgeState(wireframe &mesh, int_std &i, const char *line)
{
    size_t first, prev;
    first = prev = getFloat(i, line)-1;
    size_t cur = getFloat(i, line)-1;
    int_std state = finalState;

    while(i != -1)
    {
        if(prev >= vertCount(mesh) || cur >= vertCount(mesh))
        {
            i = -1;
            state = errorState;
        }
        else
        {
            edge e = {prev, cur};
            addEdge(mesh, e);
            prev = cur;
            cur = getFloat(i, line)-1;
        }
    }

    if(state == finalState)
    {
        edge e = {first, prev};
        addEdge(mesh, e);
    }

    return state;
}
