//Galen Turoci
//gturoci
//PA2

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"


//Structs ---------------------------------------------------------------------


//Private NodeObj type
typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

//Private Entry type
typedef EntryObj* Entry;

//Private MatrixObj type
typedef struct MatrixObj {
	int NNZ;
	int size;
	List* Rows;
} MatrixObj;


//Constructors-Destructors ----------------------------------------------------


//newEntry()
//Returns a reference to a new Entry object
Entry newEntry(int x, double y) {
	Entry E = malloc(sizeof(EntryObj));
	E->column = x;
	E->value = y;
	
	return(E);
}

//freeEntry()
//Frees all heap memory associated with Entry *pE, and sets *pE to NULL.
void freeEntry(Entry* pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

//newMatrix()
//Returns reference to new empty Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	
	//Initialize Rows
	M->Rows = calloc(n, sizeof(List));
	for (int i = 0; i < n; i++)
		M->Rows[i] = newList();
	
	//Initialize NNZ
	M->NNZ = 0;
	
	//We know our size now
	M->size = n;
	
	return(M);
}

//freeMatrix()
//Frees all heap memory associated with Matrix *pM, the Lists therein,
//and sets *pM to NULL.
//This calls makeZero, which calls clear, which SHOULD be freeing the memory of
//my Lists (LOL), then frees the Matrix itself and sets its pointer to NULL
void freeMatrix(Matrix* pM) {
	if (pM != NULL && *pM != NULL) { 
		if (size(*pM) > 0)
			makeZero(*pM);
		free(*pM);
		*pM = NULL;
	}
}


// Access functions -----------------------------------------------------------

//size()
//Returns the size of square Matrix M.
int size(Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(1);
	}
	
	return (M->size);
}

//NNZ()
//Returns the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(1);
	}
	
	return M->NNZ;
}

//equals()
//Returns true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(1);
	}
	
	Matrix copyB = newMatrix(size(B));
	copyB = copy(B);
	
	Entry eA, eB;
	int y, z, i, eq = 0;
	double a, b;
	
	eq = ((size(A) == size(copyB)) && (NNZ(A) == NNZ(copyB)));
	if (eq == 0)
		return eq;
	
	for (i = 0; i < size(A); i++) {
		List ithRowA = A->Rows[i];
		List ithRowB = copyB->Rows[i];
		
		if (length(ithRowA) == 0 && length(ithRowB) == 0)
			continue;
		
		moveFront(ithRowA);
		moveFront(ithRowB);
		while (eq && (index(ithRowA) >= 0) && (index(ithRowB) >= 0)) {
			eA = (Entry) get(ithRowA);
			eB = (Entry) get(ithRowB);
			y = eA->column;
			z = eB->column;
			a = eA->value;
			b = eB->value;
			
			eq = ((y == z) && (a == b));
			
			moveNext(ithRowA);
			moveNext(ithRowB);
		}
	}

	return eq;
}


//Manipulation procedures ----------------------------------------------------

//makeZero()
//Resets M to the zero state
void makeZero(Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(1);
	}
	
	List ithRow = newList();
	for (int i = 0; i < size(M); i++) {
		ithRow = M->Rows[i];
		if (length(ithRow) == 0)
			continue;
		
		clear(ithRow);
	}
	M->NNZ = 0;
}

//changeEntry()
//Changes the ithg row, jth column of M to the value x.
//Pre: 1 <= i <= size(M), 1 <= j <= size(M)
void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
		printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(1);
	} if (1 > i || i > size(M) || 1 > j || j > size(M)) {
		printf("Matrix Error: Can't change what isn't there!\n");
		exit(1);
	}
	
	List ithRow = M->Rows[i-1];
	int c;
	Entry e;
	
	if (length(ithRow) == 0 && x != 0.0) {
		append(ithRow, newEntry(j, x));
		M->NNZ++;
	} else if (length(ithRow) != 0) {
		moveFront(ithRow);
		e = (Entry) get(ithRow);
		c = e->column;
		while (c < j && index(ithRow) != length(ithRow) - 1) {
			moveNext(ithRow);
			e = (Entry) get(ithRow);
			c = e->column;
		}
		if (c < j && x != 0.0) {
			insertAfter(ithRow, newEntry(j, x));
			M->NNZ++;
		} else if (c == j) {
			if (x != 0.0)
				e->value = x;
			else {
				delete(ithRow);
				M->NNZ--;
			}
		} else if (x != 0.0) {
			insertBefore(ithRow, newEntry(j, x));
			M->NNZ++;
		}
		moveBack(ithRow);
		moveNext(ithRow);
	}
}


//Matrix Arithmetic operations ------------------------------------------------


//copy()
//Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	if (A == NULL) {
		printf("Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(1);
	}
	
	Matrix newM = newMatrix(size(A));
	List ithRow = newList();
	Entry e;
	int c, i;
	double x;
	
	for (i = 0; i < size(A); i++) {	
		ithRow = A->Rows[i];
		if (length(ithRow) == 0)
			continue;
		
		moveFront(ithRow);
		while (index(ithRow) >= 0) {
			e = (Entry) get(ithRow);
			c = e->column;
			x = e->value;
			changeEntry(newM, i+1, c, x);
			moveNext(ithRow);
		}
	}
	return newM;
}

//transpose()
// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A) {
	if (A == NULL) {
		printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(1);
	}
	
	Matrix newM = newMatrix(size(A));
	List ithRow = newList();
	Entry e;
	int x, i;
	double y;
	
	for (i = 0; i < size(A); i++) {
		ithRow = A->Rows[i];
		if (length(ithRow) == 0)
			continue;
		
		moveFront(ithRow);
		while (index(ithRow) >= 0) {
			e = (Entry) get(ithRow);
			x = e->column;
			y = e->value;
		
			changeEntry(newM, x, i+1, y);
			
			moveNext(ithRow);
		}
	}
	return newM;
}

//scalarMult()
//Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	if (A == NULL) {
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(1);
	}
	
	Matrix newM = newMatrix(size(A));
	List ithRow = newList();
	Entry e;
	int c, i;
	double y;
	
	for (i = 0; i < size(A); i++) {
		ithRow = A->Rows[i];
		if (length(ithRow) == 0)
			continue;
		
		moveFront(ithRow);
		while (index(ithRow) >= 0) {
			e = (Entry) get(ithRow);
			c = e->column;
			y = e->value;
			changeEntry(newM, i+1, c, (x*y));
			moveNext(ithRow);
		}
	}
	return newM;
}

//sum()
//Returns a reference to a new Matrix object representing A+B.
//pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(1);
	} if (size(A) != size(B)) {
		printf("Matrix Error: Can't add Matrices of different sizes!");
		exit(1);
	}
	
	if (equals(A, B))
		return scalarMult(2.0, A);
	
	Matrix newM = newMatrix(size(A));
	List ithRowA = newList();
	List ithRowB = newList();
	Entry eA;
	Entry eB;
	int cA, cB, i;
	double xA = 0.0, xB = 0.0;
	
	for (i = 0; i < size(A); i++) {
		ithRowA = A->Rows[i];
		ithRowB = B->Rows[i];
		if (length(ithRowA) == 0 && length(ithRowB) == 0)
			continue;
		
		moveFront(ithRowA);
		moveFront(ithRowB);
		while (index(ithRowA) >= 0 || index(ithRowB) >= 0) {
			cA = 0;
			cB = 0;
			if (length(ithRowA) != 0 && index(ithRowA) != -1) {
				eA = (Entry) get(ithRowA);
				cA = eA->column;
				xA = eA->value;
			}
			if (length(ithRowB) != 0 && index(ithRowB) != -1) {
				eB = (Entry) get(ithRowB);
				cB = eB->column;
				xB = eB->value;
			}
			
			if (cA == cB) {
				changeEntry(newM, i+1, cA, (xA+xB));
				moveNext(ithRowA);
				moveNext(ithRowB);
			} else if (cA != 0 && (cA < cB || cB == 0)) {
				changeEntry(newM, i+1, cA, xA);
				moveNext(ithRowA);
			} else {
				changeEntry(newM, i+1, cB, xB);
				moveNext(ithRowB);
			}
		}
	}
	return newM;
}

//diff()
//Returns a reference to a new Matrix object representing A-B.
//pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(1);
	} if (size(A) != size(B)) {
		printf("Matrix Error: Can't sub Matrices of different sizes!");
		exit(1);
	}
	
	Matrix newM = newMatrix(size(A));
	if (equals(A, B) == 1)
		return newM;
	
	List ithRowA = newList();
	List ithRowB = newList();
	Entry eA;
	Entry eB;
	int cA, cB, i;
	double xA = 0.0, xB = 0.0;
	
	for (i = 0; i < size(A); i++) {
		ithRowA = A->Rows[i];
		ithRowB = B->Rows[i];
		if (length(ithRowA) == 0 && length(ithRowB) == 0)
			continue;
		
		moveFront(ithRowA);
		moveFront(ithRowB);
		while (index(ithRowA) >= 0 || index(ithRowB) >= 0) {
			cA = 0;
			cB = 0;
			if (length(ithRowA) != 0 && index(ithRowA) != -1) {
				eA = (Entry) get(ithRowA);
				cA = eA->column;
				xA = eA->value;
			}
			if (length(ithRowB) != 0 && index(ithRowB) != -1) {
				eB = (Entry) get(ithRowB);
				cB = eB->column;
				xB = eB->value;
			}
		
			if (cA == cB) {
				changeEntry(newM, i+1, cA, (xA-xB));
				moveNext(ithRowA);
				moveNext(ithRowB);
			} else if (cA != 0 && (cA < cB || cB == 0)) {
				changeEntry(newM, i+1, cA, xA);
				moveNext(ithRowA);
			} else {
				changeEntry(newM, i+1, cB, -xB);
				moveNext(ithRowB);
			}
		}
	}
	return newM;
}

//product()
//Returns a reference to a new Matrix object representing AB
//pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(1);
	} if (size(A) != size(B)) {
		printf("Matrix Error: Can't mult Matrices of different sizes!");
		exit(1);
	}
	
	Matrix newM = newMatrix(size(A));
	List ithRowA = newList();
	List ithRowB = newList();
	int a = size(A), b, c, i, j, yAlength;
	double newY;
	Entry eA[a];
	Entry eB[a];
	double yA[a];
	double yB[a];
	
	yAlength = sizeof(yA)/sizeof(double);
	
	for (i = 0; i < a; i++) {
		ithRowA = A->Rows[i];
		if (length(ithRowA) == 0)
			continue;
		
		for (b = 0; b < yAlength; b++)
			yA[b] = 0.0;
		
		moveFront(ithRowA);
		for (b = 0; b < length(ithRowA); b++) {
			eA[b] = (Entry) get(ithRowA);
			yA[eA[b]->column-1] = eA[b]->value;
			moveNext(ithRowA);
		}
		
		for (j = 1; j <= a; j++) {
			for (b = 0; b < a; b++) {
				ithRowB = B->Rows[b];
				if (length(ithRowB) == 0)
					continue;
			
				moveFront(ithRowB);
				while (index(ithRowB) != j-1 && index(ithRowB) != length(ithRowB) - 1)
					moveNext(ithRowB);
			
				eB[b] = (Entry) get(ithRowB);
				yB[b] = eB[b]->value;
			
				if (eB[b]->column != j)
					yB[b] = 0.0;
			}
			
			c = 0;
			newY = 0.0;
			while (c < a) {
				newY += (yA[c] * yB[c]);
				c++;
			}
		
			changeEntry(newM, i+1, j, newY);
		}
	}
	return newM;	
}

//printMatrix()
//Prints a string representation of Matrix M to filestream out. Zero rows are
//not printed. Each non-zero is represented as one line consisting of the row
//number, followed by a colon, a space, then a space separated list of pairs
//"(col, val)" giving the column numbers and non-zero values in that row. The
//double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
		printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(1);
	}
	
	List ithRow;
	Entry e;
	int c, i;
	double x;
	
	for (i = 0; i < size(M); i++) {
		ithRow = M->Rows[i];
		if (length(ithRow) != 0) {
			moveFront(ithRow);
			fprintf(out, "%d:", i+1);
			while (index(ithRow) >= 0) {
				e = (Entry) get(ithRow);
				c = e->column;
				x = e->value;
			
				fprintf(out, " (%d, %.1f)", c, x);
				moveNext(ithRow);
			}
			fprintf(out, "\n");
		}
	}
}