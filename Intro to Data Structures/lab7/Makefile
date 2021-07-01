# Galen Turoci
# gturoci
# CMPS 12M
# March 7th, 2018
# This Makefile creates an executable jar file called DictionaryClient.
# Makefile

JAVAC      = javac 
MAINCLASS  = DictionaryClient
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 


all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit: README Makefile Dictionary.java DictionaryClient.java KeyNotFoundException.java DuplicateKeyException.java DictionaryInterface.java
	submit cmps012b-pt.w18 pa1 README Makefile Dictionary.java DictionaryClient.java KeyNotFoundException.java DuplicateKeyException.java DictionaryInterface.java
