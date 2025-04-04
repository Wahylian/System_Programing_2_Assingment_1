#ifndef NEIGHBORLIST
#define NEIGHBORLIST
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/

#include "../Graphs/vertex.hpp"
#include "list.hpp"
#include <stdexcept>
#include <iostream>

class AdjacencyList{
    private:
    unsigned int n; // the num of vertices in the Adjacency
    List<Vertex> vertices;

    public:
    // creates a Adjacency list for num_vx vertices
    AdjacencyList(unsigned int num_vx);
    
    // destructor
    ~AdjacencyList();

    // adds an edge between vertex v1 and vertex v2 of weight weight 
    void addEdge(unsigned int v1, unsigned int v2, int weight=1);

    // remove edge between v1 and v2, if the edge doesn't exist throws an error
    void removeEdge(unsigned int v1, unsigned int v2);

    // returns vertex v
    Vertex& getVertex(unsigned int v){return this->vertices.getValue(v);}

    // prints the list
    void print();
};
#endif