# Galen Turoci
# gturoci
# CMPS 12M
# January 27th, 2018
# This Makefile creates an executable jar file called FileReverse.
# File name: Makefile
FileReverse: FileReverse.o
	gcc -o FileReverse FileReverse.o

FileReverse.o: FileReverse.c
	gcc -c -std=c99 -Wall FileReverse.c

clean:
	rm -f FileReverse FileReverse.o

submit: README Makefile FileReverse.c
	submit cmps012b-pt.w18 lab3 README Makefile FileReverse.c
