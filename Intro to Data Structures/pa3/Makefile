#------------------------------------------------------------------------------
#	Makefile for CMPS 12B pa3
#	This Makefile uses wildcards and pattern substitution, which have not been
#	explained in any previous assignment.  See the GNU Make tutorial 
#
#		http://www.gnu.org/software/make/manual/make.html
#
#	to learn more about these features. Alternatively, create a Makefile 
#	without these features.
#------------------------------------------------------------------------------

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

submit: README Dictionary.java DictionaryTest.java DuplicateKeyException.java KeyNotFoundException.java DictionaryInterface.java DictionaryClient.java Makefile
	submit cmps012b-pt.w18 lab7 README Dictionary.java DictionaryTest.java DuplicateKeyException.java KeyNotFoundException.java DictionaryInterface.java DictionaryClient.java Makefile
