#include "doctest.h"
#include "../Graphs/vertex.hpp"

TEST_CASE("Vertex Initialization"){
    // a vertex must have a non negative int for a name
    SUBCASE("Vertex with valid name"){
        CHECK_NOTHROW(Vertex(5));
    }
    SUBCASE("Vertex with invalid name"){
        CHECK_THROWS(Vertex(-3));
    }
}

TEST_CASE("Adding Edges"){
    SUBCASE("add using vertex name"){
        SUBCASE("valid vertex name"){
            // creating a vertex
            Vertex v = Vertex(0);

            // adding multiple edges to it
            for(int i=0; i<10; i++){
                v.addEdge(i, i); // each edge has a different weight
                CHECK(v.getNumEdges() == i+1);
            }
        }
        SUBCASE("invalid vertex name"){
            // creating a vertex
            Vertex v = Vertex(0);

            // adding a negative vertex
            CHECK_THROWS(v.addEdge(-1));
        }
    }
    SUBCASE("add using a vertex"){
        Vertex v1 = Vertex(0);
        Vertex v2 = Vertex(1);
        Vertex v3 = Vertex(2);

        // checks neither v1 nor v2 have any edges
        CHECK(v1.getNumEdges() == 0);
        CHECK(v2.getNumEdges() == 0);
        // adding edge from v1 to v2
        v1.addEdge(v2);
        // check an edge was added on v1 and not on v2
        CHECK(v1.getNumEdges() == 1);
        CHECK(v2.getNumEdges() == 0);
        // adds another edge to v1
        v1.addEdge(v3);
        // check an edge was added on v1 and not on v3
        CHECK(v1.getNumEdges() == 2);
        CHECK(v3.getNumEdges() == 0);
    }
    SUBCASE("add using an edge"){
        SUBCASE("add with a valid edge"){
            Vertex v = Vertex(0);
            Edge e = Edge(0, 5);
            CHECK_NOTHROW(v.addEdge(e));
            // checks the edge was added
            CHECK(v.getNumEdges() == 1);
        }
        SUBCASE("add with an invalid edge"){
            // an invalid edge for vertex v would be an edge (w,u), where w!=v
            Vertex v = Vertex(0);
            Edge e = Edge(1, 5);
            CHECK_THROWS(v.addEdge(e));
        }
    }
}

TEST_CASE("Removing Edges"){
    // creating a vertex
    Vertex v = Vertex(0);

    // adding multiple edges to it
    for(int i=0; i<10; i++)
        v.addEdge(Vertex(i), i); // each edge has a different weight

    SUBCASE("Removing Existing Edge"){
        int size = v.getNumEdges();
        CHECK_NOTHROW(v.removeEdge(Vertex(3))); 
        CHECK(v.getNumEdges() == size-1); // checks that an edge was removed
    }
    SUBCASE("Removing Non Existing Edge"){
        int size = v.getNumEdges();
        CHECK_THROWS(v.removeEdge(Vertex(20))); // creating a valid vertex, but an edge doesn't exist
        CHECK(v.getNumEdges() == size); // checks that no edges were removed
    }
}
 
TEST_CASE("Test Is Edge Exists"){
    // creates multiple vertices
    Vertex v1 = Vertex(0);
    Vertex v2 = Vertex(1);
    Vertex v3 = Vertex(2);

    // adds the following edges:
    v1.addEdge(v2); // (v1, v2)
    v2.addEdge(v1); // (v2, v1)
    v1.addEdge(v3); // (v1, v3)

    // the edges are directional

    SUBCASE("Test with a Vertex"){
        CHECK(v1.isEdgeExists(v3) == true); // (v1, v3)
        CHECK(v3.isEdgeExists(v1) == false); // (v3, v1)
        CHECK(v2.isEdgeExists(v2) == false); // (v2, v2)
        CHECK(v2.isEdgeExists(v1) == true); // (v2, v1)
    }
    SUBCASE("Test with a Vertex name"){
        CHECK(v1.isEdgeExists(2) == true); // (v1, v3)
        CHECK(v3.isEdgeExists(0) == false); // (v3, v1)
        CHECK(v2.isEdgeExists(1) == false); // (v2, v2)
        CHECK(v2.isEdgeExists(0) == true); // (v2, v1)
    }
    SUBCASE("Test with an Edge"){
        // creates the relevant edges
        Edge e1 = Edge(0, 2); // (v1, v3)
        Edge e2 = Edge(2, 0); // (v3, v1)
        Edge e3 = Edge(1, 1); // (v2, v2)
        Edge e4 = Edge(1, 0); // (v2, v1)
        
        CHECK(v1.isEdgeExists(e1) == true);
        CHECK(v3.isEdgeExists(e2) == false);
        CHECK(v2.isEdgeExists(e3) == false);
        CHECK(v2.isEdgeExists(e4) == true);
    }
}


TEST_CASE("Test Get Edge"){
    // creates multiple vertices
    Vertex v1 = Vertex(0);
    Vertex v2 = Vertex(1);
    Vertex v3 = Vertex(2);

    // adds the following edges:
    v1.addEdge(v2); // (v1, v2)
    v2.addEdge(v1); // (v2, v1)
    v1.addEdge(v3); // (v1, v3)

    SUBCASE("Get Existing Edge"){
        // the edges being checked
        Edge e1 = Edge(0, 2);
        Edge e2 = Edge(0, 1);
        Edge e3 = Edge(1, 0);

        SUBCASE("Using Vertex"){
            CHECK(v1.getEdge(v3) == e1);
            CHECK(v1.getEdge(v2) == e2);
            CHECK(v2.getEdge(v1) == e3);
        }
        SUBCASE("Using vertex name"){
            CHECK(v1.getEdge(2) == e1);
            CHECK(v1.getEdge(1) == e2);
            CHECK(v2.getEdge(0) == e3);
        }
    }

    SUBCASE("Get Non Existing Edge"){        
        SUBCASE("Using Vertex"){
            CHECK_THROWS(v3.getEdge(v2)); 
            CHECK_THROWS(v3.getEdge(v1));
            CHECK_THROWS(v2.getEdge(v3));
        }
        SUBCASE("Using vertex name"){
            SUBCASE("Using valid vertex name"){
                CHECK_THROWS(v1.getEdge(4)); // an edge to a non existing vertex
                CHECK_THROWS(v3.getEdge(0)); // a non existing edge
            }
            SUBCASE("Using invalid vertex name"){
                CHECK_THROWS(v1.getEdge(-3));
            }
        }
    }
}

TEST_CASE("Test Get Edges"){
    Vertex v = Vertex(0);

    List<Edge> list_edges = List<Edge>(); // creates a list of edges
    for(int i=0; i<10; i++){
        // creates an edge
        Edge e = Edge(0, i, i);

        // adds it to the list 
        list_edges.insert(e);

        // adds the edge to v
        v.addEdge(Vertex(i), i);
    }

    // checks that the edges in v are the same as the edges created
    const List<Edge> &edges = v.getEdges();

    CHECK(edges.size() == list_edges.size());
    for(int i=0; i<list_edges.size(); i++){
        const Edge &e = list_edges.getValue(i);
        // checks that edges contains e
        CHECK(edges.isExists(e) == true);
    }
}

TEST_CASE("Test operator== and operator!="){
    SUBCASE("Exact same Vertex"){
        Vertex v = Vertex(0);
        
        SUBCASE("No Edges"){
            CHECK(v == v);
            CHECK((v != v) == false);
        }
        SUBCASE("Has Edges"){
            for(int i=0; i<10; i++){
                v.addEdge(i, i);
            }
            CHECK(v == v);
            CHECK((v != v) == false);
        }

    }
    SUBCASE("Exact Replica"){
        Vertex v1 = Vertex(0);
        Vertex v2 = Vertex(0);
        
        SUBCASE("No Edges"){
            CHECK(v1 == v2);
            CHECK((v1 != v2) == false);
        }
        SUBCASE("Has Edges"){
            for(int i=0; i<10; i++){
                v1.addEdge(i, i);
                v2.addEdge(i, i);
            }
            CHECK(v1 == v2);
            CHECK((v1 != v2) == false);
        }
    }
    SUBCASE("Different Number of Edges"){
        Vertex v1 = Vertex(0);
        Vertex v2 = Vertex(0);

        // adds edges only to v1
        for(int i=0; i<10; i++)
            v1.addEdge(i, i);

        CHECK((v1 == v2) == false);
        CHECK(v1 != v2);
    }
    SUBCASE("1 Different Edge"){
        Vertex v1 = Vertex(0);
        Vertex v2 = Vertex(0);

        // adds edges only to v1
        for(int i=0; i<10; i++){
            v1.addEdge(i, i);
            v2.addEdge(i, i);
        }

        // adds another vertex to v2
        v2.addEdge(10, 10);

        CHECK((v1 == v2) == false);
        CHECK(v1 != v2);
    }
    SUBCASE("Different vertices"){
        Vertex v1 = Vertex(0);
        Vertex v2 = Vertex(1);

        CHECK((v1 == v2) == false);
        CHECK(v1 != v2);
    }
}

TEST_CASE("Memory Leak Test"){
    Vertex *v = new Vertex(0);

    // add multiple edges to v
    for(int i=0; i<10; i++)
        v->addEdge(i, i);
    
    // remove multiple edges
    v->removeEdge(Vertex(0));
    v->removeEdge(Vertex(5));
    v->removeEdge(Vertex(8));

    // delete the vertex
    delete v;
}