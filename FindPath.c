
/* 
 * Author: Surya Keswani 
 * Contact: sukeswan@ucsc.edu
 * School: University of California, Santa Cruz
 * Date: November 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

/*
 * 
 */
int main(int argc, char** argv) {

    FILE *in, *out;

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    // check to make sure files can be accessed
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // the size of the graph 
    int n;
    // use fscanf to get the size  of the graph and make a graph that size
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    // the two vertices that make and edge are read from the file
    int x;
    fscanf(in, "%d", &x);
    int y;
    fscanf(in, "%d", &y);

    // while the vertices are not both 0 add an edge to the graph
    while (x != 0 && y != 0) {
        addEdge(G, x, y);
        fscanf(in, "%d", &x);
        fscanf(in, "%d", &y);
    }

    // print the graph once all the edges have been built
    printGraph(out, G);

    // now x will be the source and y will be the vertex to find the path from
    fscanf(in, "%d", &x);
    fscanf(in, "%d", &y);

    //this list will store the path you find
    List L = newList();
    while (x != 0 && y != 0) {
        BFS(G, x);
        getPath(L, G, y);
        // if the distance is infinity 
        if (getDist(G,y) == -1) {
            fprintf(out, "The distance from %d to %d is infinity\n", x, y);
            fprintf(out, "No %d-%d path exists\n", x, y);
            fprintf(out, "\n");
        }            // a path exists so print it out
        else {
            fprintf(out, "The distance from %d to %d is %d\n", x, y, getDist(G,y));
            fprintf(out, "A shortest %d-%d path is: ", x, y);
            printList(out, L);
            fprintf(out, "\n");

        }
        // scan the next x an y and clear the list for the new path
        fscanf(in, "%d", &x);
        fscanf(in, "%d", &y);
        clear(L);

    }

    //close the files and free the graph; 
    fclose(in);
    fclose(out);
    freeGraph(&G);
    freeList(&L);
    return (EXIT_SUCCESS);
}

