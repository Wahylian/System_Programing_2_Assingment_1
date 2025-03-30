#include "vertex.hpp"

bool Vertex::isEdgeExists(Vertex v){
    // creates an edge between this and v
    Edge edge(this->vertex_name, v.getVertexName());

    // going over all edges in this vertex
    for(int i = 0; i < this->num_edges; i++){
        // gets an edge from the list of this's edges
        Edge e = this->edges->getValue(i);

        // if they are the same edge, return true
        if(edge.isSameEdge(e))
            return true;
    }
    // if after going over all the edges in this, non matched, return false
    return false;
}

Edge Vertex::getEdge(Vertex v){
    // creates an edge between this and v
    Edge edge(this->vertex_name, v.getVertexName());

    // going over all edges in this vertex
    for(int i=0; i < this->num_edges; i++){
        // gets an edge from the list of this's edges
        Edge e = this->edges->getValue(i);

        // if they are the same edge, return it
        if(edge.isSameEdge(e))
            return e;
    }
    // if after going over all the edges in this, non mathced, throw error
    throw std::invalid_argument{"edge does not exist"};
}

List<Edge> Vertex::getEdges(){
    List<Edge> edges = List<Edge>();
    for(int i = 0; i < this->num_edges; i++){
        // adds the edge at index i
        edges.insert(this->edges->getValue(i));
    }
    return edges;
}

void Vertex::addEdge(Vertex v, int weight=1){
    // creates an edge between this and v
    Edge edge(this->vertex_name, v.getVertexName(), weight);

    // going over all edges in this vertex
    for(int i=0; i < this->num_edges; i++){
        // gets an edge from the list of this's edges
        Edge e = this->edges->getValue(i);

        // if they are the same edge, remove it from the list
        if(edge.isSameEdge(e)){
           this->edges->remove(e);
           this->num_edges--;
           break;
        }
    }
    
    // adds edge to the list
    this->edges->insert(edge);
    this->num_edges++;
}

Edge Vertex::removeEdge(Vertex v){
    // creates an edge between this and v
    Edge edge(this->vertex_name, v.getVertexName());

    // going over all edges in this vertex
    for(int i=0; i < this->num_edges; i++){
        // gets an edge from the list of this's edges
        Edge e = this->edges->getValue(i);

        // if they are the same edge, remove it from the list
        if(edge.isSameEdge(e)){
           this->edges->remove(e);
           this->num_edges--;
           return;
        }
    }
    // if after going over all the edges in this, non matched, throw error
    throw std::invalid_argument{"edge does not exist"};
}

void Vertex::print(){
    std::cout << "vertex #"<< this->vertex_name+1 << ":\t";
    for(int i = 0; i < this->num_edges; i++){
        Vertex v(i); // creates the other vertex of the edge
        // if the edge exists, prints it
        if(this->isEdgeExists(v)){
            Edge e = this->getEdge(Vertex(i));
            std::cout << "(" << e.getVertex2() << ", " << e.getWeight() << ") ";
        }
    }
}