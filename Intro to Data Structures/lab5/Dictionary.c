//Galen Turoci
//gturoci
//Class CMPS 12M
//February 15th, 2018
//Dictionary.c takes a collection of (key, value) pairs and stores them,
//then implements the DictionaryInterface in order to allow the user to
//manipulate those pairs
//DictionaryTest.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"


//private types --------------------------------------------------------------

//NodeObj
typedef struct NodeObj {
	char* key;
	char* value;
	struct NodeObj* next;
} NodeObj;

//Node
typedef NodeObj* Node;

//newNode()
//constructor of the Node type
Node newNode(char* k, char* v) {
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key = k;
	N->value = v;
	N->next = NULL;
	return(N);
}

//freeNode()
//destructor for the Node type
void freeNode(Node* pN) {
	if (pN!=NULL && *pN!=NULL) {
		free(*pN);
		*pN = NULL;
   }
}

//DictionaryObj
typedef struct DictionaryObj {
	Node top;
	int numItems;
} DictionaryObj;


//public functions -----------------------------------------------------------

//newDictionary()
//constructor for the Dictionary type
Dictionary newDictionary(void) {
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->top = NULL;
	D->numItems = 0;
	return D;
}

//freeDictionary()
//destructor for the Dictionary type
void freeDictionary(Dictionary* pD) {
	if (pD!=NULL && *pD!=NULL) {
		if (!isEmpty(*pD))
			makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
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

//insert()
//inserts key and value onto top of D
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
	if (D->top == NULL) {
		D->top = newNode(key, value);
		return;
	}
	Node N = D->top;
	while (N->next != NULL)
		N = N->next;
	N->next = newNode(key, value);
	D->numItems++;
}

//delete()
//deletes (and returns?) given key from this D
//pre: !isEmpty(D)
void delete(Dictionary D, char* key) {
	if (D==NULL) {
		fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if (D->numItems==0) {
		fprintf(stderr, "Dictionary Error: calling delete() on empty Dictionary\n");
		exit(EXIT_FAILURE);
	}
	Node N = D->top;
	if (strcmp(D->top->key, key) == 0) {
		D->top = D->top->next;
		return;
	} 
	while (strcmp(N->next->key, key) != 0) {
		N = N->next;
		if (N==NULL) {
			fprintf(stderr, "Dictionary Error: calling delete() on non-existent key\n");
			exit(EXIT_FAILURE);
		}
	}
	Node X = N->next;
	N->next = N->next->next;
	D->numItems--;
	freeNode(&X);
}

//lookup()
//returns value at position key in D //SHOULD IT RETURN KEY AND VALUE?
//pre: !isEmpty(D)
char* lookup(Dictionary D, char* key) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = D->top;
	if (N == NULL)
		return NULL;
	while (strcmp(N->key, key) != 0) {
		N = N->next;
		if (N==NULL)
			return NULL;
	}
	return N->value;
}

//makeEmpty()
//resets D to the empty state
//pre: !isEmpty(D)
void makeEmpty(Dictionary D) {
	if (D==NULL) {
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if (D->numItems==0) {
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on empty Dictionary\n");
		exit(EXIT_FAILURE);
	}
	while (D->numItems>0) {
		Node X = D->top;
		D->top = D->top->next;
		freeNode(&X);
		D->numItems--;
	}
}

//printDictionary()
//prints a text representation of D to the file pointed to by out; equivalent to toString
//pre: none
void printDictionary(FILE* out, Dictionary D) {
	Node N;
	if (D==NULL) {
		fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for (N = D->top; N != NULL; N = N->next)
		fprintf(out, "%s=%s\n", N->key, N->value);
	fprintf(out, "\n");
}
