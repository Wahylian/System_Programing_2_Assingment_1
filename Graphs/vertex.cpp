#include "vertex.hpp"

Vertex::Vertex(int vertex_name):
_vertex_name{vertex_name},
_edges{List<Edge>()}
{
    #ifdef DEBUG
    std::cout << "Vertex constructor" << std::endl;
    #endif
    // the name of the vertex must be none negative
    if(vertex_name < 0)
        throw std::invalid_argument{"vertex_name must be none negative"};
}

Vertex::Vertex(const Vertex &v):
_vertex_name{v._vertex_name},
_edges{List<Edge>(v.getEdges())}
{ 
    // nothing to do here
}

bool Vertex::isEdgeExists(const Vertex &v) const{
    return this->isEdgeExists(v.getVertexName());
}

bool Vertex::isEdgeExists(int v) const{
    // if the vertex is negative, throw error
    if(v < 0)
        throw std::invalid_argument{"vertex v must be none negative"};

    // searches if the edge exists in this list of edges
    return this->_edges.isExists(Edge(this->_vertex_name, v));
}

bool Vertex::isEdgeExists(const Edge &e) const{
    // searches if the edge exists in this list of edges
    return this->_edges.isExists(e);
}

const Edge& Vertex::getEdge(const Vertex &v) const{
    int vx = v.getVertexName(); // gets the name of v
    return this->getEdge(vx);
}

const Edge& Vertex::getEdge(int v) const{
    // if the vertex is negative throw an error
    if(v < 0)
        throw std::invalid_argument{"vertex v must be none negative"};
    
    // finds the index of the edge between this and vx
    int index = this->_edges.find(Edge(this->_vertex_name, v));

    // if the edge doesn't exist, throw an error
    if(index == -1)
        throw std::out_of_range{"edge doesn't exist"};
    
    // if the edge exists, returns a copy of it
    return this->_edges.getValue(index);
}

const List<Edge>& Vertex::getEdges() const{
    return this->_edges;
}

void Vertex::addEdge(const Vertex &v, int weight){
    // adds edge
    this->addEdge(v.getVertexName(), weight);
}

void Vertex::addEdge(int v, int weight){
    if(v < 0)
        throw std::invalid_argument{"vertex v must be none negative"};
    
    // creates an edge from this vertex to v
    Edge e = Edge(this->_vertex_name, v, weight);
    
    // checks if e exists in the list
    if(this->_edges.isExists(e)){
        // finds the index of e in the list
        int index = this->_edges.find(e);
        // removes it from the list
        this->_edges.pop(index);
    }
    
    // adds e to the list    
    this->_edges.insert(e);
}

void Vertex::addEdge(const Edge &e){
    // if the vertex in v1 of e is not this vertex throw an error
    if(e.getVertex1() != this->_vertex_name)
        throw std::invalid_argument{"edge relates to different vertex"};
    
    // adds edge
    this->addEdge(e.getVertex2(), e.getWeight());
}

Edge Vertex::removeEdge(const Vertex &v){
    // creates an edge from this vertex to v
    Edge e = Edge(this->_vertex_name, v.getVertexName());

    // finds out if e exists in the list (checking if there is an edge from this vertex to v)
    int index = this->_edges.find(e);

    // if it doesn't exist, throw an error
    if(index == -1)
        throw std::out_of_range{"The edge (" + e.to_string() + ") doesn't exist"};
    
    // if it does exist, remove it and return it
    return this->_edges.pop(index); 
}

void Vertex::print() const{
    // prints the name of the vertex
    std::cout << "Vertex #" << this->_vertex_name << ":" << std::endl;

    // if the vertex is has no edges, prints no edges
    if(this->_edges.isEmpty())
        std::cout << "No Edges" << std::endl;
    else{ // prints every edge in the vertex
        for(int i=0; i<this->_edges.size(); i++) {
            // gets the i-th edge
            const Edge &e = this->_edges.getValue(i);
            // prints it's information
            std::cout << i+1 << ". " << e.to_string() << std::endl;
        }
    }
}

bool Vertex::operator== (const Vertex &v) const{
    // checks if they have a different name
    if(this->getVertexName() != v.getVertexName())
        return false;
    
    // checks if they have a different amount of edges
    if(this->_edges.size() != v._edges.size())
        return false;

    // checks if v contains all the edges in this
    for(int i=0; i<this->_edges.size(); i++){
        const Edge &e = this->_edges.getValue(i); // gets an edge from the list of edges
        if(!v.isEdgeExists(e)) // checks if such an edge exists in v
            // if it doesn't, they are different vertices
            return false;
    }

    // if the vertices have the same name, size and edges, they are the same 
    return true;
}

bool Vertex::operator!= (const Vertex &v) const{
    // returns true if == returns false, else true
    return !(*this == v); 
}