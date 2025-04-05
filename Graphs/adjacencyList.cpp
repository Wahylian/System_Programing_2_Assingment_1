#include "adjacencyList.hpp"

AdjacencyList::AdjacencyList(int num_vx):
_n{num_vx},
_m{0},
_vertices{List<Vertex>()}{
    // the list must have a non negative amount of vertices to create it
    if(this->_n < 0)
        throw std::invalid_argument{"there must be a non negative amount of vertices in the list"};

    // creates a number of vertices based on the number provided and inserts them to the list
    for(int i=0; i<this->_n; i++)
        this->_vertices.insert(Vertex(i));
}

AdjacencyList::AdjacencyList(const AdjacencyList &al):
_n{al._n},
_m{al._m},
_vertices{al._vertices}
{
    // nothing to do here
}

void AdjacencyList::addEdge(int v, int u, int weight){
    // checks both vertices are in range, if they aren't throws an error
    if(v < 0 || v >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};
    if(u < 0 || u >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(u)+ " doesn't exist"};

    // creates the edge that needs to be inserted
    Edge e = Edge(v, u, weight);

    // gets vertex v from the list of vertices
    Vertex &vx = this->_vertices.getValue(v);

    // gets the number of edges in vx
    int num_edges = vx.getNumEdges();

    // adds e to vx
    vx.addEdge(e);

    // if the number of edges changed, increases the number of edges by 1
    if(vx.getNumEdges() != num_edges)
        this->_m++;
}

void AdjacencyList::removeEdge(int v, int u){
    // checks both vertices are in range, if they aren't throws an error
    if(v < 0 || v >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};
    if(u < 0 || u >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(u)+ " doesn't exist"};

    // gets vertex v from the list of vertices
    Vertex vx = this->_vertices.getValue(v);

    // attempts to remove (v, u) from vx
    vx.removeEdge(u);

    // if the removal was successful, decreases the number of edges by 1
    this->_m--;

    // inserts vx to the list in index v
    this->_vertices.insert(vx, v);
}

bool AdjacencyList::isEdgeExists(int v, int u) const{
    // checks both vertices are in range, if they aren't throws an error
    if(v < 0 || v >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};
    if(u < 0 || u >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(u)+ " doesn't exist"};

    // gets vertex v from the list of vertices
    const Vertex &vx = this->_vertices.getValue(v);

    // checks if edge exists
    return vx.isEdgeExists(u);
}

const Vertex& AdjacencyList::getVertex(int v) const{
    // checks the vertex is in range, if not, throw an error
    if(v < 0 || v >= this->_n)
        throw std::out_of_range{"vertex "+ std::to_string(v)+ " doesn't exist"};

    // gets the vertex at index v
    return this->_vertices.getValue(v);
}

void AdjacencyList::print() const{
    // goes over each vertex in the list in order of indices
    for(int i=0; i<this->_n; i++){
        // gets the i-th vertex
        const Vertex &v = this->_vertices.getValue(i);
        // prints the vertex
        v.print();
    }
}