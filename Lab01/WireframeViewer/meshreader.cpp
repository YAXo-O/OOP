#include "meshreader.h"
#include "file.h"
#include "objloader.h"

int_std readMesh(wireframe &mesh, const char *file)
{
    file_t in;
    int_std code = read_failure;

    if(openFile(in, file, "r"))
    {
        code = loadOBJ(mesh, in);

        closeFile(in);
    }

    return code;
}
