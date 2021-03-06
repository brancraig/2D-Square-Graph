# Make file for the 2D-Square-Gridgraph

CC=g++
CFLAGS=-c -Wall
DEBUGFLAGS=-g -Wall
TESTOUTPUT=testexec.out
RUNGDB=gdb
OUTPUTFILE=gridexec.out
MEMTEST=valgrind --leak-check=full

all: gridgraph

allrun: gridgraph 
	./$(OUTPUTFILE)

test: gridgraph.o testmain.o
	$(CC) $(DEBUGFLAGS) gridgraph.o testmain.o -o $(TESTOUTPUT)
	./$(TESTOUTPUT)


debug:  gridgraph.o gridmain.o
	$(CC) $(DEBUGFLAGS) gridgraph.o gridmain.o -o $(TESTOUTPUT)
	$(RUNGDB) $(TESTOUTPUT)	

memtest: gridgraph.o gridmain.o
	$(CC) gridgraph.o gridmain.o -o $(OUTPUTFILE)
	$(MEMTEST) ./$(OUTPUTFILE)


gridgraph: gridgraph.o gridmain.o
	$(CC) gridgraph.o gridmain.o -o $(OUTPUTFILE)

gridgraph.o: gridgraph.cpp
	$(CC) $(CFLAGS) gridgraph.cpp

gridmain.o: gridmain.cpp
	$(CC) $(CFLAGS) gridmain.cpp

testmain.o: testmain.cpp
	$(CC) $(CFLAGS) testmain.cpp

clean:
	rm *.o *.out


