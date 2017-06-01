#include "wireframe.h"

wireframe constructMesh()
{
    wireframe mesh;

    mesh.edgeArr = constructVector<edge>();
    mesh.points = constructVector<point3d>();

    return mesh;
}

void destroyMesh(wireframe &mesh)
{
    destroyVector(mesh.edgeArr);
    destroyVector(mesh.points);
}

size_t vertCount(wireframe &mesh)
{
    return count(mesh.points);
}

size_t edgeCount(wireframe &mesh)
{
    return count(mesh.edgeArr);
}

void addVert(wireframe &mesh, const point3d &vert)
{
    push_back(mesh.points, vert);
}

void addEdge(wireframe &mesh, const edge &e)
{
    push_back(mesh.edgeArr, e);
}

