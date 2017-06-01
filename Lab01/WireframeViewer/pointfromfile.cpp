#include <cmath>
#include "pointfromfile.h"
#include "getfloatregexp.h"

// Возращает действительное число, считанное в строке с данной позиции
// В случае, если считать такое число невозможно, в качестве позиции вернётся -1
float getFloat(int_std &pos, const char *str)
{
    floatInfo info = {0, 0, 0, true}; // intPart, fractionPart
    // fractonDigits, bPositive

    int_std state = 0;
    while(state != finalState && state != errorState)
        switch(state)
        {
        case initState:
            state = processInitStateFloat(info, pos, str);
            break;

        case signAquiredState:
            state = processSignAquiredStateFloat(info, pos, str);
            break;

        case getIntState:
            state = processGetIntStateFloat(info, pos, str);
            break;

        case getFractionFirstDigState:
            state = processGetFractionFirstDigStateFloat(info, pos, str);
            break;

        case getFractionState:
            state = processGetFractionStateFloat(info, pos, str);
            break;
        }

    if(state == errorState)
        return 0;

    info.fractionPart /= pow(10, info.fractionDigits);
    float number = info.intPart + info.fractionPart;
    if(!info.bPositive)
        number *= -1;

    return number;
}

// Возвращает точку, координаты которой записаны в строке как три подряд идущих действительных числа
// В случае, если считать точку невозможно (некорректные данные в строке), позиция указателя меняется на -1
point3d getPoint(int_std &pos, const char *line)
{
    point3d pp = {3, 3, 3};
    pp.x = getFloat(pos, line);
    if(pos == -1)
        return pp;

    pp.y = getFloat(pos, line);
    if(pos == -1)
        return pp;

    pp.z = getFloat(pos, line);

    return pp;
}
