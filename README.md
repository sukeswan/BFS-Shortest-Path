List.c: an Abstract Data Type that contains integers. The list acts as a bi-directional queue. There are different methods that allow the list of integers (stored in nodes) to be manipulated. There is also a cursor node that highlights a specific node. The cursor has an index which allows for iteration through the list. The cursor can be in the list or can be absent.

List.h: Header file for List.c

Graph.c: an Abstract Data Type that creates a graph struct. Struct can perform BFS search and find path from source to any vertex using BFS tree. 

Graph.h: Header file for Graph.c

FindPath.c: I/O file that takes in a graph knowing the number of edges, and the actual edges. FindPath then finds the path from x to y using x as the source to perform BFS and y ad the vertex on the BFS Tree. 

The input file should be formatted as such. The first line of the input file should be the integer n, representing the number of vertices of the graph. Each subsequent n lines of the input file should contain 2 integers separated by a space. The integers represent the end vertices of an edge of the graph. After all n edges have been entered the following line should contain “0 0”. This line acts as a null terminator letting the program know that all the edges of the graph have been inputted. After the null terminator line, the input file should contain any number of lines that each contain 2 vertices of the graph (range 1-n). The program will use the first vertex as a source and the second as a destination finding the shortest path between the 2 vertices. The input file should end with the last line being “0 0”. Example input and output files can be found in the repository. 

README: Table of contents 
