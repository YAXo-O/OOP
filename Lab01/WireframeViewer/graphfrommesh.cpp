#include "graphfrommesh.h"
#include "applytransforms.h"
#include "project.h"

void graphFromMesh(graph &g, wireframe &mesh)
{
    for(size_t i = 0; i < vertCount(mesh); i++)
        //point3d m_point = transform(mesh.points.data[i]);
        //push_back(g.verts, project(m_point));
        addVertG(g, project(transform(mesh.points.data[i])));
    for(size_t i = 0; i < edgeCount(mesh); i++)
        //push_back(g.edges, mesh.edgeArr.data[i]);
        addEdgeG(g, mesh.edgeArr.data[i]);
}
