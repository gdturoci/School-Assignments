//Galen Turoci
//gturoci
//pa1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 150

int main(int argc, char* argv[]) {

	char line[MAX_LEN];
	
	//Checks to see that the number of command line arguments are 3;
	// any more or less, and the program will quit
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	//Open the first file for reading
	FILE *In;
	FILE *In1;
	In = fopen(argv[1], "r");
	In1 = fopen(argv[1], "r");
	if (In == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	//Open the second file for writing
	FILE *Out;
	Out = fopen(argv[2], "w");
	if (Out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	//A variable to count the number of lines in fileIn
	int lineCount = 0;
	
	//Gets the contents of the input file
	while (fgets(line, MAX_LEN, In) != NULL)
		lineCount++;
	
	//close fileIn
	fclose(In);
	
	//initialize an array of strings
	char** input = malloc(lineCount * sizeof(char*));
	
	//Put the contents of the input file into that string array
	int x = 0;
	while (fgets(line, MAX_LEN, In1) != NULL) {
		input[x] = (char*)malloc(sizeof(line+1));
		strcpy(input[x], line);
		x++;
	}
	
	//close fileIn1
	fclose(In1);
	
	//Inserting the indices of the array into the List
	List L = newList();
	int cursor;
	int i = 0;
	append(L, i);
	for (i = 1; i < lineCount; i++) {
		moveFront(L);
		cursor = get(L);
		int j = length(L);
		while (j > 1 && (strcmp(input[cursor], input[i]) < 0)) {
			moveNext(L);
			cursor = get(L);
			j--;
		}
		if (strcmp(input[cursor], input[i]) < 0)
			append(L, i);
		else
			insertBefore(L, i);
	}
	
	//Print the sorted array and close fileOut
	moveFront(L);
	while (index(L)>=0) {
		cursor = get(L);
		fprintf(Out, "%s", input[cursor]);
		moveNext(L);
	}
	fclose(Out);
	
	//Free the memory of the array
	for (int i = 0; i < lineCount; i++)
		free(input[i]);
	free(input);
	
	//Free the memory of the list
	freeList(&L);
	
	//Quit
	return(0);
}
