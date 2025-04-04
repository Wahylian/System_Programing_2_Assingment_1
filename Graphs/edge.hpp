#ifndef EDGE
#define EDGE
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif
#include <stdexcept>
#include <string>
class Edge{
    private:
    int v;
    int u;
    int weight;

    public:
    // constructor
    Edge(int vertex1, int vertex2, int weight=1); 
    // NOTE: since the edge is built for a directional graph, an edge from a vertex to itself is allowed

    // returns vertex 1
    int getVertex1() const{return this->v;}

    // returns vertex 2
    int getVertex2() const {return this->u;}

    // returns the wieght of the edge
    int getWeight() const {return this->weight;}

    // sets the weight of the edge
    void setWeight(int weight){this->weight = weight;}

    // returns true if this and e are the same, else false
    bool operator==(const Edge &e) const;

    // returns false if this and e are the same, else true
    bool operator!=(const Edge &e) const;

    // returns a string representation of the edge
    std::string to_string() const;
};
#endif