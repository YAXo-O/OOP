#ifndef POINT2D_H
#define POINT2D_H

struct point2d
{
    float x, y;
};

inline point2d addPoints(const point2d &a, const point2d &b);
inline point2d subPoints(const point2d &a, const point2d &b);
point2d reverse(const point2d &r);

inline float len(const point2d &vec);
inline float vecAngle(const point2d &vec1, const point2d &vec2);
inline float scalarProduct(const point2d &vec1, const point2d &vec2);

#endif // POINT2D_H
