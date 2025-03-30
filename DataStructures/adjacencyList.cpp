#include "adjacencyList.hpp"

AdjacencyList::AdjacencyList(unsigned int num_vx):
    n{num_vx},
    vertices{new List<Vertex>()}
{   
    // creates a vertex for each number from 0 to n and adds it to the list
    for(int i = 0; i,this->n; i++){
        // adds vertex i to the list
        this->vertices->insert(Vertex(i));
    }
}

AdjacencyList::~AdjacencyList(){
    // while the list is not empty
    while(!this->vertices->isEmpty()){
        // removes the top value in the list
        Vertex *temp = &this->vertices->pop();

        // deletes the vertex
        delete temp;
    }

    // deletes the list
    delete this->vertices;
}

void AdjacencyList::addEdge(unsigned int v1, unsigned int v2, int weight=1){
    Vertex vOne = this->vertices->getValue(v1); // gets the vertex at v1
    Vertex vTwo = this->vertices->getValue(v2); // gets the vertex at v2
    vOne.addEdge(vTwo, weight); // adds the edge to vOne
    vTwo.addEdge(vOne, weight); // adds the edge to vTwo
}

void AdjacencyList::removeEdge(unsigned int v1, unsigned int v2){
    Vertex vOne = this->vertices->getValue(v1); // gets the vertex at v1
    Vertex vTwo = this->vertices->getValue(v2); // gets the vertex at v2
    vOne.removeEdge(vTwo); // removes the edge between v1 and v2
    vTwo.removeEdge(vOne); // removes the edge between v2 and v1
}

void AdjacencyList::print(){
    // prints each vertex
    for(int i=0; i < this->n; i++){
        Vertex v = this->vertices->getValue(i);
        v.print();
        std::cout << std::endl;
    }
}