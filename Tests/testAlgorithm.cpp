// rido1607@gmail.com
#include "doctest.h"
#include "../Graphs/graph.hpp"
#include "../Graphs/algorithm.hpp"
using namespace graph;

TEST_CASE("Run on Empty Graph"){
    Graph g = Graph(0); // creates a graph with 0 vertices
    Algorithms alg = Algorithms();

    SUBCASE("BFS"){
        // since the graph is empty, it throws an error as there is no valid starting vertex
        CHECK_THROWS(alg.bfs(g, 0));
    }
    SUBCASE("DFS"){
        CHECK_NOTHROW(alg.dfs(g));
        // gets the dfs graph
        Graph dfs = alg.dfs(g);
        // checks the dfs graph is empty
        CHECK(dfs.numVertices() == 0);
    }
    SUBCASE("dijkstra"){
        // since the graph is empty, it throws an error as there is no valid starting vertex
        CHECK_THROWS(alg.dijkstra(g, 0));
    }
    SUBCASE("Prims"){
        // since the graph is empty, it throws an error as there is no valid starting vertex
        CHECK_THROWS(alg.prim(g));
    }
    SUBCASE("Kruskal"){
        // since the graph is empty, it throws an error as there is no valid starting vertex
        CHECK_THROWS(alg.kruskal(g));
    }
}

TEST_CASE("Run on Full Graph"){
    // creates a graph with 4 verticed
    Graph g = Graph(4);
    // adds all edges to graph - non negative
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 5);
    g.addEdge(0, 3, 0);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 3, 4);
    // creates an instance of the algorithms class
    Algorithms alg = Algorithms();

    SUBCASE("BFS"){
        // create a graph that will be equal to the bfs graph when run on s=0
        Graph bfs_expected = Graph(4);
        bfs_expected.addEdge(0, 1, 1);
        bfs_expected.addEdge(0, 2, 1);
        bfs_expected.addEdge(0, 3, 1);

        // runs bfs on the graph
        Graph bfs = alg.bfs(g, 0);
        // checks the bfs graph is the same as the expected graph
        CHECK(bfs == bfs_expected);
    }
    SUBCASE("DFS"){
        // create a graph that will be equal to the dfs graph when run on s=0
        Graph dfs_expected = Graph(4);
        dfs_expected.addEdge(0, 1, 1);
        dfs_expected.addEdge(1, 2, 1);
        dfs_expected.addEdge(2, 3, 1);

        // runs dfs on the graph
        Graph dfs = alg.dfs(g);
        // checks the dfs graph is the same as the expected graph
        CHECK(dfs == dfs_expected);
    }
    SUBCASE("dijkstra"){
        // create a graph that will be equal to the dijkstra graph when run on s=3
        Graph dijkstra_expected = Graph(4);
        dijkstra_expected.addEdge(3, 0, 0);
        dijkstra_expected.addEdge(0, 1, 2);
        dijkstra_expected.addEdge(1, 2, 1);

        // runs dijkstra on the graph
        Graph dijkstra = alg.dijkstra(g, 3);
        // checks the dijkstra graph is the same as the expected graph
        CHECK(dijkstra == dijkstra_expected);
    }
    SUBCASE("Prim"){
        // create a graph that will be equal to the prim graph
        Graph prim_expected = Graph(4);
        prim_expected.addEdge(0, 1, 2);
        prim_expected.addEdge(1, 2, 1);
        prim_expected.addEdge(0, 3, 0);

        // runs prim on the graph
        Graph prim = alg.prim(g);
        // checks the prim graph is the same as the expected graph
        CHECK(prim == prim_expected);
    }
    SUBCASE("Kruskal"){
        // create a graph that will be equal to the kruskal graph
        Graph kruskal_expected = Graph(4);
        kruskal_expected.addEdge(0, 1, 2);
        kruskal_expected.addEdge(1, 2, 1);
        kruskal_expected.addEdge(0, 3, 0);

        // runs kruskal on the graph
        Graph kruskal = alg.kruskal(g);
        // checks the kruskal graph is the same as the expected graph
        CHECK(kruskal == kruskal_expected);
    }
}

TEST_CASE("Run on Disconnected Graph"){
    // creates a graph
    Graph g = Graph(6);
    // adds edges to graph - non negative
    g.addEdge(0, 1, 4);
    g.addEdge(0, 3, 3);
    g.addEdge(1, 4, 0);
    g.addEdge(2, 5, 1);
    g.addEdge(4, 3, 1);

    // creates an instance of the algorithms class
    Algorithms alg = Algorithms();
    SUBCASE("BFS"){
        // create a graph that will be equal to the BFS graph on s=0
        Graph bfs_expected = Graph(6);
        bfs_expected.addEdge(0, 1, 1);
        bfs_expected.addEdge(0, 3, 1);
        bfs_expected.addEdge(1, 4, 1);

        // runs BFS on the graph
        Graph bfs = alg.bfs(g, 0);
        // checks the BFS graph is the same as the expected graph
        CHECK(bfs == bfs_expected);
    }
    SUBCASE("DFS"){
        // create a graph that will be equal to the DFS graph
        Graph dfs_expected = Graph(6);
        dfs_expected.addEdge(0, 1, 1);
        dfs_expected.addEdge(1, 4, 1);
        dfs_expected.addEdge(4, 3, 1);
        dfs_expected.addEdge(2, 5, 1);

        // runs DFS on the graph
        Graph dfs = alg.dfs(g);

        // checks the DFS graph is the same as the expected graph
        CHECK(dfs == dfs_expected);
    }
    SUBCASE("dijkstra"){
        // create a graph that will be equal to the dijkstra graph when run on s=0
        Graph dijkstra_expected = Graph(6);
        dijkstra_expected.addEdge(1, 4, 0);
        dijkstra_expected.addEdge(4, 3, 1);
        dijkstra_expected.addEdge(0, 3, 3);

        // runs dijkstra on the graph
        Graph dijkstra = alg.dijkstra(g, 0);
        // checks the dijkstra graph is the same as the expected graph
        CHECK(dijkstra == dijkstra_expected);
    }
    SUBCASE("Prim"){
        // create a graph that will be equal to the prim graph
        Graph prim_expected = Graph(6);
        prim_expected.addEdge(1, 4, 0);
        prim_expected.addEdge(0, 3, 3);
        prim_expected.addEdge(3, 4, 1);
        prim_expected.addEdge(2, 5, 1);

        // runs prim on the graph
        Graph prim = alg.prim(g);
        // checks the prim graph is the same as the expected graph
        CHECK(prim == prim_expected);
    }
    SUBCASE("Kruskal"){
        // create a graph that will be equal to the kruskal graph
        Graph kruskal_expected = Graph(6);
        kruskal_expected.addEdge(1, 4, 0);
        kruskal_expected.addEdge(0, 3, 3);
        kruskal_expected.addEdge(3, 4, 1);
        kruskal_expected.addEdge(2, 5, 1);

        // runs kruskal on the graph
        Graph kruskal = alg.kruskal(g);
        // checks the kruskal graph is the same as the expected graph
        CHECK(kruskal == kruskal_expected);
    }
}

TEST_CASE("Run on Graph with a Negative Edges"){
    // create a graph
    Graph g = Graph(5);
    // adds edges to graph - some negative
    g.addEdge(0, 2, -1);
    g.addEdge(0, 3, 1);
    g.addEdge(0, 4, 2);
    g.addEdge(1, 2, 0);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);

    // creates an instance of the algorithms class
    Algorithms alg = Algorithms();

    SUBCASE("BFS"){
        // creates the expected bfs graph when s=0
        Graph bfs_expected = Graph(5);
        bfs_expected.addEdge(0, 2, 1);
        bfs_expected.addEdge(0, 3, 1);
        bfs_expected.addEdge(0, 4, 1);
        bfs_expected.addEdge(2, 1, 1);

        // runs bfs on the graph
        Graph bfs = alg.bfs(g, 0);
        // checks the bfs graph is the same as the expected graph
        CHECK(bfs == bfs_expected);
    }
    SUBCASE("DFS"){
        // creates the expected dfs graph
        Graph dfs_expected = Graph(5);
        dfs_expected.addEdge(0, 2, 1);
        dfs_expected.addEdge(2, 1, 1);
        dfs_expected.addEdge(1, 3, 1);
        dfs_expected.addEdge(0, 4, 1);

        // runs dfs on the graph
        Graph dfs = alg.dfs(g);
        // checks the dfs graph is the same as the expected graph
        CHECK(dfs == dfs_expected);
    }
    SUBCASE("dijkstra"){
        // checks that an error is thrown
        // as dijkstra doesn't allow for negative edges
        CHECK_THROWS(alg.dijkstra(g, 0));
    }
    SUBCASE("Prim"){
        // creates the expected prim graph
        Graph prim_expected = Graph(5);
        prim_expected.addEdge(0,2,-1);
        prim_expected.addEdge(0,3,1);
        prim_expected.addEdge(0,4,2);
        prim_expected.addEdge(2,1,0);

        // runs prim on the graph
        Graph prim = alg.prim(g);
        // checks the prim graph is the same as the expected graph
        CHECK(prim == prim_expected);
    }
    SUBCASE("Kruskal"){
        // creates the expected kruskal graph
        Graph kruskal_expected = Graph(5);
        kruskal_expected.addEdge(0,2,-1);
        kruskal_expected.addEdge(0,3,1);
        kruskal_expected.addEdge(0,4,2);
        kruskal_expected.addEdge(2,1,0);

        // runs kruskal on the graph
        Graph kruskal = alg.kruskal(g);
        // checks the kruskal graph is the same as the expected graph
        CHECK(kruskal == kruskal_expected);
    }
}
