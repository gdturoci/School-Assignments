#Galen Turoci
#gturoci
#CMPS 12M
#February 23rd, 2018
#This Makefile creates an executable jar file called ListClient.
#Makefile

# Variables
JARFILE    = ListClient
MAINCLASS  = ListClient
SOURCES    = List.java ListInterface.java ListClient.java\
             ListIndexOutOfBoundsException.java
CLASSES    = List.class ListInterface.class ListClient.class List\$$Node.class\
             ListIndexOutOfBoundsException.class

# Build Targets
all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(SOURCES)
	javac -Xlint $(SOURCES)  

clean:
	rm -f $(CLASSES) $(JARFILE)
	
submit: README Makefile List.java ListTest.java ListInterface.java ListIndexOutOfBoundsException.java ListClient.java
	submit cmps012b-pt.w18 lab6 README Makefile List.java ListTest.java ListInterface.java ListIndexOutOfBoundsException.java ListClient.java