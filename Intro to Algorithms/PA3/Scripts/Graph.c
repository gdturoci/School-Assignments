//Galen Turoci
//gturoci
//pa4

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

//Structs ---------------------------------------------------------------------

typedef struct GraphObj {
	List* neibrs;
	char* color;
	int* parent;
	int* dist;
	
	int verts;
	int edges;
	int source;
} GraphObj;


//Constructors-Destructors ----------------------------------------------------

//newGraph(int n)
//Returns a Graph pointing to a newly created GraphObj representing
//a graph having n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->neibrs = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(char));
	G->parent = calloc(n+1, sizeof(int));
	G->dist = calloc(n+1, sizeof(int));
	G->verts = n;
	G->edges = 0;
	G->source = NIL;
	
	for (int i = 1; i <= n; i++)
		G->neibrs[i] = newList();
	
	return(G);
}

//freeGraph(Graph* pG)
//Frees all dynamic memory associated with the Graph *pG, then sets *pG to NULL
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		while (getSize(*pG) > 0)
			makeNull(*pG);
		free(*pG);
		*pG = NULL;
	}
}


//Access Functions ------------------------------------------------------------

//getOrder(Graph G)
//Return the number of vertices in G
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference.\n");
		exit(1);
	}
	
	return(G->verts);
}

//getSize(Graph G)
//Return the number of edges in G
int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph reference.\n");
		exit(1);
	}
	
	return(G->edges);
}

//getSource(Graph G)
//Returns the source vertex most recently used in BFS(),
//or NIL if BFS() has not been called
int getSource(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSource() on NULL Graph reference.\n");
		exit(1);
	}
	
	return(G->source);
}

//getParent(Graph G, int u)
//Returns the parent of vertex u in the Breadth-First tree created by BFS(),
//or NIL if BFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph reference.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be > 1 and < getOrder(G).\n");
		exit(1);
	}
	
	if (G->source != NIL)
		return(G->parent[u]);
	else
		return(NIL);
}

//getDist(Graph G, int u)
//Returns the dist from the most recent BFS source to vertex u,
//or INF if BFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph reference.\n");
		exit(1);
	}
	
	if (G->source != NIL)
		return(G->dist[u]);
	else
		return(INF);
}

//getPath(List L, Graph G, int u)
//Appends to the List L the vertices of a shortest path in G from source to u,
//or appends to L the value NIL if no such path exists.
//Pre: getSource(G) != NIL && 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getPath() on NULL Graph reference.\n");
		exit(1);
	} if (L == NULL) {
		printf("Graph Error: calling getPath() on NULL List reference.\n");
		exit(1);
	} if (getSource(G) == NIL) {
		printf("Graph Error: getSource(G) is NIL.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be >= 1 and <= getOrder(G).\n");
		exit(1);
	}
	
	int s = G->source;
	if (s == u)
		append(L, s);
	else if (getParent(G, u) == NIL)
		append(L, NIL);
	else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
}


//Manipulation procedures -----------------------------------------------------

//makeNull(Graph G)
//Deletes all edges of G, restoring it to its original state
void makeNull(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling makeNull() on NULL Graph reference.\n");
		exit(1);
	}
	
	for (int i = 1; i <= getOrder(G); i++)
		clear(G->neibrs[i]);
	
	G->edges = 0;
}

//addEdge(Graph G, int u, int v)
//Inserts a new edge joing u to v
//i.e. u is added to the adjacency List of v, and v to the adjacency List of u
//Pre: 1 <= u && v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addEdge() on NULL Graph reference.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be > 1 and < getOrder(G).\n");
		exit(1);
	} if (1 > v || v > getOrder(G)) {
		printf("Graph Error: v must be > 1 and < getOrder(G).\n");
		exit(1);
	}
	
	if (length(G->neibrs[u]) != 0) {
		moveFront(G->neibrs[u]);
		while (v > get(G->neibrs[u]) && index(G->neibrs[u]) != length(G->neibrs[u])-1)
			moveNext(G->neibrs[u]);
		if (v < get(G->neibrs[u]))
			insertBefore(G->neibrs[u], v);
		else
			append(G->neibrs[u], v);
	} else
		append(G->neibrs[u], v);
	
	if (length(G->neibrs[v]) != 0) {
		moveFront(G->neibrs[v]);
		while (u > get(G->neibrs[v]) && index(G->neibrs[v]) != length(G->neibrs[v])-1)
			moveNext(G->neibrs[v]);
		if (u < get(G->neibrs[v]))
			insertBefore(G->neibrs[v], u);
		else
			append(G->neibrs[v], u);
	} else
		append(G->neibrs[v], u);
	
	G->edges++;
}

//addArc(Graph G, int u, int v)
//Inserts a new directed edge from u to v
//i.e. v is added to the adjacency List of u
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be > 1 and < getOrder(G).\n");
		exit(1);
	} if (1 > v || v > getOrder(G)) {
		printf("Graph Error: v must be > 1 and < getOrder(G).\n");
		exit(1);
	}
	
	if (length(G->neibrs[u]) != 0) {
		moveFront(G->neibrs[u]);
		while (v > get(G->neibrs[u]) && index(G->neibrs[u]) != length(G->neibrs[u])-1)
			moveNext(G->neibrs[u]);
		if (v < get(G->neibrs[u]))
			insertBefore(G->neibrs[u], v);
		else
			append(G->neibrs[u], v);
	} else
		append(G->neibrs[u], v);
	
	G->edges++;
}

//BFS(Graph G, int s)
//Runs the BFS algorithm on the Graph G with source s,
//setting the color, dist, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
	if (G == NULL) {
		printf("Graph Error: calling BFS() on NULL Graph reference.\n");
		exit(1);
	}
	
	G->source = s;
	
	//For every vert in G,
	//set the color to white,
	//the dist to INF,
	//and the parent to NIL.
	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] = 'w';
		G->dist[i] = INF;
		G->parent[i] = NIL;
	}
	
	//Start at the source
	G->color[s] = 'g';
	G->dist[s] = 0;
	
	//Create a Queue and start it up
	List Queue = newList();
	append(Queue, s); 
	
	//While the Queue isn't empty
	while (length(Queue) != 0) { 
		int u = front(Queue);
		deleteFront(Queue);
		moveFront(G->neibrs[u]);
		while (index(G->neibrs[u]) > -1) {
			int v = get(G->neibrs[u]);
			if (G->color[v] == 'w') {
				G->color[v] = 'g';
				G->dist[v] = G->dist[u]+1;
				G->parent[v] = u;
				append(Queue, v);
			}
			moveNext(G->neibrs[u]);
		}
		G->color[u] = 'b';
	}
}


//Other ops -------------------------------------------------------------------

//printGraph(FILE* out, Graph G)
//Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on NULL Graph reference.\n");
		exit(1);
	}
	
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->neibrs[i]);
	}
	fprintf(out, "\n");
}