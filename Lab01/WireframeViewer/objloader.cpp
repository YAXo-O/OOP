#include "objloader.h"
#include "returncodes.h"
#include "pointfromfile.h"
#include "linemanagment.h"
#include "objparser.h"

int_std loadOBJ(wireframe &mesh, file_t &in)
{
    int_std code = read_ok;


    for(char *line; (line = getLine(in)) != nullptr && code == read_ok;)
    {
        code = parseOBJ(mesh, line);

        clearLine(line);
    }

    return code;
}
