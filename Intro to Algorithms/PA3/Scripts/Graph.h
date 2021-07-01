//Galen Turoci
//CMPS101
//PA4

//Graph.h
//A header for the Graph ADT

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

#define NIL 0
#define INF -1

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

//Returns the source vertex most recently used in BFS(),
//or NIL if BFS() has not been called
int getSource(Graph G);

//Returns the parent of vertex u in the Breadth-First tree created by BFS(),
//or NIL if BFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

//Returns the distance from the most recent BFS source to vertex u,
//or INF if BFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

//Appends to the List L the vertices of a shortest path in G from source to u,
//or appends to L the value NIL if no such path exists.
//Pre: getSource(G) != NIL && 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);


//Manipulation procedures -----------------------------------------------------

//Deletes all edges of G, restoring it to its original state
void makeNull(Graph G);

//Inserts a new edge joing u to v
//i.e. u is added to the adjacency List of v, and v to the adjacency List of u
//Pre: 1 < u && v <(=?) getOrder(G)
void addEdge(Graph G, int u, int v);

//Inserts a new directed edge from u to v
//i.e. v is added to the adjacency List of u
void addArc(Graph G, int u, int v);

//Runs the BFS algorithm on the Graph G with source s,
//setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);


//Other ops -------------------------------------------------------------------

//Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif