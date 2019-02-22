
/* 
 * Author: Surya Keswani 
 * Contact: sukeswan@ucsc.edu
 * School: University of California, Santa Cruz
 * Date: November 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
//#include "List.h" 
#define INF -1
#define NIL 0 
#define white 0 
#define gray 1
#define black 2

typedef struct GraphObj {
    // initialize everything you will need for a Graph Object
    List* adj;
    int* color;
    int* parent;
    int* dist;
    int vertices;
    int edges;
    int source;
} GraphObj;

/*** Constructors/De-constructors ***/
Graph newGraph(int n) {

    // allocate dynamic memory for the graph fields
    Graph graph = malloc(sizeof (GraphObj));
    graph->adj = calloc(n + 1, sizeof (List));
    graph->color = calloc(n + 1, sizeof (int));
    graph->parent = calloc(n + 1, sizeof (int));
    graph->dist = calloc(n + 1, sizeof (int));

    graph->vertices = n;
    graph->edges = 0;
    graph->source = NIL;

    // set all the values for the fields; 
    for (int i = 1; i < n + 1; i++) {
        graph->adj[i] = newList();
        graph->color[i] = white;
        graph->dist[i] = INF;
        graph->parent[i] = NIL;
    }

    return graph;

}
// frees all memory associated with graph object

void freeGraph(Graph* pG) {
    // if the pointer or the actual graph object are not null
    if (pG != NULL && *pG != NULL) {
        // free all the lists in the adjacency matrix
        for (int i = 0; i <= (*pG)->vertices; i++) {
            // dereference the pointer
            freeList(&((*pG)->adj[i]));
        }
        // free all other fields
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->dist);
        free((*pG)->parent);
        // free the pointer and set it to null
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
//returns # of vertices in the graph

int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph Error: getOrder() called on NULL Graph");
        exit(1);
    }
    return G->vertices;
}
// returns # of edges in the graph

int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph Error: getSize() called on NULL Graph");
        exit(1);
    }
    return G->edges;
}
// returns the most recent BFS source vertex

int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph Error: getSource() called on NULL Graph");
        exit(1);
    }
    return G->source;
}
// returns the parent of vertex u

int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: getParent() called on NULL Graph");
        exit(1);
    }
    if (u < 1) {
        printf("Graph Error: getParent() u less than 1 ");
        exit(1);
    }
    if (getOrder(G) < u) {
        printf("Graph Error: getParent() u greater than graph order ");
        exit(1);
    }
    // return the parent at u 
    return G->parent[u];
}
// returns the distance from most recent BFS source vertex to vertex u 

int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: getDist() called on NULL Graph");
        exit(1);
    }
    if (u < 1) {
        printf("Graph Error: getDist() u less than 1 ");
        exit(1);
    }
    if (getOrder(G) < u) {
        printf("Graph Error: getDist() u greater than graph order ");
        exit(1);
    }
    // return the distance at u 
    return G->dist[u];
}
// returns BFS path from source vertex of G to vertex u

void getPath(List L, Graph G, int u) {
    if (u < 1) {
        printf("Graph Error: getPath() u less than 1 ");
        exit(1);
    }
    if (getOrder(G) < u) {
        printf("Graph Error: getPath() u greater than graph order ");
        exit(1);
    }
    if (getSource(G) == NIL) {
        printf("Graph Error: getPath called without BFS being run");
    }
    if (G == NULL) {
        printf("Graph Error: gerPath() called on NULL Graph");
        exit(1);
    }
    if(G->source == u){
        append(L,u); 
    }
    // if the distance from u to the source vertex is infinity return nil list
    else if (G->dist[u] == INF) {
        append(L, NIL);
    }
    else {
        // append the first vertex
        append(L, u);
        //set current to the parent
        int current = G->parent[u];
        // while the current parents is not equal to source
        while (current != G->source) {
            prepend(L, current);
            current = G->parent[current];
        }
        prepend(L, G->source);
    }
}

/*** Manipulation procedures ***/
// resets graph to original state

void makeNull(Graph G) {
    if (G == NULL) {
        printf("Graph Error: makeNull() called on NULL Graph");
        exit(1);
    }
    // clear each list and set the edges to be 0
    for (int i = 1; i < getOrder(G) + 1; i++) {
        clear(G->adj[i]);
    }
    //set edges to be 0
    G->edges = 0;
}
// adds u-v edges to the graph

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: addEdge() called on NULL Graph");
        exit(1);
    }
    if (u < 1) {
        printf("Graph Error: addEdge() u less than 1 ");
        exit(1);
    }
    if (getOrder(G) < u) {
        printf("Graph Error: addEdge() u greater than graph order ");
        exit(1);
    }
    if (v < 1) {
        printf("Graph Error: addEdge() v less than 1 ");
        exit(1);
    }
    if (getOrder(G) < v) {
        printf("Graph Error: addEdge() v greater than graph order ");
        exit(1);
    }
    // an edge is just an arc in both directions
    // add arc in both directions to act as an edge
    addArc(G, u, v);
    addArc(G, v, u);
    // decrease the edges by one since arc will increase by 2
    G->edges--;
}
// adds arc u->v

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: addArc() called on NULL Graph");
        exit(1);
    }
    if (u < 1) {
        printf("Graph Error: addArc() u less than 1 ");
        exit(1);
    }
    if (getOrder(G) < u) {
        printf("Graph Error: addArc() u greater than graph order ");
        exit(1);
    }
    if (v < 1) {
        printf("Graph Error: addArc() v less than 1 ");
        exit(1);
    }
    if (getOrder(G) < v) {
        printf("Graph Error: addArc() v greater than graph order ");
        exit(1);
    }
    // get u adjacency list
    List uList = G->adj[u];
    //if the adjacency list at u is empty just add v 
    if (length(uList) == 0) {
        append(uList, v);
    } else {
        // move cursor to the front
        moveFront(uList);
        // iterate through the u list putting v in vertex sorted order
        for (int i = 0; i < length(uList); i++) {
            // otherwise look where v is smaller
            if (get(uList) < v) {
                moveNext(uList);
            } else {
                insertBefore(uList, v);
                break;
            }
        }
        if (back(uList) < v) {
            append(uList, v);
        }
    }
    // increase edges by 1
    G->edges++;
}
// runs Breadth First Search algorithm on graph g with source vertex s

void BFS(Graph G, int s) {
    // set G source to be s
    G->source = s;
    // iterate through all the vertices
    for (int i = 1; i <= G->vertices; i++) {
        // set the color to be white
        G->color[i] = white;
        // set the distance from the source to be infinity
        G->dist[i] = INF;
        // set the parent to be nil
        G->parent[i] = NIL;
        // move the cursor to the front of each adjacency list
        if (length(G->adj[i]) > 0) {
            moveFront(G->adj[i]);
        }
    }
    //set source color to be gray
    G->color[s] = gray;
    // set distance to be 0 for source
    G->dist[s] = 0;
    // create a queue using the list adt from pa2
    List queue = newList();
    // add the source vertex to the queue
    append(queue, s);
    int currentVertex;
    // while the queue is not empty
    while (length(queue) != 0) {
        //current vertex is whatever is at the front of the queue
        currentVertex = front(queue);
        // delete the front to replicate what dequeue would do
        deleteFront(queue);
        // iterate through the adjacency list if the currentVertex
        for (int j = 1; j <= length(G->adj[currentVertex]); j++) {
            int currentAdjV = get(G->adj[currentVertex]);
            // if the color of the current adjacency vertex is white
            if (G->color[currentAdjV] == white) {
                // set the color to gray
                G->color[currentAdjV] = gray;
                // set the distance to be the current vertex distance plus 1
                G->dist[currentAdjV] = (G->dist[currentVertex]) + 1;
                // set the parent to be the currentVertex
                G->parent[currentAdjV] = currentVertex;
                // append the current adjacency vertex (enqueue)
                append(queue, currentAdjV);
            }
            // move cursor to the next adjacency vertex
            moveNext(G->adj[currentVertex]);
        }
        // set color of current vertex to be black
        G->color[currentVertex] = black;
    }
    // free the list memory 
    freeList(&queue);
}

/*** Other operations ***/
// prints the adjacency matrix of graph G to file out

void printGraph(FILE* out, Graph G) {
    // iterate through the adjacency matrix
    for (int i = 1; i <= G->vertices; i++) {
        List current = G->adj[i];
        // print the vertex
        fprintf(out, "%d: ", i);
        // print the adjacency list for that vertex
        printList(out, current);
        //print a new line
        fprintf(out, "\n");
    }
}
