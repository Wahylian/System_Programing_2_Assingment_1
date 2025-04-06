CXX=clang++
CXXFLAGS=-Wall -Werror -std=c++2a 

# object files for the data structures
OBJS_DS = DSs/list.o DSs/node.o DSs/priorityQueue.o DSs/reversePriorityQueue.o \
	DSs/tuple.o DSs/unionFind.o

# object files for the graph related files
OBJS_GRAPH = Graphs/adjacencyList.o Graphs/algorithm.o Graphs/edge.o Graphs/graph.o Graphs/vertex.o

MAIN_OBJ = main.o $(OBJS_GRAPH) $(OBJS_DS)

TEST_OBJ = Tests/testFile.o Tests/testList.o Tests/testPriorityQueue.o Tests/testReversePriorityQueue.o \
	Tests/testUnionFind.o DSs/unionFind.o Tests/testEdge.o Graphs/edge.o Tests/testVertex.o \
	Graphs/vertex.o Tests/testAdjacencyList.o Graphs/adjacencyList.o Tests/testGraph.o \
	Graphs/graph.o

# valgrind flags, taken from course site, folder 02-classes-constructors-destructors: the makefile in the valgrind folder
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99 

# creates the main executable
main: $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o main $(MAIN_OBJ)

# turns the specified cpp file into an object file with the same name
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: main
	valgrind $(VALGRIND_FLAGS) ./main

# creates a test executable for the test files
test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ)

# checks for memory leaks during the tests
valgrind-test: test
	valgrind $(VALGRIND_FLAGS) ./test

clean:
	rm -f *.o DSs/*.o Tests/*.o Graphs/*.o main test