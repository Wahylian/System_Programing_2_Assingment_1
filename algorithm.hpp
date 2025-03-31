#include "graph.hpp"
#include "DataStructures/reversePriorityQueue.hpp"
#include "DataStructures/unionFind.hpp"

class Algorithms{
    private:
    // finds all undiscovered vertices in g that are reachable from v and adds the edges among the path to them to edges
    void dfsVisit(Graph& g, unsigned int vx, List<unsigned int>& whites, List<unsigned int>& grays, List<unsigned int>& blacks, List<Edge>& edges);

    // relaxes an edge
    void relax(Edge& e, List<int>& pi, List<unsigned int>& d, RevPriorityQueue<unsigned int>& q);

    public:
    // constructor
    Algorithms(){}

    // algorithms

    // recieves a graph and a starting vertex and returns a bfs graph from that vertex
    Graph bfs(Graph g, unsigned int s);

    // recieves a graph and returns a dfs graph 
    Graph dfs(Graph g);

    // recieves a graph and a starting vertex and returns a graph of shortest paths to all vertices in the graph
    // uses dijakstra
    Graph dijakstra(Graph g, unsigned int s);

    // recieves a graph and creates a minimal spanning tree of that graph
    // uses prim's algorithm
    Graph prim(Graph g);

    // recieves a graph and creates a minimal spanning tree of that graph
    // uses kruskal's algorithm
    Graph kruskal(Graph g);
};