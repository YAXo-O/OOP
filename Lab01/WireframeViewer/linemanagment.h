#ifndef LINEMANAGMENT_H
#define LINEMANAGMENT_H

#include "file.h"

char *getLine(file_t &f);
char *resize(char *str, size_t oldSize,  size_t newSize);

void clearLine(char *&str);

#endif // LINEMANAGMENT_H
