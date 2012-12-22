#
# Makefile for DS-MiniSQL project
# TO MEMBERS:
#	 Updare your own object file!
#

CXX = g++
CPPFLAGS = -Wextra -Werror -Wall -O2

OBJS = minisql.o api.o catalog.o index.o interpreter.o record.o

minisql: $(OBJS)
	$(CXX) $(CPPFLAGS) -o minisql $(OBJS)

minisql.o: MiniSQL.cpp MiniSQL.h
	$(CXX) $(CPPFLAGS) -c MiniSQL.cpp
api.o: API.cpp API.h
	$(CXX) $(CPPFLAGS) -c API.cpp
catalog.o: Catalog.cpp Catalog.h
	$(CXX) $(CPPFLAGS) -c Catalog.cpp
index.o: Index.cpp Index.h
	$(CXX) $(CPPFLAGS) -c Index.cpp
interpreter.o: Interpreter.cpp Interpreter.h
	$(CXX) $(CPPFLAGS) -c Interpreter.cpp
record.o: Record.cpp Record.h
	$(CXX) $(CPPFLAGS) -c Record.cpp
