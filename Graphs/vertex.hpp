#pragma once
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif
#include <stdexcept>
#include <iostream>
#include "../DSs/list.hpp"
#include "edge.hpp"

// this class represents a vertex
// it is built for a directional graph
class Vertex{
    private:
    int _vertex_name;
    List<Edge> _edges; // the list of all edges of this vertex

    public:
    // constructor
    Vertex(int vertex_name);   
    
    // copy constructor
    Vertex(const Vertex &v);

    // returns the name of the vertex
    int getVertexName() const {return this->_vertex_name;}

    // returns the number of edges that the vertex has
    int getNumEdges() const {return this->_edges.size();}

    // returns true if there is an edge from this vertex to v
    bool isEdgeExists(const Vertex& v) const;

    // returns true if there is an edge from this vertex to v
    bool isEdgeExists(int v) const;

    // returns true if there is an edge e in this vertex
    bool isEdgeExists(const Edge &e) const;

    // returns the edge from this vertex to v
    const Edge& getEdge(const Vertex& v) const;

    // returns the edge from this vertex to v
    const Edge& getEdge(int v) const;

    // returns a reference to all edges from this vertex
    const List<Edge>& getEdges() const;

    // adds an edge from this vertex to v of weight weight
    // if an edge between the two already exists, overrides the weight
    void addEdge(const Vertex &v, int weight=1);
    // NOTE: Since the vertex is built for a directional graph, an edge from a vertex to itself is premitted

    // adds an edge from this vertex to v of weight weight
    // if an edge between the two already exists, overrides the weight
    void addEdge(int v, int weight=1);

    // adds the edge to this vertex
    void addEdge(const Edge &e);

    // removes the edge between this vertex and v
    // if the edge doesn't exist, throw an error
    Edge removeEdge(const Vertex &v);

    // prints the information of this vertex
    void print() const;

    // returns true if this and v are the same, else false
    bool operator== (const Vertex &v) const; 

    // returns false if this and v are the same, else true
    bool operator!= (const Vertex &v) const;
};