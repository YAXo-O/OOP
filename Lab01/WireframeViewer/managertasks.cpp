#include <cstring>
#include "commands.h"
#include "wireframe.h"
#include "managertasks.h"
#include "meshreader.h"
#include "applytransforms.h"
#include "transformoperations.h"

int_std taskLoad(wireframe &model,const argument &arg)
{
    if(strlen(arg.fileName) == 0)  return status_invalid_arg_no_file;

    wireframe loaded = constructMesh();
    if(readMesh(loaded, arg.fileName) == read_failure)  return status_open_file_error;

    destroyMesh(model);
    model = loaded;

    return status_ok;
}

int_std taskTransform(const transformations &trans)
{
    updateMatrix(trans);

    return status_ok;
}

int_std taskClean(wireframe &model)
{
    destroyMesh(model);
    destroyMatrix(getMatrix());

    return status_ok;
}

int_std taskUnknown()
{
    return status_unknown_command;
}
