#include "adjacencyList.hpp"

AdjacencyList::AdjacencyList(int num_vx):
n{num_vx},
vertices{List<Vertex>()}{
    // the list must have a non negative amount of vertices to create it
    if(this->n < 0)
        throw std::invalid_argument{"there must be a non negative amount of vertices in the list"};

    // creates a number of vertices based on the number provided and inserts them to the list
    for(int i=0; i<this->n; i++)
        this->vertices.insert(Vertex(i));
}

void AdjacencyList::addEdge(int v, int u, int weight){
    // checks both vertices are in range, if they aren't throws an error
    if(v < 0 || v >= this->n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};
    if(u < 0 || u >= this->n)
        throw std::out_of_range{"vertex "+ std::to_string(u)+ " doesn't exist"};

    // creates the edge that needs to be inserted
    Edge e = Edge(v, u, weight);
    
    // gets vertex v from the list
    Vertex vx = this->vertices.pop(this->vertices.find(Vertex(v)));

    // adds e to vx
    vx.addEdge(e);

    // reinserts vc into the list
    this->vertices.insert(vx);
}

void AdjacencyList::removeEdge(int v, int u){
    // checks both vertices are in range, if they aren't throws an error
    if(v < 0 || v >= this->n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};
    if(u < 0 || u >= this->n)
        throw std::out_of_range{"vertex "+ std::to_string(u)+ " doesn't exist"};

    // gets vertex v from the list of vertices
    Vertex vx = this->vertices.pop(this->vertices.find(Vertex(v)));

    // attempts to remove (v, u) from vx
    vx.removeEdge(u);
}

const Vertex& AdjacencyList::getVertex(int v) const{
    // checks the vertex is in range, if not, throw an error
    if(v < 0 || v >= this->n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};

    // gets the vertex from the list of vertices
    return this->vertices.getValue(this->vertices.find(Vertex(v)));
}

void AdjacencyList::print() const{
    // goes over each vertex in the list in order of indices
    for(int i=0; i<this->n; i++){
        // finds the index of the i-th vertex
        int index = this->vertices.find(Vertex(i));
        // gets the vertex
        const Vertex &v = this->vertices.getValue(index);
        // prints the vertex
        v.print();
    }
}