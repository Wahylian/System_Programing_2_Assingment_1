#include "edge.hpp"

bool Edge::isSameEdge(Edge e){
    // if v1 of e is equal to v1 and v2 of e is equal to v2, they are the same edge
    if(e.getVertex1() == this->v1 && e.getVertex2() == this->v2)
        return true;
    // else they are a different edge
    return false;
}

Edge Edge::getCompliment(){
    return Edge(this->v2, this->v1, this->weight);
}