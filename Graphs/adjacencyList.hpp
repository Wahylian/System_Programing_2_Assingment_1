#ifndef NEIGHBORLIST
#define NEIGHBORLIST
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/

#include "vertex.hpp"
#include "../DSs/list.hpp"
#include <stdexcept>
#include <iostream>

class AdjacencyList{
    private:
    int n; // the num of vertices in the Adjacency
    List<Vertex> vertices;

    public:
    // creates a Adjacency list for num_vx vertices
    AdjacencyList(int num_vx);

    // returns the amount of vertices in the adjacency list
    int getNumVx() const{return this->n;}

    // adds an edge between vertex v1 and vertex v2 of weight weight, replaces existing edge
    void addEdge(int v1, int v2, int weight=1);

    // remove edge between v1 and v2, if the edge doesn't exist throws an error
    void removeEdge(int v1, int v2);

    // returns vertex v
    const Vertex& getVertex(int v) const;

    // prints the list
    void print() const;
};
#endif