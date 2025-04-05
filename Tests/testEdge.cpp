#include "doctest.h"
#include "../Graphs/edge.hpp"

TEST_CASE("Edge initialization"){
    // checks creating an edge with negative vertices
    SUBCASE("Testing Negative Vertices"){
        // checking with 2 negative edges
        CHECK_THROWS(Edge(-1, -2));

        // checking with 1 negative edge
        CHECK_THROWS(Edge(5, -4));
        CHECK_THROWS(Edge(0, -10));
    }

    // checks creating an edge with valid vertices
    SUBCASE("Testing valid creation"){
        CHECK_NOTHROW(Edge(0, 5));
        CHECK_NOTHROW(Edge(1, 3));
    }

    // since the edge is built for a directional graph, checks creating an edge from a vertex to itself is permitted
    SUBCASE("Testing Edge to self"){
        CHECK_NOTHROW(Edge(1, 1));
        CHECK_NOTHROW(Edge(0,0));
    }

    // checks creation with non-default weight
    SUBCASE("Testing Edge with weight"){
        CHECK_NOTHROW(Edge(0, 1, 5)); // positive weight
        CHECK_NOTHROW(Edge(0, 0, 10)); // edge (v,v) with positive weight
        CHECK_NOTHROW(Edge(5, 2, -2)); // negative weight
        CHECK_NOTHROW(Edge(1, 7, 0)); // zero weight edge
    }
}

TEST_CASE("Test Copy Constructor"){
    // create a new edge
    Edge *e = new Edge(0, 6, 3);
    // create a copy of the edge
    Edge *copy = new Edge(*e);

    // check that the pointers point to different addresses
    CHECK(e != copy);

    // checks that the values in e and copy are the same
    CHECK(e->getVertex1() == copy->getVertex1());
    CHECK(e->getVertex2() == copy->getVertex2());
    CHECK(e->getWeight() == copy->getWeight());

    // checks that changing the weight in the copy doesn't affect the original
    copy->setWeight(8);
    CHECK(copy->getWeight() == 8);
    CHECK(e->getWeight() == 3);

    // deletes both edges
    delete e;
    delete copy;
}

TEST_CASE("Getters"){
    SUBCASE("Get vertex1"){
        Edge e = Edge(1, 4);
        CHECK(e.getVertex1() == 1);
    }
    SUBCASE("Get vertex2"){
        Edge e = Edge(10, 0);
        CHECK(e.getVertex2() == 0);
    }
    SUBCASE("Get weight- default weight"){
        Edge e = Edge(3, 5);
        CHECK(e.getWeight() == 1);
    }
    SUBCASE("Get weight- non default"){
        Edge e = Edge(1, 10, 3);
        CHECK(e.getWeight() == 3); // positive weight

        e = Edge(2, 9, 0);
        CHECK(e.getWeight() == 0); // zero weight

        e = Edge(0, 3, -3);
        CHECK(e.getWeight() == -3); // negative weight
    }
}

TEST_CASE("Set Weight"){
    // set the weight to a positive integer
    SUBCASE("Set Positive"){
        Edge e = Edge(1, 5, 2);
        e.setWeight(10);

        CHECK(e.getWeight() == 10);
    }
    // set the weight to zero
    SUBCASE("Set Zero Weight"){
        Edge e = Edge(2, 1, 8);
        e.setWeight(0);

        CHECK(e.getWeight() == 0);
    }
    // set the weight to a negative integer
    SUBCASE("Set Negative"){
        Edge e = Edge(5, 7, 4);
        e.setWeight(-3);

        CHECK(e.getWeight() == -3);
    }
}

TEST_CASE("Test operator== and operator!="){
    // checks the exact same edge (down to the address)
    SUBCASE("Exact same Edge"){
        Edge e = Edge(1, 5);
        CHECK(e == e);
        CHECK((e != e) == false);
    }
    // checks the same edge 
    SUBCASE("Exact Replica"){
        Edge e1 = Edge(4, 2, 9);
        Edge e2 = Edge(4, 2, 9);
        CHECK(e1 == e2);
        CHECK((e1 != e2) == false);
    }
    // checks the same edge, different weights
    SUBCASE("Same vertices, Different Weight"){
        Edge e1 = Edge(1, 7, -1);
        Edge e2 = Edge(1, 7, 4);
        CHECK(e1 == e2);
        CHECK((e1 != e2) == false);
    }
    // checks edges going out of the same vertex to a different second vertices
    SUBCASE("Vertex 1 is Same, Vertex 2 Different"){
        SUBCASE("Same Weight"){
            // same weight
            Edge e1 = Edge(5, 6);
            Edge e2 = Edge(5, 9);
            CHECK((e1 == e2) == false);
            CHECK(e1 != e2);
        }
        SUBCASE("Different Weight"){
            // differnt weight
            Edge e1 = Edge(2, 5); 
            Edge e2 = Edge(2, 10, -1); 
            CHECK((e1 == e2) == false);
            CHECK(e1 != e2);
        }
    }
    // checks edges going out of different vertices into the same second vertex
    SUBCASE("Vertex 1 Different, Vertex 2 is Same"){
        SUBCASE("Same Weight"){
            // same weight
            Edge e1 = Edge(5, 6);
            Edge e2 = Edge(9, 6);
            CHECK((e1 == e2) == false);
            CHECK(e1 != e2);
        }
        SUBCASE("Different Weight"){
            // differnt weight
            Edge e1 = Edge(5, 2); 
            Edge e2 = Edge(3, 2, -1); 
            CHECK((e1 == e2) == false);
            CHECK(e1 != e2);
        }
    }
    // checks completely different edges
    SUBCASE("Both Vertices Different"){ 
        // edges on different vertices with the same weight
        SUBCASE("Same Weight"){
            Edge e1 = Edge(0, 4);
            Edge e2 = Edge(3, 8);
            CHECK((e1 == e2) == false);
            CHECK(e1 != e2);
        }
        // edges on differnt vertices with different weights
        SUBCASE("Different Weight"){
            Edge e1 = Edge(1, 9, -1);
            Edge e2 = Edge(2, 0);
            CHECK((e1 == e2) == false);
            CHECK(e1 != e2);
        }
    }
    // checks an edge and its compliment edge
    SUBCASE("Edge and Compliment Edge"){
        Edge e1 = Edge(3, 6);
        Edge e2 = Edge(6, 3);
        CHECK((e1 == e2) == false);
        CHECK(e1 != e2);
    }
}

TEST_CASE("Test Memory Leak"){
    // creates a new instance of edge
    Edge *e = new Edge(0, 6);

    // changes it's weight
    e->setWeight(5);

    // deletes the edge
    delete e;
}