# rido1607@gmail.com
CXX=clang++
CXXFLAGS=-Wall -Werror -std=c++2a 

# object files for the data structures
OBJS_DS = DSs/list.o DSs/node.o DSs/priorityQueue.o DSs/reversePriorityQueue.o \
	DSs/tuple.o DSs/unionFind.o

# object files for the graph related files
OBJS_GRAPH = Graphs/adjacencyList.o Graphs/algorithm.o Graphs/edge.o Graphs/graph.o Graphs/vertex.o

MAIN_OBJ = main.o $(OBJS_GRAPH) $(OBJS_DS)

# object files for the test files
TEST_OBJ = Tests/testFile.o Tests/testList.o Tests/testPriorityQueue.o Tests/testReversePriorityQueue.o \
	Tests/testUnionFind.o DSs/unionFind.o Tests/testEdge.o Graphs/edge.o Tests/testVertex.o \
	Graphs/vertex.o Tests/testAdjacencyList.o Graphs/adjacencyList.o Tests/testGraph.o \
	Graphs/graph.o Tests/testAlgorithm.o Graphs/algorithm.o Tests/testNode.o DSs/node.o \
	Tests/testTuple.o DSs/tuple.o

# valgrind flags, taken from course site, folder 02-classes-constructors-destructors: the makefile in the valgrind folder
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99 

# creates the main executable
Main: $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o Main $(MAIN_OBJ)

# turns the specified cpp file into an object file with the same name
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: Main
	valgrind $(VALGRIND_FLAGS) ./Main

# creates a test executable for the test files
test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ)

# checks for memory leaks during the tests
valgrind-test: test
	valgrind $(VALGRIND_FLAGS) ./test

clean:
	rm -f *.o DSs/*.o Tests/*.o Graphs/*.o Main test

.PHONY: clean 