#include "graph.h"

graph constructGraph()
{
    graph g;
    g.edges = constructVector<edge>();
    g.verts = constructVector<point2d>();

    return g;
}

void destroyGraph(graph &g)
{
    destroyVector(g.edges);
    destroyVector(g.verts);
}

size_t vertCountG(const graph &g)
{
    return g.verts.size;
}

size_t edgeCountG(const graph &g)
{
    return g.edges.size;
}

void addVertG(graph &g, const point2d &vert)
{
    push_back(g.verts, vert);
}

void addEdgeG(graph &g, const edge &e)
{
    push_back(g.edges, e);
}
