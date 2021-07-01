//Galen Turoci
//CMPS101 Summer 2019
//PA2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"

//#define MAX_LEN 150

int main(int argc, char* argv[]) {

	//char* line[MAX_LEN];
	
	//Checks to see that the number of command line arguments are 3;
	// any more or less, and the program will quit
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	//Open the first file for reading
	FILE *In;
	In = fopen(argv[1], "r");
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
	
	//Initialize some numbers
	int n, a, b, row, column, i;
	double x;
	
	//Shove some fukkin' numbers in those ints
	fscanf(In, "%d %d %d", &n, &a, &b);
	
	//The Matrices we will be using
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	Matrix scalarMultM = newMatrix(n);
	Matrix sumM = newMatrix(n);
	Matrix diffM = newMatrix(n);
	Matrix transposeM = newMatrix(n);
	Matrix productM = newMatrix(n);
	Matrix copyM = newMatrix(n);
	
	//Reading the first group of entries in the input file and placing them in
	//Matrix A
	for (i = 0; i < a; i++) {
		fscanf(In, "%d %d %lf", &row, &column, &x);
		changeEntry(A, row, column, x);
	}
	
	//Reading the second group of entries in the input file and placing them in
	//Matrix B
	for (i = 0; i < a; i++) {
		fscanf(In, "%d %d %lf", &row, &column, &x);
		changeEntry(B, row, column, x);
	}
	
	
	//Close In
	fclose(In);
	
	//Let's DO THIS
	//Print the matrices
	fprintf(Out, "A has %d non-zero entries:\n", a);
	printMatrix(Out, A);
	fprintf(Out, "\n");
	fprintf(Out, "B has %d non-zero entries:\n", b);
	printMatrix(Out, B);
	fprintf(Out, "\n");
	
	//scalarMult
	scalarMultM = scalarMult(1.5, A);
	fprintf(Out, "(1.5)*A =\n");
	printMatrix(Out, scalarMultM);
	fprintf(Out, "\n");
	
	//sum
	sumM = sum(A, B);
	fprintf(Out, "A+B =\n");
	printMatrix(Out, sumM);
	fprintf(Out, "\n");
	copyM = copy(A);
	sumM = sum(copyM, A);
	fprintf(Out, "A+A =\n");
	printMatrix(Out, sumM);
	fprintf(Out, "\n");
		
	//diff
	diffM = diff(B, A);
	fprintf(Out, "B-A =\n");
	printMatrix(Out, diffM);
	fprintf(Out, "\n");
	diffM = diff(copyM, A);
	fprintf(Out, "A-A =\n");
	printMatrix(Out, diffM);
	fprintf(Out, "\n");
	
	//transpose
	transposeM = transpose(A);
	fprintf(Out, "Transpose(A) =\n");
	printMatrix(Out, transposeM);
	fprintf(Out, "\n");
	
	//product
	productM = product(A, B);
	fprintf(Out, "A*B =\n");
	printMatrix(Out, productM);
	fprintf(Out, "\n");
	productM = product(B, B);
	fprintf(Out, "B*B =\n");
	printMatrix(Out, productM);
	fprintf(Out, "\n");
	
	
	//Free the memory of the Matrices
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&scalarMultM);
	freeMatrix(&sumM);
	freeMatrix(&diffM);
	freeMatrix(&transposeM);
	freeMatrix(&productM);
	freeMatrix(&copyM);
	
	//Close Out
	fclose(Out);
	
	return(0);
}