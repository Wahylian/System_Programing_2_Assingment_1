// rido1607@gmail.com
#pragma once
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/

#include "vertex.hpp"
#include "../DSs/list.hpp"
#include <stdexcept>
#include <iostream>

class AdjacencyList{
    private:
    int _n; // the num of vertices in the AdjacencyList
    int _m; // the num of edges in the AdjacencyList
    List<Vertex> _vertices;

    public:
    // constructor
    AdjacencyList(int num_vx);

    // copy constructor
    AdjacencyList(const AdjacencyList &al);

    // returns the amount of vertices in the adjacency list
    int getNumVx() const{return this->_n;}

    // returns the amount of edges in the adjacency list
    int getNumEdges() const{return this->_m;}

    // adds an edge between vertex v1 and vertex v2 of weight weight, replaces existing edge
    void addEdge(int v1, int v2, int weight=1);

    // remove edge between v1 and v2, if the edge doesn't exist throws an error
    void removeEdge(int v1, int v2);

    // returns true if the edge (v1, v2) exists, else false
    bool isEdgeExists(int v1, int v2) const;

    // returns vertex v
    const Vertex& getVertex(int v) const;

    // prints the list
    void print() const;
};