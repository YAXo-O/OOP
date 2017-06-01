#ifndef GETFLOATREGEXP_H
#define GETFLOATREGEXP_H

#include "int_standart.h"

// Состояния автомата
const int_std initState = 0;
const int_std signAquiredState = 1;
const int_std getIntState = 2;
const int_std getFractionFirstDigState = 3; // После десятичной точки(запятой) должна быть хотя бы одна цифра
                                        // Она в данном состоянии и считывается
const int_std getFractionState = 4; // Здесь может быть считаны все остальные цифры дробной части числа
const int_std finalState = 10;
const int_std errorState = 11;

struct floatInfo
{
    float intPart, fractionPart;
    size_t fractionDigits;
    bool bPositive;
};

int_std processInitStateFloat(floatInfo &info, int_std &id, const char *line);
int_std processSignAquiredStateFloat(floatInfo &info, int_std &id, const char *line);
int_std processGetIntStateFloat(floatInfo &info, int_std &id, const char *line);
int_std processGetFractionFirstDigStateFloat(floatInfo &info, int_std &id, const char *line);
int_std processGetFractionStateFloat(floatInfo &info, int_std &id, const char *line);

#endif // GETFLOATREGEXP_H
