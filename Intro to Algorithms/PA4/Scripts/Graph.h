//Galen Turoci
//CMPS101
//PA4

//Graph.h
//A header for the Graph ADT

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

#define NIL 0
#define UNDEF -1

//Exported Type
typedef struct GraphObj* Graph;


//Constructors-Destructors ----------------------------------------------------

//Returns a Graph pointing to a newly created GraphObj representing
//a graph having n vertices and no edges
Graph newGraph(int n);

//Frees all dynamic memory associated with the Graph *pG, then sets *pG to NULL
void freeGraph(Graph* pG);


//Access Functions ------------------------------------------------------------

//Return the corresponding field values
int getOrder(Graph G);
int getSize(Graph G);

//Returns the parent of vertex u in the Depth-First forest created by DFS(),
//or NIL if DFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

//Returns the discover time of vertex u in the Depth-First forest created by
//DFS(), or UNDEF if DFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

//Returns the finish time of vertex u in the Depth-First forest created by
//DFS(), or UNDEF if DFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);


//Manipulation procedures -----------------------------------------------------

//Inserts a new directed edge from u to v
//i.e. v is added to the adjacency List of u
//Pre: 1 <= u/v <= getOrder(G)
void addArc(Graph G, int u, int v);

//Inserts a new edge joing u to v
//i.e. u is added to the adjacency List of v, and v to the adjacency List of u
//Pre: 1 <= u/v <= getOrder(G)
void addEdge(Graph G, int u, int v);

//Runs the depth-first search algorithm on G.
//S defines the order in which vertices will be processed in the main DFS loop,
//and, when DFS is complete, it will store the vertices in order of decreasing
//finish times
//Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);


//Other ops -------------------------------------------------------------------

//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

//Returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G);

//Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif