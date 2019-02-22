
/* 
 * Author: Surya Keswani 
 * Contact: sukeswan@ucsc.edu
 * School: University of California, Santa Cruz
 * Date: November 2018
 */

#ifndef GRAPH_H
#define GRAPH_H
#include "List.h"
#define INF -1
#define NIL 0 
#define white 0 
#define gray 1
#define black 2

typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif /* GRAPH_H */

