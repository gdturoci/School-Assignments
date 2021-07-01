//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

//newList()
//Returns reference to new empty List object.
List newList(void);

//freeList()
//Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL);


// Access functions -----------------------------------------------------------

//length()
//Returns the length of L.
int length(List L);

//index()
//Returns the index of L
int index(List L);

//front()
//Returns the value at the front of L.
//Pre: L->length() < 1
int front(List L);

//back()
//returns teh value at the back of L-
//Pre: L->length() < 1
int back(List L);

//get()
//Returns cursor element
//Pre: length()>0, index()>=0
int get(List L);

//equals()
//returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

//Manipulation procedures ----------------------------------------------------

//clear()
//Resets this List to its original empty state
void clear(List L);

//moveFront()
//If List is non-empty, places the cursor under the front element
//Does nothing otherwise
void moveFront(List L);

//moveBack()
//If List is non-empty, places the cursor under the back element
//Does nothing otherwise
void moveBack(List L);

//movePrev()
//If cursor is defined and not at front, moves cursor one step toward
//front of this List, if cursor is defined and at front, cursor becomes
//undefined, if cursor is undefined does nothing.
void movePrev(List L);

//moveNext()
//If cursor is defined and not at back, moves cursor one step toward
//back of this List, if cursor is defined and at back, cursor becomes
//undefined, if cursor is undefined does nothing.
void moveNext(List L);

//prepend()
//Places new data element at the end of L
void prepend(List L, int data);

//append()
//Places new data element at the end of L
void append(List L, int data);

//insertBefore()
//Insert a new element before the cursor
//Pre: length()>0, index()>=0
void insertBefore(List L, int data);

//insertAfter()
//Insert a new element after the cursor
//Pre: length()>0, index()>=0
void insertAfter(List L, int data);

//deleteFront()
//Deletes element at front of L
//Pre: L->length() > 0
void deleteFront(List L);

//deleteBack()
//Deletes element at back of L
//Pre: L->length() > 0
void deleteBack(List L);

//delete()
//Deletes the cursor element, making cursor undefined
//Pre: length()>0, index()>=0
void delete(List L);

// Other Functions ------------------------------------------------------------

//printList()
//Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

//copyList()
//Copies the List
List copyList(List L);

#endif