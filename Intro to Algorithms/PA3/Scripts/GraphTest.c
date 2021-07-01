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
	int n = 99;
	
	//Create a new graph
	Graph G1 = newGraph(n);
	//Graph G2 = newGraph(n);
	List L = newList();
	List I = newList();
	
	
	//Access tests before manipulating
	
	//Test getOrder
	/*printf("%d : 5\n", getOrder(G1));
	
	//Test getSize
	printf("%d : 0\n", getSize(G1));
	
	//Test getSource
	printf("%d : 0\n", getSource(G1));
	
	//Test getParent
	printf("%d : 0\n", getParent(G1, 3));
	
	//Test getDist
	printf("%d : 0\n", getDist(G1, 4));
	
	//Test getPath
	//getPath(L, G1, 3);
	//printList(stdout, L);*/
	
	//Manipulation Tests
	
	//Test addArc
	addArc(G1, 64, 4);
	addArc(G1, 64, 3);
	addArc(G1, 42, 2);
	addArc(G1, 2, 64);
	addArc(G1, 4, 2);
	addArc(G1, 3, 42);
	BFS(G1, 3);
	getPath(L, G1, 64);
	append(I, 3);
	append(I, 42);
	append(I, 2);
	append(I, 64);
	printf("%d : 1\n", equals(L, I));
	moveFront(L);
	BFS(G1, 2);
	getPath(L, G1, 2);
	append(I, 2);
	printf("%d : 1\n", equals(L, I));
	getPath(L, G1, 99);
	printf("%d : 0\n", equals(L, I));
	
	
	//Test addEdge
	/*addEdge(G2, 1, 2);
	addEdge(G2, 2, 3);
	addEdge(G2, 3, 4);
	addEdge(G2, 4, 5);
	addEdge(G2, 5, 1);
	
	//Test getSize after manipulating
	printf("%d : 5\n", getSize(G1));
	printf("%d : 5\n", getSize(G2));
	
	//Test makeNull
	makeNull(G1);
	makeNull(G2);
	printf("%d : 0\n", getSize(G1));
	printf("%d : 0\n", getSize(G2));*/
	
	
	//Test BFS
	//BFS(G1, 1);
	
	
	//Test printGraph
	//printGraph(stdout, G1);
		
	//Test getSource after running BFS
	/*printf("%d : 1\n", getSource(G1));
	
	//Test getParent after running BFS
	printf("%d : 2\n", getParent(G1, 3));*/
	
	//Test getDist after running BFS
	//printf("%d : 3", getDist(G1, 4));
	
	
	//Quit
	return(0);
}