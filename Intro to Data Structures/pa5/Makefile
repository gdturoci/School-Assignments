#Galen Turoci
#gturoci
#Class CMPS 12M
#March 16th, 2018
#Makefile for the Dictionary.c ADT and its test client
#Makefile

ADT     = Dictionary
EXEBIN  = $(ADT)Client
SOURCES = $(ADT).c $(EXEBIN).c
OBJECTS = $(ADT).o $(EXEBIN).o
HEADERS = $(ADT).h

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -g -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 

submit: README Dictionary.c Dictionary.h DictionaryTest.c DictionaryClient.c Makefile
	submit cmps012b-pt.w18 pa5 README Dictionary.c Dictionary.h DictionaryTest.c DictionaryClient.c Makefile