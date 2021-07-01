//ListTest.c
//Galen Turoci

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

#define MAX_LEN 150

int main(int argc, char* argv[]) {
	
	List L = newList();
	append(L, 1);
	deleteFront(L);
	
	freeList(&L);
	
	return(0);
	
}