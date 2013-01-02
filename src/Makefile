#
# Makefile for DS-MiniSQL project
# TO MEMBERS:
#	 Updare your own object file!
#

CXX = g++
CPPFLAGS = -Wextra -Werror -Wall -O2

OBJS = MiniSQL.o API.o Catalog.o Index.o Interpreter.o Record.o helper.o

minisql: $(OBJS)
	$(CXX) $(CPPFLAGS) -o minisql $(OBJS)

MiniSQL.o: MiniSQL.cpp MiniSQL.h
	$(CXX) $(CPPFLAGS) -c MiniSQL.cpp
API.o: API.cpp API.h
	$(CXX) $(CPPFLAGS) -c API.cpp
Catalog.o: Catalog.cpp Catalog.h
	$(CXX) $(CPPFLAGS) -c Catalog.cpp
Index.o: Index.cpp Index.h
	$(CXX) $(CPPFLAGS) -c Index.cpp
Interpreter.o: Interpreter.cpp Interpreter.h
	$(CXX) $(CPPFLAGS) -c Interpreter.cpp
Record.o: Record.cpp Record.h
	$(CXX) $(CPPFLAGS) -c Record.cpp
helper.o: helper.cpp helper.h
	$(CXX) $(CPPFLAGS) -c helper.cpp

clean:
	rm -f *.o minisql ../data/*.idx ../data/table.list

cleand:
	rm -f ../data/*