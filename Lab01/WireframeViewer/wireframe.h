#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "point3d.h"
#include "edge.h"
#include "vector.h"

typedef vector<point3d> point3dVec;
typedef vector<edge> edgeVec;

struct wireframe
{
    point3dVec points;
    edgeVec edgeArr;
};

wireframe constructMesh();
void destroyMesh(wireframe &mesh);

size_t vertCount(wireframe &mesh);
size_t edgeCount(wireframe &mesh);
void addVert(wireframe &mesh, const point3d &vert);
void addEdge(wireframe &mesh, const edge &e);


#endif // WIREFRAME_H
