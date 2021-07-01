//Galen Turoci
//CMPS 101
//PA4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
	
	//The size of our graphs
	int n = 100;
	
	//Create a new graph
	Graph G1 = newGraph(n);
	//Graph G2 = newGraph(n);
	//Graph G3 = newGraph(n);
	//Graph G4 = newGraph(n);
	List L = newList();
	// List I = newList();
	
	
	//Access tests before manipulating
	
	//Test getOrder
	/*printf("%d : 5\n", getOrder(G1));
	
	//Test getSize
	printf("%d : 0\n", getSize(G1));
	
	//Test getParent
	printf("%d : 0\n", getParent(G1, 3));
	
	//Test getDiscover
	printf("%d : -1\n", getDiscover(G1, 4));
	
	//test getFinish
	printf("%d : -1\n", getFinish(G1, 4));*/
	
	
	//Manipulation Tests
	
	
	//Test addArc
	/*addArc(G1, 64, 4);
	addArc(G1, 64, 3);
	addArc(G1, 42, 2);
	addArc(G1, 2, 64);
	addArc(G1, 4, 2);
	addArc(G1, 3, 42);
	for (int i = 1; i <= 100; i++)
		prepend(L, i);
	DFS(G1, L);
	DFS(G1, L);
	printf("%d : 126\n", getDiscover(G1, 4));*/
	
	addArc(G1, 54, 1);
    addArc(G1, 54, 2);
    addArc(G1, 54, 3);
    addArc(G1, 1, 54);
    addArc(G1, 1, 55);
    for (int i = 1; i <= 100; i++) {
		append(L, i);
    }
    DFS(G1, L);
	printf("%d : 5\n", getSize(G1));
	addArc(G1, 55, 1);
	printf("%d : 6\n", getSize(G1));
	/* addArc(G1, 7, 8);
	addArc(G1, 3, 7);
	addArc(G1, 6, 7);
	addArc(G1, 7, 6);
	addArc(G1, 2, 6);
	addArc(G1, 2, 5);
	addArc(G1, 5, 6);
	addArc(G1, 5, 1); */
	
	//Test addEdge
	// addEdge(G2, 1, 2);
	// addEdge(G2, 2, 3);
	// addEdge(G2, 3, 4);
	// addEdge(G2, 4, 5);
	// addEdge(G2, 5, 1);
	
	//Test getSize after manipulating
	//printf("%d : 5\n", getSize(G1));
	//printf("%d : 5\n", getSize(G2));
	
	//Test printGraph
	//printGraph(stdout, G1);
	// printGraph(stdout, G2);
	
	//Test transpose
	//G3 = transpose(G1);
	//printGraph(stdout, G1);
	//printGraph(stdout, G3);
	
	//Test copyGraph
	//G4 = copyGraph(G1);
	//printGraph(stdout, G1);
	//printGraph(stdout, G4);
	
	
	//Test DFS
	/*append(L, 1);
	append(L, 2);
	append(L, 3);
	append(L, 4);
	append(L, 5);
	append(L, 6);
	append(L, 7);
	append(L, 8);
	DFS(G1, L);
	G2 = transpose(G1);
	DFS(G2, L);
	int x = 0;
	moveFront(L);
	while (index(L) > -1) {
		if (getParent(G2, get(L)) == NIL)
			x++;
		moveNext(L);
	}
	printf("%d : 4\n", x);*/
	
	
	//Test getParent after running DFS
	// printf("%d : 0\n", getParent(G2, 1));
	// printf("%d : 3\n", getParent(G2, 2));
	// printf("%d : 0\n", getParent(G2, 3));
	// printf("%d : 3\n", getParent(G2, 4));
	// printf("%d : 1\n", getParent(G2, 5));
	// printf("%d : 7\n", getParent(G2, 6));
	// printf("%d : 0\n", getParent(G2, 7));
	// printf("%d : 0\n", getParent(G2, 8));
	
	
	//Test getDiscover after running DFS
	//printf("%d : 2\n", getDiscover(G1, 2));
	
	//Test getFinish after running DFS
	//printf("%d : 6\n", getFinish(G1, 1));
	
	/*addArc(G1, 64, 4);
	addArc(G1, 64, 3);
	addArc(G1, 42, 2);
	addArc(G1, 2, 64);
	addArc(G1, 4, 2);
	addArc(G1, 3, 42);
	
	
	// addArc(G1, 1, 2);
	// addArc(G1, 2, 3);
	// addArc(G1, 3, 1);
	// addArc(G1, 4, 1);
	
	for (int i = 1; i <= n; i++)
		append(L, i);
	DFS(G1, L);
	G2 = transpose(G1);*/
	/*printf("%d : 1\n", getDiscover(G1, 100));
	printf("%d : 73\n", getDiscover(G1, 64));
	printf("%d : 80\n", getDiscover(G1, 4));
	DFS(G1, L);
	printf("%d : 126\n", getDiscover(G1, 4));*/
	
	
	
	//Quit
	return(0);
}