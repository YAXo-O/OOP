#include <cmath>
#include "point3d.h"

inline point3d addPointa(const point3d &a, const point3d &b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline point3d subPoints(const point3d &a, const point3d &b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

point3d reverse(const point3d &r)
{
    return {-r.x, -r.y, -r.z};
}

inline float len(const point3d &vec)
{
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

float vecAngle(const point3d &vec1, const point3d &vec2)
{
    return acos(scalarProduct(vec1, vec2)/(len(vec1)*len(vec2)));
}

inline float scalarProduct(const point3d &vec1, const point3d &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}
