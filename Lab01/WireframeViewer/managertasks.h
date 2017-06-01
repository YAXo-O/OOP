#ifndef MANAGERTASKS_H
#define MANAGERTASKS_H

#include "int_standart.h"
#include "commands.h"
#include "wireframe.h"

int_std taskLoad(wireframe &model, const argument &arg);
int_std taskTransform(const transformations &trans);
int_std taskClean(wireframe &model);
int_std taskUnknown();

#endif // MANAGERTASKS_H
