#ifndef GRAPH
#define GRAPH
#include <iostream>

#include "vertex.hpp"
#include "edge.hpp"
#include "../DSs/adjacencyList.hpp"

// a class representing a graph
class Graph{
    private:
    unsigned int n; // the amount of vertices in the graph
    AdjacencyList al;

    // returns true if v is a valid vertex in this graph, else false
    bool isValidVertex(unsigned int v){return v < this->n;}

    public:
    // construction function
    Graph(unsigned int num_vx):
        n{num_vx},
        al{AdjacencyList(num_vx)}
    {}

    // base functions:

    // adds an edge between v and u of the provided weight
    void addEdge(unsigned int v, unsigned int u, int weight=1);

    // adds an edge to the graph
    void addEdge(Edge e);

    // removes an edge between v and u, throws an error if there is no edge between them
    void removeEdge(unsigned int v, unsigned int u){this->al.removeEdge(v,u);}

    // prints the graph
    void print_graph(){this->al.print();}

    // extra functions:
    // returns a list of all edges in the graph
    List<Edge> getEdges();

    // returns a reference to vertex v from the graph
    const Vertex& getVertex(unsigned int v){return this->al.getVertex(v);}

    // returns the number of vertices in the graph
    unsigned int getSize(){return this->n;}
};
#endif