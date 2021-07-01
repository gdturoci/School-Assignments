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
	int* discover;
	int* finish;
	
	int verts;
	int edges;
	int source;
} GraphObj;


//Constructors-Destructors ----------------------------------------------------

//Returns a Graph pointing to a newly created GraphObj representing
//a graph having n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->neibrs = calloc(n+1,sizeof(List));
	G->color = calloc(n+1, sizeof(char));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	
	G->verts = n;
	G->edges = 0;
	G->source = NIL;
	
	for (int i = 1; i <= n; i++)
		G->neibrs[i] = newList();
	
	return(G);
}

//Frees all dynamic memory associated with the Graph *pG, then sets *pG to NULL
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		//while (getSize(*pG) > 0)
			//makeNull(*pG);
		free(*pG);
		*pG = NULL;
	}
}


//Access Functions ------------------------------------------------------------

//Return the number of vertices in G
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference.\n");
		exit(1);
	}
	
	return (G->verts);
}

//Return the number of edges in G
int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph reference.\n");
		exit(1);
	}
	
	return (G->edges);
}

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
		return (G->parent[u]);
	else
		return (NIL);
}

//Returns the discover time of vertex u in the Depth-First forest created by
//DFS(), or UNDEF if DFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDiscover() on NULL Graph reference.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be >= 1 and <= getOrder(G).\n");
		exit(1);
	}
	
	if (G->source != NIL)
		return (G->discover[u]);
	else
		return (UNDEF);
}

//Returns the finish time of vertex u in the Depth-First forest created by
//DFS(), or UNDEF if DFS() has not yet been called
//Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getFinish() on NULL Graph reference.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be >= 1 and <= getOrder(G).\n");
		exit(1);
	}
	
	if (G->source != NIL)
		return (G->finish[u]);
	else
		return (UNDEF);
}


//Manipulation procedures -----------------------------------------------------

//Inserts a new directed edge from u to v
//i.e. v is added to the adjacency List of u
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference.\n");
		exit(1);
	} if (1 > u || u > getOrder(G)) {
		printf("Graph Error: u must be >= 1 and <= getOrder(G).\n");
		exit(1);
	} if (1 > v || v > getOrder(G)) {
		printf("Graph Error: v must be >= 1 and <= getOrder(G).\n");
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


void Visit(Graph G, List S, int u, int *timeptr) {
	
	//u.discover = time
	//u.color = gray
	G->discover[u] = ++(*timeptr);
	G->color[u] = 'g';
	
	//for each vertex adjacent to u
		//if v.color == white
			//v.parent = u
			//Visit(G, v)
	moveFront(G->neibrs[u]);
	while (index(G->neibrs[u]) > -1) {
		int v = get(G->neibrs[u]);
		if (G->color[v] == 'w') {
			G->parent[v] = u;
			Visit(G, S, v, &*timeptr);
		}
		moveNext(G->neibrs[u]);
	}
	
	//u is now black and is finished
	G->color[u] = 'b';
	G->finish[u] = ++(*timeptr);
	
	//Delete the CURRENT vertex from the list
	moveFront(S);
	while (get(S) != u) {
		moveNext(S);
	}
	delete(S);
	
	//Re-add the vertex to the list
	append(S, u);
	
	return;
}

//Runs the depth-first search algorithm on G.
//S defines the order in which vertices will be processed in the main DFS loop,
//and, when DFS is complete, it will store the vertices in order of decreasing
//finish times
//Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
	if (G == NULL) {
		printf("Graph Error: calling DFS() on NULL Graph reference.\n");
		exit(1);
	} if (S == NULL) {
		printf("List Error: calling DFS() on NULL List reference.\n");
		exit(1);
	} if (length(S) != getOrder(G)) {
		printf("DFS Error: length of S (%d) must == order of G (%d).\n", length(S), getOrder(G));
		exit(1);
	}
	
	G->source = front(S);
	
	//for each vertex in G
		//u.color = white
		//u.parent = NIL
	for (int i = 1; i <= getOrder(G); i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
	}
	
	//Set time to 0
	int time = 0;
	
	//Old shit
	while (G->color[front(S)] == 'w')
		Visit(G, S, front(S), &time);
	
	
	//Sort the list in order of decreasing finishing times
	int l = length(S);
	int finTimes[l];
	int j = 0;
	moveFront(S);
	while (index(S) > -1) {
		finTimes[j] = get(S);
		moveNext(S);
		j++;
	}
	clear(S);
	for (int i = 1; i < l; i++) {
		int key = finTimes[i];
		j = i - 1;
		while (j > 0 && finTimes[i] < key) {
			finTimes[j + 1] = finTimes[j];
			j--;
		}
		finTimes[j + 1] = key;
	}
	
	for (int i = 0; i < l; i++)
		prepend(S, finTimes[i]);
	
}


//Other ops -------------------------------------------------------------------

//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling transpose() on NULL Graph reference.\n");
		exit(1);
	}
	
	Graph newG = newGraph(getOrder(G));
	
	for (int i = 1; i <= getOrder(G); i++) {
		moveFront(G->neibrs[i]);
		while (index(G->neibrs[i]) > -1) {
			addArc(newG, get(G->neibrs[i]), i);
			moveNext(G->neibrs[i]);
		}
	}
	
	return (newG);
}

//Returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling copyGraph() on NULL Graph reference.\n");
		exit(1);
	}
	
	Graph newG = newGraph(getOrder(G));
	
	for (int i = 1; i <= getOrder(G); i++) {
		moveFront(G->neibrs[i]);
		while (index(G->neibrs[i]) > -1) {
			addArc(newG, i, get(G->neibrs[i]));
			moveNext(G->neibrs[i]);
		}
	}
	
	return (newG);
}

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