//Galen Turoci
//CMPS 101 Summer 2019
//PA2

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char* argv[]) {
	
	//The size of our matrices
	int n = 15; 
	
	//Create a new matrices
	Matrix Test1 = newMatrix(n);
	Matrix Test2 = newMatrix(n);
	//Matrix CopyM = newMatrix(n);
	//Matrix scalarMultM = newMatrix(n);
	//Matrix sumM = newMatrix(n);
	Matrix diffM = newMatrix(n);
	//Matrix transposeM = newMatrix(n);
	//Matrix productM = newMatrix(n);
	
	//Test size() when size is 3
	//printf("%d : 3\n", size(Test1));
	
	//Test NNZ() when there are no NNZ
	//printf("%d\n", NNZ(Test1));
	
	//Testing changeEntry()
	changeEntry(Test1, 1, 1, -4);
	changeEntry(Test1, 1, 2, -2);
	changeEntry(Test1, 1, 3, 0);
	changeEntry(Test1, 2, 5, 4);
	changeEntry(Test1, 2, 1, -2);
	changeEntry(Test1, 3, 1, 2);
	changeEntry(Test1, 2, 2, -2);
	changeEntry(Test1, 3, 3, 0);
	
	changeEntry(Test2, 1, 1, -4);
	changeEntry(Test2, 1, 2, 0);
	changeEntry(Test2, 2, 1, 0);
	changeEntry(Test2, 2, 2, -2);
	changeEntry(Test2, 2, 4, 2);
	changeEntry(Test2, 3, 1, 2);
	changeEntry(Test2, 3, 2, 2);
	changeEntry(Test2, 7, 8, 5);
	
	
	diffM = diff(Test1, Test2);
	printMatrix(stdout, diffM);
	printf("\n%d : 6\n", NNZ(diffM));
	
	
	
	//Test size while it is still 3
	/*printf("%d : 3\n", size(Test1));
	
	//Print the matrices
	printf("Test1 = \n");
	printMatrix(stdout, Test1);
	printf("\n");
	printf("Test2 = \n");
	printMatrix(stdout, Test2);
	printf("\n");
	
	//Test equals() and NNZ()
	printf("Test1 size: %d - Test2 size: %d\n", size(Test1), size(Test2));
	printf("Test1 NNZ: %d - Test2 NNZ: %d\n", NNZ(Test1), NNZ(Test2));
	printf("%d : 1\n", equals(Test1, Test1));
	printf("%d : 0\n", equals(Test1, Test2));
	
	//Test copy() and equals() again
	CopyM = copy(Test1);
	printf("\nCopy = \n");
	printMatrix(stdout, CopyM);
	printf("%d : 1\n", equals(Test1, CopyM));
	
	//Test makeZero()
	printf("%d : 9\n", NNZ(CopyM));
	makeZero(CopyM);
	printf("%d : 0\n", NNZ(CopyM));
	printMatrix(stdout, CopyM);
	
	//Test scalarMult()
	scalarMultM = scalarMult(1.5, Test1);
	printf("\nscalarMult = \n");
	printMatrix(stdout, scalarMultM);
	
	//Test sum()
	sumM = sum(Test1, Test2);
	printf("\nsum = \n");
	printMatrix(stdout, sumM);
	sumM = sum(Test1, CopyM);
	printf("\nsum = \n");
	printMatrix(stdout, sumM);
	
	//Test diff()
	diffM = diff(Test1, Test2);
	printf("\ndiff = \n");
	printMatrix(stdout, diffM);
	printf("%d : 8\n", NNZ(diffM));
	diffM = diff(Test1, CopyM);
	printf("\ndiff = \n");
	printMatrix(stdout, diffM);
	printf("%d : 0\n", NNZ(diffM));
	
	//Test transpose()
	transposeM = transpose(Test1);
	printf("\ntranspose = \n");
	printMatrix(stdout, transposeM);
	transposeM = transpose(Test2);
	printf("\ntranspose = \n");
	printMatrix(stdout, transposeM);
	
	//Test product()
	productM = product(Test1, Test2);
	printf("\nproduct = \n");
	printMatrix(stdout, productM);
	productM = product(Test2, Test1);
	printf("\nproduct = \n");
	printMatrix(stdout, productM);
	productM = product(Test2, Test2);
	printf("\nproduct = \n");
	printMatrix(stdout, productM);*/
}