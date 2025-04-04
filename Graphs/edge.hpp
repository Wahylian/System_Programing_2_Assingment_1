#ifndef EDGE
#define EDGE
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif
#include <stdexcept>
class Edge{
    private:
    int v;
    int u;
    int weight;

    public:
    // constructor
    Edge(int vertex1, int vertex2, int weight=1);

    // returns vertex 1
    int getVertex1() const{return this->v;}

    // returns vertex 2
    int getVertex2() const {return this->u;}

    // returns the wieght of the edge
    int getWeight() const {return this->weight;}

    // sets the weight of the edge
    void setWeight(int weight){this->weight = weight;}

    // checks if two edges are equal
    bool operator==(const Edge &e) const;
};
#endif