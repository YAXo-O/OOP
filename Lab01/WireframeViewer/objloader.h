#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "int_standart.h"
#include "wireframe.h"
#include "file.h"

int_std loadOBJ(wireframe &mesh, file_t &file);

#endif // OBJLOADER_H
