#pragma once
#include <iostream>
#include "adjacencyList.hpp"

// a class representing a non-directional graph
class Graph{
    private:
    int _n; // the amount of vertices in the graph
    AdjacencyList _al;

    // returns true if v is a valid vertex in this graph, else false
    bool isValidVertex(int v){return v >= 0 && v < this->_n;}

    public:
    // constructor
    Graph(int num_vx);

    // copy constructor
    Graph(const Graph &g);

    // base functions:

    // adds an edge between v and u of the provided weight
    void addEdge(int v, int u, int weight=1);

    // adds an edge to the graph
    void addEdge(const Edge &e);

    // removes an edge between v and u, throws an error if there is no edge between them
    void removeEdge(int v, int u);

    // prints the graph
    void print_graph() const;

    // extra functions:
    // returns a list of all edges in the graph
    List<Edge> getEdges() const;

    // returns a reference to vertex v from the graph
    const Vertex& getVertex(int v) const {return this->_al.getVertex(v);}

    // returns true if the edge exists, else false
    bool isEdgeExists(int v, int u) const;

    // returns true if the edge exists, else false
    bool isEdgeExists(const Edge &e) const;

    // returns the number of vertices in the graph
    int numVertices() const {return this->_n;}

    // returns the number of edges in the graph
    int numEdges() const;
};