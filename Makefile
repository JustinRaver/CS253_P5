#--make file for CS253 p4 Smash shell
#--includes targets for all (defaut and clean
#--rebuild files when out of date with .c files or headerfiles included in .c

#----define object files
	OBJS = smash.o commands.o history.o
#----Define name of released produyct 
	EXE = smash
#----Define options passed by make to compilker and compiler options
	CFLAGS= -Wall -g -O0 -std=c99
	CC = gcc
#----Define target for all when building executables
all: rules.d $(EXE)

rules.d: Makefile $(wildcard *.c) $(wildcard *.h)
	gcc -MM $(wildcard *.c) >rules.d

#----Include the rules for rebuilding each *.o file
-include rules.d

#----Define Rule for linking executable product
$(EXE): $(OBJS)

	$(CC) $(CFLAGS) $^ -o $@

#----Define clean for cleaning .o and the executables
clean:
	rm -f $(OBJS) $(EXE) *.d *~
	
