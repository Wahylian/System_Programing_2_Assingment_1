#include "vertex.hpp"

Vertex::Vertex(int vertex_name):
vertex_name{vertex_name},
edges{List<Edge>()}
{
    #ifdef DEBUG
    std::cout << "Vertex constructor" << std::endl;
    #endif
    // the name of the vertex must be none negative
    if(vertex_name < 0)
        throw std::invalid_argument{"vertex_name must be none negative"};
}

bool Vertex::isEdgeExists(const Vertex &v) const{
    return this->isEdgeExists(v.getVertexName());
}

bool Vertex::isEdgeExists(int v) const{
    // if the vertex is negative, throw error
    if(v < 0)
        throw std::invalid_argument{"vertex v must be none negative"};

    // searches if the edge exists in this list of edges
    return this->edges.isExists(Edge(this->vertex_name, v));
}

Edge Vertex::getEdge(const Vertex &v) const{
    int vx = v.getVertexName(); // gets the name of v

    // finds the index of the edge between this and vx
    int index = this->edges.find(Edge(this->vertex_name, vx));

    // if the edge doesn't exist, throw an error
    if(index == -1)
        throw std::out_of_range{"edge doesn't exist"};
    
    // if the edge exists, returns a copy of it
    Edge &e = this->edges.getValue(index);
    return ;
}