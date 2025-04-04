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
    // returns true if both edges go from vertex v to vertex u
    // ignores weight
    if(this->v == e.getVertex1() && this->u == e.getVertex2())
        return true;

    return false;
}

bool Edge::operator!= (const Edge &e) const{
    // returns true if == returns false, else true
    return !(*this == e);
}

std::string Edge::to_string() const{
    std::string s = "(" + std::to_string(this->getVertex1());
    s += ", " + std::to_string(this->getVertex2()) +")";
    s += " Weight: "+ std::to_string(this->getWeight());
    return s;
}