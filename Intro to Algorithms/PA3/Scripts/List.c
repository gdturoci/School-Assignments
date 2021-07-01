//Galen Turoci
//gturoci
//pa4

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structs --------------------------------------------------------------------

//private NodeObj type
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//Constructors-Destructors ---------------------------------------------------

//newNode()
//Returns reference to new Node object. Initializes next and data fields.
//Private.
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL.
//Private.
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

//newList()
//Returns reference to new empty List object.
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}


//freeList()
//Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) { 
		while (length(*pL) > 0)
			deleteFront(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

//length()
//Returns the length of L.
int length(List L) {
	if (L == NULL) {
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return (L->length);
}

//index()
//Returns the index of L
int index(List L) {
	if (L == NULL) {
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return (L->index);
}

//front()
//Returns the value at the front of L.
//Pre: length(L) < 1
int front(List L) {
	if (L == NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	} if (length(L) < 1) {
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->front->data);
}

//back()
//returns the value at the back of this List
//Pre: length(L) > 0
int back(List L) {
	if (L == NULL) {
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1) {
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return(L->back->data);
}

//get()
//Returns cursor element
//Pre: length(L)>0, index(L)>=0
int get(List L) {
	if (L == NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1) {
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->cursor->data);
}

//equals()
//returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B) {
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}

	eq = (length(A) == length(B));
	N = A->front;
	M = B->front;
	while (eq && N != NULL) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

//Manipulation procedures ----------------------------------------------------

//clear()
//Resets this List to its original empty state
void clear(List L) {
	if (L == NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	while (length(L) > 0)
		deleteFront(L);
}

//moveFront()
//If List is non-empty, places the cursor under the front element
//Does nothing otherwise
void moveFront(List L) {
	if (L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	} if (length(L) > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

//moveBack()
//If List is non-empty, places the cursor under the back element
//Does nothing otherwise
void moveBack(List L) {
	if (L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L) > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

//movePrev()
//If cursor is defined and not at front, moves cursor one step toward
//front of this List, if cursor is defined and at front, cursor becomes
//undefined, if cursor is undefined does nothing.
void movePrev(List L) {
	if (L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == L->front)
		L->cursor = NULL;
	else
		L->cursor = L->cursor->prev;
	L->index--;
}

//moveNext()
//If cursor is defined and not at back, moves cursor one step toward
//back of this List, if cursor is defined and at back, cursor becomes
//undefined, if cursor is undefined does nothing.
void moveNext(List L) {
	if (L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
	}
	else {
		L->cursor = L->cursor->next;
		L->index++;
	}
}

//prepend()
//Places new data element at the front of L
void prepend(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	
	Node N = newNode(data);
	if (length(L) < 1)
		L->front = L->back = N; 
	else { 
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
	}
	if (L->cursor != NULL)
		L->index++;
	L->length++;
}

//append()
//Places new data element at the end of L
void append(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	
	Node N = newNode(data);
	if (length(L) < 1) 
		L->front = L->back = N; 
	else { 
		L->back->next = N;
		N->prev = L->back;
		L->back = N; 
	}
	L->length++;
}

//insertBefore()
//Insert a new element before the cursor
//Pre: length(L) > 0, index(L) >= 0
void insertBefore(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1 || index(L) < 0) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	else if (L->cursor == L->front)
		prepend(L, data);
	else {
		Node N = newNode(data);
		Node M = L->cursor->prev;
		L->cursor->prev = N;
		N->prev = M;
		M->next = N;
		N->next = L->cursor; 
		L->length++;
		L->index++;
	}
}

//insertAfter()
//Insert a new element after the cursor
//Pre: length(L) > 0, index(L) >= 0
void insertAfter(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1 || index(L) < 0) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	else if (L->cursor == L->back)
		append(L, data);
	else {
		Node N = newNode(data);
		Node M = L->cursor->next;
		L->cursor->next = N;
		N->next = M;
		M->prev = N;
		N->prev = L->cursor; 
		L->length++;
	}
}

//deleteFront()
//Deletes element at front of L
//Pre: length(L) > 0
void deleteFront(List L) {
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	
	Node N = NULL;
	N = L->front;
	if (length(L) == 1) {
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
	} else {
		L->front = L->front->next; 
		L->index--;	
	}
	L->length--;
	freeNode(&N);
}

//deleteBack()
//Deletes element at back of L
//Pre: length(L) > 0
void deleteBack(List L) {
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	
	Node N = NULL;
	N = L->back;
	if (length(L) == 1) {  
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
	} else {
		if (L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		}
		L->back = L->back->prev;
	}
	L->length--;
	freeNode(&N);
}

//delete()
//Deletes the cursor element, making cursor undefined
//Pre: length(L) > 0, index(L) >= 0
void delete(List L) {
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L) < 1 || index(L) < 0) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	
	if (L->cursor == L->back)
		deleteBack(L);
	else if (L->cursor == L->front)
		deleteFront(L);
	else {
		Node N = NULL;
		N = L->cursor;
		Node M = L->cursor->next;
		L->cursor = L->cursor->prev;
		L->cursor->next = M;
		L->index = -1;
		L->length--;
		freeNode(&N);
	}
}

//Other Functions ------------------------------------------------------------

//printList()
//Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
	}

	for(N = L->front; N != NULL; N = N->next)
		fprintf(out, "%d ", N->data);
	fprintf(out, "\n");
}

//copyList()
//Copies the List
List copyList(List L) {
	List LC = newList();
	Node N = L->front;

	while (N != NULL) {
		append(LC, N->data);
		N = N->next;
	}
	return LC;
}