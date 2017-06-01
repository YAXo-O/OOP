#ifndef OBJREADER_H
#define OBJREADER_H

#include "wireframe.h"
#include "returncodes.h"

int_std readMesh(wireframe &mesh, const char *file);

#endif // OBJREADER_H
