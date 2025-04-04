#include "edge.hpp"

Edge::Edge(int vertex1, int vertex2, int weight):
v{vertex1},
u{vertex2},
weight{weight}
{
    #ifdef DEBUG
    std::cout << "Edge constructor" << std::endl;
    #endif

    // if vertex 1 is a negative number, throw an error
    if(vertex1<0)
        throw std::invalid_argument{"vertex1 cannot be negative"};

    // if vertex 2 is a negative number, throw an error
    if(vertex2<0)
        throw std::invalid_argument{"vertex2 cannot be negative"};
}

bool Edge::operator== (const Edge &e) const{
    // the graph is undirectional and so two edges will be equal if they go through the same vertices
    // even if they have different weights
    if(this->v == e.getVertex1() && this->u == e.getVertex2())
        return true;
    
    if(this->u == e.getVertex1() && this->v == e.getVertex2())
        return true;
    
    return false;
}