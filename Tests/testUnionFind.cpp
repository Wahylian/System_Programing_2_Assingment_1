#include "doctest.h"
#include "../DSs/unionFind.hpp"

TEST_CASE("Initializing the UnionFind"){
    SUBCASE("A legal Initialization"){
        // a unionfind must be built using a positive number of vertices
        CHECK_NOTHROW(UnionFind(10));
    }

    SUBCASE("An illegal Intialization"){
        // a unionfind cannot be built with a non positive number of vertices
        CHECK_THROWS(UnionFind(0)); // creating with 0 vertices

        CHECK_THROWS(UnionFind(-5)); // creating with a negative amount of vertices
    }
}

TEST_CASE("Test Find Function"){
    // attempts to find a vertex outside the parameters of the unionfind
    SUBCASE("Find a none existing vertex"){
        UnionFind uf = UnionFind(10);

        // checks to find a negative vertex
        CHECK_THROWS(uf.Find(-1));

        // checks for a vertex not in the unionfind
        CHECK_THROWS(uf.Find(10));
    }

    // attempts to find a vertex in the unionfind, when it is the head of it's set
    SUBCASE("Find a vertex, head of set"){
        UnionFind uf = UnionFind(5);

        // finds the head of 2
        CHECK(uf.Find(2) == 2);

        // finds the head of 0
        CHECK(uf.Find(0) == 0);
    }

    // attempts to find the head of the set a vertex is in, where it is not the head of the set
    SUBCASE("Find a vertex, not head of set"){
        UnionFind uf = UnionFind(5);

        // unions vertices 0, 2, and 4
        uf.Union(0,2);
        uf.Union(2,4);

        // finds the head of 4
        CHECK(uf.Find(4) == 0);

        // finds the head of 2
        CHECK(uf.Find(2) == 0);

        // finds the head of 3
        CHECK(uf.Find(3) == 3);
    }
}

TEST_CASE("Test Union Function"){
    SUBCASE("Union between 2 non existing vertices"){
        UnionFind uf = UnionFind(5);

        CHECK_THROWS(uf.Union(-1, 5));// both of these vertices are not in the unionfind
    }

    SUBCASE("Union between 1 non existing vertex and 1 existing vertex"){
        UnionFind uf = UnionFind(5);
        
        CHECK_THROWS(uf.Union(-1, 2)); // the first vertex isn't in the unionfind

        CHECK_THROWS(uf.Union(3, 7)); // the second vertex isn't in the unionfind
    }

    SUBCASE("Union between 2 exisiting vertices"){
        UnionFind uf = UnionFind(5);

        // checks that both vertices are their own heads of sets
        CHECK(uf.Find(4) == 4);
        CHECK(uf.Find(1) == 1);

        // unions 4 and 1
        CHECK_NOTHROW(uf.Union(4,1));

        // checks that the head of 1 is the head of 4
        CHECK(uf.Find(1) == uf.Find(4));
    }

    // unions all vertices into the same set
    SUBCASE("All Vertices in one Set"){
        UnionFind uf = UnionFind(4);

        // checks all vertices are their own heads of sets
        for(int i=0; i<4; i++)
            CHECK(uf.Find(i) == i);
        
        // unions all vertices such that 2 is the head of their combined set
        uf.Union(0,1); // makes 0 the head of 1
        uf.Union(2,3); // makes 2 the head of 3 
        uf.Union(2,1); // makes 2 the head of 1

        // checks all vertices are in the same set and that their head is 2
        for(int i=0; i<4; i++)
            CHECK(uf.Find(i) == 2);
    }
}

TEST_CASE("Memory Leak Test"){
    // creates a new instance of unionfind
    UnionFind *uf = new UnionFind(5);

    // unions some of the vertices
    uf->Union(2,1);
    uf->Union(2,3);
    uf->Union(4,2);

    // checks the union is in the following state:
    // {_0_}, {_4_, 2, 3, 1} (meaning 0 is the head of itself, and 4 is the head of the set containing the rest)
    CHECK(uf->Find(0) == 0);
    for(int i = 1; i<5; i++)
        CHECK(uf->Find(i) == 4);
    
    // delete the unionfind
    delete uf;
}