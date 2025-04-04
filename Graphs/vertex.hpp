#ifndef VERTEX
#define VERTEX
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif
#include <stdexcept>
// including the list class to store the edges of v
#include "../DSs/list.hpp"

// includes the edge class save the edges of v
#include "edge.hpp"

// this class represents a vertex
// it is built for a directional graph
class Vertex{
    private:
    int vertex_name;
    List<Edge> edges; // the list of all edges of this vertex

    public:
    // constructor
    Vertex(int vertex_name);    

    // returns the name of the vertex
    int getVertexName() const {return this->vertex_name;}

    // returns the number of edges that the vertex has
    int getNumEdges() const {return this->edges.size();}

    // returns true if there is an edge from this vertex to v
    bool isEdgeExists(const Vertex& v) const;

    // returns true if there is an edge from this vertex to v
    bool isEdgeExists(int v) const;

    // returns the edge from this vertex to v
    Edge getEdge(const Vertex& v) const;

    // returns a reference to all edges from this vertex
    const List<Edge>& getEdges();

    // adds an edge from this vertex to v of weight weight
    // if a vertex between the two already exist, overrides the weight
    void addEdge(Vertex &v, int weight=1);

    // removes the edge between this vertex and v
    Edge removeEdge(Vertex &v);

    // prints the information of this vertex
    void print();
};
#endif