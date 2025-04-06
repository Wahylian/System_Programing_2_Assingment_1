// rido1607@gmail.com
#pragma once
#include "graph.hpp"
#include "../DSs/reversePriorityQueue.hpp"
#include "../DSs/unionFind.hpp"
namespace graph{
    class Algorithms{
        private:
        // finds all undiscovered vertices in g that are reachable from v and adds the edges among the path to them to edges
        void dfsVisit(const Graph& g, int vx, List<int>& whites, List<int>& grays, List<int>& blacks, List<Edge>& edges);
    
        // relaxes an edge
        void relax(const Edge& e, List<int>& pi, List<int>& d, RevPriorityQueue<int>& q);
    
        public:
        // constructor
        Algorithms(){}
    
        // algorithms
    
        // recieves a graph and a starting vertex and returns a bfs graph from that vertex
        Graph bfs(const Graph &g, int s);
    
        // recieves a graph and returns a dfs graph 
        Graph dfs(const Graph &g);
    
        // recieves a graph and a starting vertex and returns a graph of shortest paths to all vertices in the graph
        // uses dijkstra
        Graph dijkstra(const Graph &g, int s);
    
        // recieves a graph and creates a minimal spanning tree of that graph
        // uses prim's algorithm
        Graph prim(const Graph &g);
    
        // recieves a graph and creates a minimal spanning tree of that graph
        // uses kruskal's algorithm
        Graph kruskal(const Graph &g);
    };
}
