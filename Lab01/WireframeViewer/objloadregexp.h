#ifndef OBJLOADREGEXP_H
#define OBJLOADREGEXP_H

#include "int_standart.h"
#include "wireframe.h"

// Состояния автомата
const int_std initState = 0;
const int_std vertState = 1;
const int_std edgeState = 2;
const int_std finalState = 10;
const int_std errorState = 11;

int_std processInitState(int_std &id, const char *line);
int_std processVertState(wireframe &mesh, int_std &id, const char *line);
int_std processEdgeState(wireframe &mesh, int_std &id, const char *line);

#endif // OBJLOADREGEXP_H
