//Galen Turoci
//gturoci
//Class CMPS 12B
//March 8th, 2018
//Dictionary.c takes a collection of (key, value) pairs and stores them,
//then implements Dictionary.h in order to allow the user to
//manipulate those pairs
//Dictionary.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"


//private types --------------------------------------------------------------

const int tableSize = 101;

//NodeObj
typedef struct NodeObj {
	char* key;
	char* value;
	struct NodeObj* next;
} NodeObj;

//Node
typedef NodeObj* Node;

//newNode()
//Constructor of the Node type
Node newNode(char* k, char* v) {
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->key = k;
	N->value = v;
	N->next = NULL;
	return(N);
}

//freeNode()
//Destructor for the Node type
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

//DictionaryObj
typedef struct DictionaryObj {
	int numItems;
    Node *Table; //Hash table
} DictionaryObj;

//Public Functions------------------------------------------------------------

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if ( shift == 0 )
		return value;
	return (value << shift) | (value >> (sizeInBits - shift));
}

//pre_hash()
//turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
		}
	return result;
}
//hash()
//turns a string into an int in the range 0 to tableSize-1
int hash(char* key) {
	return pre_hash(key)%tableSize;
} 

//newDictionary()
//constructor for the Dictionary type
Dictionary newDictionary(void) {
    Dictionary D = malloc(sizeof(DictionaryObj));
    assert(D!=NULL);
    D->numItems = 0;
	D->Table = calloc(tableSize, sizeof(Node));
    return D;
}

//freeDictionary()
//destructor for the Dictionary type
void freeDictionary(Dictionary* pD) {
    if (pD!=NULL && *pD!=NULL) {
        if (!isEmpty(*pD))
            makeEmpty(*pD);
		free((*pD)->Table);
        free(*pD);
        *pD = NULL;
    }
}

//isEmpty()
//returns 1 (true) if D is empty, 0 (false) otherwise; equivalent to isEmpty
//pre: none
int isEmpty(Dictionary D) {
    if (D==NULL) {
        fprintf (stderr, "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return(D->numItems==0);
}

//size()
//returns the amount of key, value pairs in this Dictionary
//pre: !isEmpty(D)
int size(Dictionary D) {
    if (D==NULL) {
        fprintf (stderr, "Dictionary Error: calling size() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return D->numItems;
}

//lookup()
//returns value at position key in D
//pre: !isEmpty(D)
char* lookup(Dictionary D, char* key) {
    if (D == NULL) {
        fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
	Node N = D->Table[hash(key)];
	if (N == NULL)
		return NULL;
	else {
		while (N != NULL) {
        	if (strcmp(N->key, key) == 0)
            	return N->value;
			N = N->next;
		}
	}
	return NULL;
}

//insert()
//inserts key and value into D at location Table[hash(key)]
//pre: none
void insert(Dictionary D, char* key, char* value) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if (lookup(D, key) != NULL) {
		fprintf(stderr, "Dictionary Error: Cannot insert duplicate keys\n");
		exit(EXIT_FAILURE);
	}
	Node N = D->Table[hash(key)];
	if (N == NULL)
		D->Table[hash(key)] = newNode(key, value);
	else {
		N = newNode(key, value);
		N->next = D->Table[hash(key)];
		D->Table[hash(key)] = N;
	}
	D->numItems++;
}

//delete()
//deletes pair with given key from this D
//pre: !isEmpty(D)
void delete(Dictionary D, char* key) {
	if (D==NULL) {
		fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = D->Table[hash(key)];
	if (N == NULL) {
		fprintf(stderr, "Dictionary Error: calling delete() on non-existent key\n");
		exit(EXIT_FAILURE);
	}
	else if (strcmp(N->key, key) == 0) {
		D->Table[hash(key)] = N->next;
		freeNode(&N);
		D->numItems--;
		return;
	}
	while (strcmp(N->next->key, key) != 0)
		N = N->next;
	Node X = N->next;
	N->next = N->next->next;
	D->numItems--;
	freeNode(&X);
}

//makeEmpty()
//resets D to the empty state
//pre: !isEmpty(D)
void makeEmpty(Dictionary D) {
    if (D==NULL) {
        fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
	int i;
	D->numItems = 0;
	for (i = 0; i<tableSize; i++) {
		Node N = D->Table[i];
		if (N != NULL)
			D->numItems++;
	}
	i = 0;
    while (D->numItems>0) {
		Node N = D->Table[i];
		if (N != NULL) {
			Node X = N;
			D->Table[i] = D->Table[i]->next;
			freeNode(&X);
			D->numItems--;
		}
		i++;
    }
}

//printDictionary()
//prints a text representation of D to the file pointed to by out
//pre: none
void printDictionary(FILE* out, Dictionary D) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i<tableSize; i++) {
		Node N = D->Table[i];
		if (N != NULL) {
			fprintf(out, "%s %s\n", N->key, N->value);
			while (N->next != NULL) {
				N = N->next;
				fprintf(out, "%s %s\n", N->key, N->value);
			}
		}
	}
}
