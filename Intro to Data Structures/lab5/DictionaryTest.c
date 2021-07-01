//Galen Turoci
//gturoci
//Class CMPS 12M
//February 15th, 2018
//This program was used to test the ADT operations before implementing
//them into Dictionary.c.
//DictionaryTest.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]) {
	Dictionary DT = newDictionary();
	char* word1[] = {"one","two","three","four","five","six","seven"};
	char* word2[] = {"foo","bar","blah","galumph","happy","sad","blue"};
	int i;

	for (i = 0; i < 7; i++)
		insert(DT, word1[i], word2[i]);
	
	printDictionary(stdout, DT);
	
	delete(DT, "one");
	//delete(DT, "eight"); Segmentation fault
	delete(DT, "six");
	delete(DT, "four");
	
	printDictionary(stdout, DT);
	
	lookup(DT, "five");
	lookup(DT, "four");
	
	printf("%s\n", (isEmpty(DT)?"true":"false"));
	printf("%d\n", size(DT));
	makeEmpty(DT);
	printf("%s\n", (isEmpty(DT)?"true":"false"));
	
	freeDictionary(&DT);
	
	return (EXIT_SUCCESS);
}
