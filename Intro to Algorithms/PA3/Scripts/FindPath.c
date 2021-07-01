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
	
	//Create a new graph of size n
	Graph G = newGraph(n);
	
	//Do shit with the ints in the input file
	int source = 0;
	int dest = 0;
	while (fgets(line, MAX_LEN, in) != NULL) {
		fscanf(in, "%d", &source);
		fscanf(in, "%d", &dest);
		
		if ((source + dest) == 0)
			break;
		
		addEdge(G, source, dest);
	}
	
	printGraph(out, G);
	
	List L = newList();
	while (fgets(line, MAX_LEN, in) != NULL) {
		fscanf(in, "%d", &source);
		fscanf(in, "%d", &dest);
		
		if ((source + dest) == 0)
			break;
		
		BFS(G, source);
		clear(L);
		
		if (getDist(G, dest) == INF) {
			fprintf(out, "The distance from %d to %d is infinity\n", source, dest);
			fprintf(out, "No %d-%d path exists\n", source, dest);
		} else {
			fprintf(out, "The distance from %d to %d is %d\n", source, dest, getDist(G, dest));
			fprintf(out, "A shortest %d-%d path is: ", source, dest);
			getPath(L, G, dest);
			printList(out, L);
			fprintf(out, "\n");
		}
	}
	
	//Quit
	return(0);
}