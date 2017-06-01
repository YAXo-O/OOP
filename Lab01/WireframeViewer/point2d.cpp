#include <cmath>
#include "point2d.h"


inline point2d addPoints(const point2d &a, const point2d &b)
{    
    return {a.x + b.x, a.y + b.y};
}

inline point2d subPoints(const point2d &a, const point2d &b)
{
    return {a.x - b.x, a.y - b.y};
}

point2d reverse(const point2d &r)
{
    return {-r.x, -r.y};
}

inline float len(const point2d &vec)
{
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

inline float vecAngle(const point2d &vec1, const point2d &vec2)
{
    return acos(scalarProduct(vec1, vec2)/(len(vec1)*len(vec2)));
}

inline float scalarProduct(const point2d &vec1, const point2d &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y;
}
