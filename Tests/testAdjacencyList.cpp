#include "doctest.h"
#include "../Graphs/adjacencyList.hpp"

TEST_CASE("AdjacencyList Initialization"){
    SUBCASE("valid list"){
        int var = 5;
        AdjacencyList aj = AdjacencyList(var);

        // checks that the size of the list is correct
        CHECK(aj.getNumVx() == var);
    }
    SUBCASE("valid list, 0 vertices"){
        AdjacencyList aj = AdjacencyList(0); // creates an adjacency list with 0 vertices

        // checks that the size of the list is correct
        CHECK(aj.getNumVx() == 0);
    }
    SUBCASE("invalid list"){
        // attempting to create a list of -3 vertices
        CHECK_THROWS(AdjacencyList(-3));
    }
}

TEST_CASE("Test Copy Constructor"){
    // creates a new adjacency list
    AdjacencyList *aj = new AdjacencyList(5);

    // adds multiple edges to the list
    aj->addEdge(0, 4, -5);
    aj->addEdge(0, 2);
    aj->addEdge(4, 2, 10);
    aj->addEdge(3, 1, 5);
    aj->addEdge(3, 0);

    // creates a copy of aj
    AdjacencyList *copy = new AdjacencyList(*aj);

    // checks each pointer points to a different address
    CHECK(aj != copy);

    // checks they are the same size
    CHECK(aj->getNumVx() == copy->getNumVx());
    CHECK(aj->getNumEdges() == copy->getNumEdges());

    // goes over each vertex in the lists, and check they are stored in different addresses
    for(int i=0; i<aj->getNumVx(); i++){
        const Vertex &v = aj->getVertex(i);
        const Vertex &u = copy->getVertex(i);

        // checks v and u are stored at different addresses
        CHECK(&v != &u);

        // checks they are equal
        CHECK(v == u);

        // checks the list of vertices in v is stored in a different address than the list of vertices in u
        CHECK(&v.getEdges() != &u.getEdges());
    }

    // checks that removing an edge in copy doesn't affect aj
    CHECK(copy->isEdgeExists(3, 1) == true);
    copy->removeEdge(3, 1);
    CHECK(copy->isEdgeExists(3, 1) == false);
    // checks it still exists in aj
    CHECK(aj->isEdgeExists(3, 1));

    // deletes both lists
    delete aj;
    delete copy;
}

TEST_CASE("Adding edge to list"){
    SUBCASE("adds valid edge"){
        // creates an adjacency list of 5 vertices
        int var = 5;
        AdjacencyList aj = AdjacencyList(var);

        // checks if the edge (0, 2) exists
        CHECK(aj.isEdgeExists(0, 2) == false);

        // attempts to add an edge between to existing vertices
        aj.addEdge(0, 2, 5);

        // checks if the edge (0, 2) exists now
        CHECK(aj.isEdgeExists(0, 2) == true);
    }
    SUBCASE("adds invalid edge"){
        // creates an adjacency list of 5 vertices
        int var = 5;
        AdjacencyList aj = AdjacencyList(var);

        // attempts to add an edge between invalid vertices
        CHECK_THROWS(aj.addEdge(-1, 4)); // negative vertex to real vertex
        CHECK_THROWS(aj.addEdge(3, 8)); // real vertex to a non-existing vertex
    }
    // testing adding an edge that already exists
    SUBCASE("adds existing edge"){
        int var = 5;
        AdjacencyList aj = AdjacencyList(var);

        // adds an edge
        aj.addEdge(1,4, 7); // adds an edge between vertex 1 and 4 of weight 7
        
        // checks it exists
        CHECK(aj.isEdgeExists(1,4));

        // checks that v has just 1 edge
        const Vertex &vx1 = aj.getVertex(1);
        CHECK(vx1.getNumEdges() == 1);

        // adds the same edge with a different weight
        aj.addEdge(1, 4, 2);

        // checks it exists
        CHECK(aj.isEdgeExists(1,4));

        // checks that v has just 1 edge
        const Vertex &vx2 = aj.getVertex(1);
        CHECK(vx2.getNumEdges() == 1);

        // adds a different edge 
        aj.addEdge(1,2, 5);

        // checks it exists
        CHECK(aj.isEdgeExists(1,2));

        // checks that v has 2 edges now
        const Vertex &vx3 = aj.getVertex(1);
        CHECK(vx2.getNumEdges() == 2);
    }
}
TEST_CASE("Remove Edges"){
    SUBCASE("Remove Existing Edge"){
        AdjacencyList aj = AdjacencyList(5);
        // adds multiple edges
        aj.addEdge(1,2, 4);
        aj.addEdge(0,3,0);
        aj.addEdge(0,2, -9);

        // checks amount of edges
        CHECK(aj.getNumEdges() == 3);

        // attempts to remove an edge
        aj.removeEdge(0,3);

        // checks the amount of edges decreased
        CHECK(aj.getNumEdges() == 2);

        // checks the edge was actually removed
        CHECK(aj.isEdgeExists(0, 3) == false);
    }
    SUBCASE("Remove none-Existing Edge"){
        AdjacencyList aj = AdjacencyList(5);
        // adds multiple edges
        aj.addEdge(1,2, 4);
        aj.addEdge(0,3,0);
        aj.addEdge(0,2, -9);

        // checks amount of edges
        CHECK(aj.getNumEdges() == 3);

        // attempts to remove a none existing edge
        CHECK_THROWS(aj.removeEdge(0,4));
    }
}

TEST_CASE("Get Vertex"){
    AdjacencyList aj = AdjacencyList(5);

    // adds multiple edges
    aj.addEdge(0, 4);
    aj.addEdge(1, 4, 8);
    aj.addEdge(2, 3, 0);
    aj.addEdge(3, 1, -2);

    SUBCASE("Get existing vertex"){
        // gets vertex 4
        const Vertex& vx1 = aj.getVertex(4);

        // checks this is vx #4
        CHECK(vx1.getVertexName() == 4);

        // checks that vx1 has no edges
        CHECK(vx1.getNumEdges() == 0);

        // gets vertex 1
        const Vertex& vx2 = aj.getVertex(1);

        // checks this is vx #1
        CHECK(vx2.getVertexName() == 1);

        // checks that vx2 has 1 edge
        CHECK(vx2.getNumEdges() == 1);
    }
    SUBCASE("Get none existing vertex"){
        CHECK_THROWS(aj.getVertex(-1)); // negative vertex
        CHECK_THROWS(aj.getVertex(5)); // out of range vertex
    }
}

TEST_CASE("Test Memory Leak"){
    AdjacencyList *aj = new AdjacencyList(5);

    // adds multiple edges to aj
    aj->addEdge(0, 1, -5);
    aj->addEdge(1, 4, 0);
    aj->addEdge(1, 2, 7);
    aj->addEdge(3, 1, 2);

    // checks that there are 4 edges
    CHECK(aj->getNumEdges() == 4); 

    // gets a vertex from the list
    const Vertex &vx = aj->getVertex(3);

    // removes an edge from the list
    aj->removeEdge(1, 4);

    // checks that there are 3 edges
    CHECK(aj->getNumEdges() == 3);

    // deletes aj
    delete aj;
}
