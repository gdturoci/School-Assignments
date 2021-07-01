//Galen Turoci
//CMPS 101
//pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 150

int main(int argc, char* argv[]) {
	
	char line[MAX_LEN];
	
	//If there are any more or less than 3 arguments, quit
	if (argc != 3) {
		printf("Usage: FindPath <input file> <output file>\n");
		exit(1);
	}
	
	//Open an input file for reading
	FILE *in;
	in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	//Open a second file for writing
	FILE *out;
	out = fopen(argv[2], "w");
	if (out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	//Get the # of verts from the input file
	int n = 0;
	fscanf(in, "%d", &n);
	
	//Create two new graphs of size n
	Graph G = newGraph(n);
	Graph transG = newGraph(n);
	
	//Do shit with the ints in the input file
	int source = 0;
	int dest = 0;
	while (fgets(line, MAX_LEN, in) != NULL) {
		fscanf(in, "%d", &source);
		fscanf(in, "%d", &dest);
		
		if ((source + dest) == 0)
			break;
		
		addArc(G, source, dest);
	}
	
	//Print the OG graph
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	
	//Create a List for DFS and fills it up
	List L = newList();
	for (int i = 1; i <= n; i++)
		append(L, i);
	
	//Run DFS on G
	DFS(G, L);
	
	//Make a transpose of the OG graph and run DFS on it
	transG = transpose(G);
	DFS(transG, L);
	
	//Determine the number of SCCs
	int SCCnum = 0;
	moveFront(L);
	while (index(L) > -1) {
		if (getParent(transG, get(L)) == NIL)
			SCCnum++;
		moveNext(L);
	}
	
	//Create an array of Lists to hold our SCCs
	List* SCC = calloc(SCCnum, sizeof(List));
	for (int i = 0; i < SCCnum; i++)
		SCC[i] = newList();
	
	//Fill those Lists with the SCCs
	moveFront(L);
	int y = SCCnum-1;
	while (y > -1) {
		if (getParent(transG, get(L)) == NIL) {
			append(SCC[y], get(L));
			moveNext(L);
		}
		while (getParent(transG, get(L)) != NIL) {
			append(SCC[y], get(L));
			moveNext(L);
			if (index(L) == -1)
				break;
		}
		y--;
	}
	
	//Print those fuckers out
	fprintf(out, "G contains %d strongly connected components:\n", SCCnum);
	moveFront(L);
	for (int i = 1; i <= SCCnum; i++) {
		fprintf(out, "Component %d: ", i);
		int j = i-1;
		moveFront(SCC[j]);
		while (index(SCC[j]) > -1) {
			fprintf(out, "%d ", get(SCC[j]));
			moveNext(SCC[j]);
		}
		fprintf(out, "\n");
	}
	
	
	//Quit
	return (0);
}
	