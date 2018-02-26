CC = g++
CFLAGS  = -Wall -o
MAIN = main
DEPTH = depthFirst
BREADTH = breadthFirst

$(MAIN): $(MAIN).cpp
	$(CC) $(CFLAGS) $(MAIN) $(MAIN).cpp $(DEPTH).cpp $(BREADTH).cpp

$(VERT_SLICE): $(VERT_SLICE).cpp
	$(CC) $(CFLAGS) $(VERT_SLICE) $(VERT_SLICE)
clean:
	$(RM) $(MAIN)