#
# Makefile for DS-MiniSQL project
# TO MEMBERS:
#	 Updare your own object file!
#

CXX = g++
CPPFLAGS = -Wextra -Werror -Wall -O2

OBJS = minisql.o catalog.o interpreter.o

all: minisql

minisql: $(OBJS)
	$(CXX) $(CPPFLAGS) -o minisql $(OBJS)

minisql.o: minisql.cpp Buffer.h Catalog.h ConditionTree.h Definition.h Index.h Interpreter.h
catalog.o: Catalog.cpp Catalog.h
interpreter.o: Interpreter.cpp Interpreter.h

clean:
	rm -f *~ *.o minisql