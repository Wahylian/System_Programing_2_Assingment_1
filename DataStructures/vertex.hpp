#include "list.hpp"
#include "edge.hpp"
#include <stdexcept>
#include <iostream>

// this class represents a vertex
// it is built for a directional graph
class Vertex{
    private:
    unsigned int vertex_name;
    unsigned int num_edges; // on default there will be zero edges
    List<Edge> *edges; // the list of all edges of this vertex

    public:
    // constructor
    Vertex(unsigned int vertex_name)
        :
        vertex_name{vertex_name},
        num_edges{0},
        edges{new List<Edge>()}
    {}
    // destructor
    ~Vertex(){
        delete this->edges;
    }

    // returns the name of the vertex
    unsigned int getVertexName(){return this->vertex_name;}

    // returns the number of edges that the vertex has
    unsigned int getNumEdges(){return this->num_edges;}

    // returns true if there is an edge from this vertex to v
    bool isEdgeExists(Vertex v);

    // returns the edge from this vertex to v
    Edge getEdge(Vertex v);

    // returns all edges from this vertex
    List<Edge> getEdges();

    // adds an edge from this vertex to v of weight weight
    // if a vertex between the two already exist, overrides the weight
    void addEdge(Vertex v, int weight=1);

    // removes the edge between this vertex and v
    Edge removeEdge(Vertex v);

    // prints the information of this vertex
    void print();
};