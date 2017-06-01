#ifndef POINTS3D_H
#define POINTS3D_H

struct point3d
{
    float x,y,z;
};

inline point3d addPoints(const point3d &a, const point3d &b);
inline point3d subPoints(const point3d &a, const point3d &b);
point3d reverse(const point3d &r);

inline float len(const point3d &vec);
inline float vecAngle(const point3d &vec1, const point3d &vec2);
inline float scalarProduct(const point3d &vec1, const point3d &vec2);

#endif // POINTS3D_H
