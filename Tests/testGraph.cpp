#include "doctest.h"
#include "../Graphs/graph.hpp"

TEST_CASE("Graph Initialization"){
    SUBCASE("Valid Graph"){
        SUBCASE("Empty Graph"){
            // attempts to create a graph with 0 vertices
            CHECK_NOTHROW(Graph(0));
        }
        SUBCASE("Positive amount of Vertices"){
            Graph g = Graph(5);

            // check that the size of the graph is 5
            CHECK(g.numVertices() == 5);
        }
    }
    SUBCASE("Invalid Graph"){
        // attempts to create a graph with a negative amount of vertices
        CHECK_THROWS(Graph(-3));
    }
}

TEST_CASE("Test Add Edge"){
    SUBCASE("Adding edge through vertices"){
        Graph g = Graph(5);

        // checks the graph has no edges
        CHECK(g.numEdges() == 0);

        // add an edge to the graph
        g.addEdge(0, 4, 2);

        // checks the graph has 1 edge
        CHECK(g.numEdges() == 1);

        // adding a different edge
        g.addEdge(1, 0, -1);

        // checks the graph has 2 edges
        CHECK(g.numEdges() == 2);
    }
    SUBCASE("Adding edge Object"){
        Graph g = Graph(5);

        // checks the graph has no edges
        CHECK(g.numEdges() == 0);

        // add an edge to the graph 
        Edge e1 = Edge(0, 4, 2);
        g.addEdge(e1);

        // checks the graph has 1 edge
        CHECK(g.numEdges() == 1);

        // adding a different edge 
        Edge e2 = Edge(1, 0, -1);
        g.addEdge(e2);

        // checks the graph has 2 edges
        CHECK(g.numEdges() == 2);
    }
    SUBCASE("Add Invalid Edge"){
        Graph g = Graph(5);

        // attempts to add an impossible edge
        CHECK_THROWS(g.addEdge(-1, 0, 5)); // edge with a vertex with negative vertex
        CHECK_THROWS(g.addEdge(2, 7)); // edge with a non-existing vertex
        CHECK_THROWS(g.addEdge(Edge(4,9,0))); // edge object with non-existing vertex
    }
    SUBCASE("Adding the same vertex twice with different weights"){
        Graph g = Graph(5);

        // checks the graph has no edges
        CHECK(g.numEdges() == 0);

        // add an edge to the graph
        g.addEdge(0, 4, 2);

        // checks the graph has 1 edge
        CHECK(g.numEdges() == 1);

        // adds the same edge with a different weight
        g.addEdge(Edge(0, 4, -1));

        // checks the graph still has only 1 edge
        CHECK(g.numEdges() == 1);

        // checks its the same edge
        CHECK(g.isEdgeExists(0, 4) == true);
    }
    SUBCASE("Add edge from a vertex to itself"){
        Graph g = Graph(5);
        // attempts to add an edge from a vertex to itself
        CHECK_THROWS(g.addEdge(0, 0));
    }
}

TEST_CASE("Test isEdgeExists"){
    SUBCASE("With vertices"){
        Graph g = Graph(5);
        
        // adds an edge to the graph
        g.addEdge(3, 2);
        // check the graph has 1 edge
        CHECK(g.numEdges() == 1);

        SUBCASE("Exists"){
            // checks the edge exists
            CHECK(g.isEdgeExists(3, 2));
            // checks the complimentary edge exists
            CHECK(g.isEdgeExists(2, 3));
        }
        SUBCASE("Doesn't Exist"){
            // checks a different edge doesn't exist
            CHECK(g.isEdgeExists(0, 3) == false);
        }
    }
    SUBCASE("With edge"){
        Graph g = Graph(5);

        Edge e = Edge(4, 0);
        // adds an edge to the graph
        g.addEdge(e);
        // check the graph has 1 edge
        CHECK(g.numEdges() == 1);

        SUBCASE("Exists"){
            // checks the edge exists
            CHECK(g.isEdgeExists(e));
            // checks the complimentary edge exists
            CHECK(g.isEdgeExists(Edge(0, 4)));
        }
        SUBCASE("Doesn't Exist"){
            // checks a different edge doesn't exist
            CHECK(g.isEdgeExists(Edge(0, 2, 20)) == false);
        }
    }
}

TEST_CASE("Remove Edge"){
    Graph g = Graph(5);

    // adds edges to g
    g.addEdge(1, 4, -1);
    g.addEdge(1, 3, 0);
    g.addEdge(0, 3);
    g.addEdge(Edge(2, 4));
    g.addEdge(Edge(3, 4));

    // checks the graph has 5 edges
    CHECK(g.numEdges() == 5);

    SUBCASE("Remove Existing edge"){
        SUBCASE("Remove edge at direction of creation"){
            // checks the edge (1, 4) exists
            CHECK(g.isEdgeExists(1, 4));
            // checks the edge (4, 1) exists
            CHECK(g.isEdgeExists(4, 1));

            // removes edge
            CHECK_NOTHROW(g.removeEdge(1, 4));

            // checks the edge (1, 4) doesn't exist
            CHECK(g.isEdgeExists(1, 4) == false);
            // checks the edge (4, 1) doesn't exist
            CHECK(g.isEdgeExists(4, 1) == false);
        }
        SUBCASE("Remove edge at opposite direction to the creation"){
            // checks the edge (4, 2) exists
            CHECK(g.isEdgeExists(4, 2));
            // checks the edge (2, 4) exists
            CHECK(g.isEdgeExists(2, 4));

            // removes edge
            CHECK_NOTHROW(g.removeEdge(4, 2));

            // checks the edge (4, 2) doesn't exist
            CHECK(g.isEdgeExists(4, 2) == false);
            // checks the edge (2, 4) doesn't exists
            CHECK(g.isEdgeExists(2, 4) == false);
        }
    }
    SUBCASE("Remove non-Existing edge"){
        // attempts to remove an edge that doesn't exist in the graph
        CHECK(g.isEdgeExists(0, 2) == false); // edge (0, 2) wasn't added to it
        
        CHECK_THROWS(g.removeEdge(0, 2));
    }
    SUBCASE("Remove invalid Edge"){
        // attempts to remove an edge with a negative vertex
        CHECK_THROWS(g.removeEdge(-1, 3));
        // attempts to remove an edge with an out of range vertex
        CHECK_THROWS(g.removeEdge(3, 5));
    }
}

TEST_CASE("Test get edges"){
    // creates a graph
    Graph g = Graph(5);
    // creates a list of edges, where each edge added to the graph will be added
    List<Edge> copyEdges = List<Edge>();

    // adds edges
    g.addEdge(1, 2);
    copyEdges.insert(Edge(1, 2));
    copyEdges.insert(Edge(2, 1));

    g.addEdge(4, 1);
    copyEdges.insert(Edge(4, 1));
    copyEdges.insert(Edge(1, 4));

    // checks there are 2 edges in the graph
    CHECK(g.numEdges() == 2);

    // gets the list of edges in the graph
    const List<Edge> &edges = g.getEdges();

    // checks that both lists are the same size
    CHECK(copyEdges.size() == edges.size());

    // checks all edges in copy edges are in edges
    for(int i=0; i<copyEdges.size(); i++){
        // checks the i-th edge in copyedges exists in edges
        CHECK(edges.isExists(copyEdges.getValue(i)) == true);
    }
}

TEST_CASE("Get Vertex"){
    Graph g = Graph(5);

    // adds multiple edges
    g.addEdge(0, 4);
    g.addEdge(1, 4, 8);
    g.addEdge(2, 3, 0);
    g.addEdge(3, 1, -2);

    SUBCASE("Get existing vertex"){
        // gets vertex 4
        const Vertex& vx1 = g.getVertex(4);

        // checks this is vx #4
        CHECK(vx1.getVertexName() == 4);

        // checks that vx1 has 2 edge: (4, 0) and (4, 1)
        CHECK(vx1.getNumEdges() == 2);

        // gets vertex 1
        const Vertex& vx2 = g.getVertex(1);

        // checks this is vx #1
        CHECK(vx2.getVertexName() == 1);

        // checks that vx2 has 2 edges: (1, 4) and (3, 1)
        CHECK(vx2.getNumEdges() == 2);
    }
    SUBCASE("Get none existing vertex"){
        CHECK_THROWS(g.getVertex(-1)); // negative vertex
        CHECK_THROWS(g.getVertex(5)); // out of range vertex
    }
}
/*
#define DEBUG1
TEST_CASE("Test Memory Leak"){
    // creates a new graph
    Graph *g = new Graph(5);

    #ifdef DEBUG1
    // adds edges to the graph
    g->addEdge(1, 3, 0);
    g->addEdge(3, 2, 8);
    g->addEdge(0, 4, -1);
    g->addEdge(4, 1);

    
    // checks there are 4 edges
    CHECK(g->numEdges() == 4);

    #endif
    #ifdef DEBUG2
    // adds same edge with differnt weight
    g->addEdge(2, 3, 2);

    // checks there are still 4 edges
    CHECK(g->numEdges() == 4);
    #endif
    #ifdef DEBUG3
    // removes edges from graph
    g->removeEdge(4, 0);

    // checks there are 3 edges in the graph
    CHECK(g->numEdges() == 3);

    #endif
    // deletes the graph
    delete g;
}*/