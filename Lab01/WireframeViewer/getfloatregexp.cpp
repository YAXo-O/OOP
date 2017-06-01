#include <cstring>
#include "getfloatregexp.h"

int_std processInitStateFloat(floatInfo &info, int_std &pos, const char *str)
{
    if(str[pos] == ' ' || str[pos] == '\t')
    {
        pos++;
        return initState;
    }

    if(str[pos] == '+' || str[pos] == '-')
    {
        if(str[pos] == '-')
            info.bPositive = false;

        pos++;
        return signAquiredState;
    }

    if(str[pos] >= '0' && str[pos] <= '9')
    {
        info.intPart *= 10;
        info.intPart += float(str[pos++] - '0');
        return getIntState;
    }
    if(str[pos] == '.' || str[pos] == ',')
    {
        pos++;
        return getFractionFirstDigState;
    }

    pos = -1;
    return errorState;
}

int_std processSignAquiredStateFloat(floatInfo &info, int_std &pos, const char *str)
{
    if(str[pos] >= '0' && str[pos] <= '9')
    {
        info.intPart *= 10;
        info.intPart += str[pos++] - '0';
        return getIntState;
    }

    if(str[pos] == '.' || str[pos] == ',')
    {
        pos++;
        return getFractionFirstDigState;
    }

    pos = -1;
    return errorState;
}

int_std processGetIntStateFloat(floatInfo &info, int_std &pos, const char *str)
{
    if(str[pos] >= '0' && str[pos] <= '9')
    {
        info.intPart *= 10;
        info.intPart += str[pos++] - '0';
        return getIntState;
    }

    if(str[pos] == '.' || str[pos] == ',')
    {
        pos++;
        return getFractionFirstDigState;
    }

    if(pos == int_std(strlen(str)) || str[pos] == '\n' || str[pos] == ' ' || str[pos] == '\t')
        return finalState;

    pos = -1;
    return errorState;
}

int_std processGetFractionFirstDigStateFloat(floatInfo &info, int_std &pos, const char *str)
{
    if(str[pos] >= '0' && str[pos] <= '9')
    {
        info.fractionPart *= 10;
        info.fractionPart += str[pos++] - '0';
        info.fractionDigits++;
        return getFractionState;
    }

    pos = -1;
    return errorState;
}

int_std processGetFractionStateFloat(floatInfo &info, int_std &pos, const char *str)
{
    if(str[pos] >= '0' && str[pos] <= '9')
    {
        info.fractionPart *= 10;
        info.fractionPart += str[pos++] - '0';
        info.fractionDigits++;
        return getFractionState;
    }

    if(pos == int_std(strlen(str)) || str[pos] == '\n' || str[pos] == ' ' || str[pos] == '\t')
        return finalState;

    pos = -1;
    return errorState;
}
