#------------------------------------------------------------------------------
# makefile for Queens.c with Macros
#------------------------------------------------------------------------------

PROGRAM_NAME = Queens
FLAGS        = -std=c99 -Wall
SOURCES      = $(PROGRAM_NAME).c
OBJECTS      = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm $(EXEBIN) $(OBJECTS)

submit : $(SOURCES) Makefile README
	submit cse015-pt.f19 pa2 $(SOURCES) Makefile README 

check : 
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/pa2/bdelgad3

memcheck : 
	valgrind --leak-check=full Queens $(SOURCES) outfile

