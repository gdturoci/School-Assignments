#------------------------------------------------------------------------------
# A Makefile with macros
#------------------------------------------------------------------------------

JAVASRC   = HelloUser.java
SOURCES   = README Makefile $(JAVASRC)
MAINCLASS = HelloUser
CLASSES   = HelloUser.class
JARFILE   = HelloUser
SUBMIT    = submit cmps012b-pt.w18 lab1

all: $(JARFILE)

$(JARFILE): $(CLASSES)
      echo Main-class: $(MAINCLASS) > Manifest
      jar cvfm $(JARFILE) Manifest $(CLASSES)
      rm Manifest
      chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
      javac -Xlint $(JAVASRC)

clean:
      rm $(CLASSES) $(JARFILE)
submit: $(SOURCES)
      $(SUBMIT) $(SOURCES)