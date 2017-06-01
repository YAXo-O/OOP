#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include "edge.h"
#include "point2d.h"

typedef vector<point2d> point2dVec;
typedef vector<edge> edgeVec;

struct graph
{
    point2dVec verts;
    edgeVec edges;
};

graph constructGraph();
void destroyGraph(graph &g);

size_t vertCountG(const graph &g);
size_t edgeCountG(const graph &g);
void addVertG(graph &g, const point2d &vert);
void addEdgeG(graph &g, const edge &e);

#endif // GRAPH_H
