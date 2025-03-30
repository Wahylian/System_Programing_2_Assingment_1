#include "tuple.hpp"

class Edge{
    private:
    unsigned int v1;
    unsigned int v2;
    int weight;

    public:
    // constructor
    Edge(unsigned int vertex1, unsigned int vertex2, int weight=1):
    v1{vertex1},
    v2{vertex2},
    weight{weight}
    {}

    // returns vertex 1
    unsigned int getVertex1(){return this->v1;}

    // returns vertex 2
    unsigned int getVertex2(){return this->v2;}

    // returns the wieght of the edge
    int getWeight(){return this->weight;}

    // sets the weight of the edge
    void setWeight(int weight){this->weight = weight;}

    // returns true if the edge is between the same 2 vertices
    bool isSameEdge(Edge e);

    // returns the compliment edge of this
    Edge getCompliment();
};