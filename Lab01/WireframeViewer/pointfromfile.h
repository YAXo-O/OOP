#ifndef POINTFROMFILE_H
#define POINTFROMFILE_H

#include "point3d.h"
#include "int_standart.h"

float getFloat(int_std &pos, const char *str);
point3d getPoint(int_std &pos, const char *line);

#endif // POINTFROMFILE_H
