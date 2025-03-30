// implementation for graph
#include "graph.hpp"

List<Edge> Graph::getEdges(){
    List<Edge> edges = List<Edge>();

    // goes over each vertex in the graph
    for(int i = 0; i < this->n; i++){
        // gets a vertex from the graph
        Vertex v = this->al.getVertex(i);

        // get all possible edges from that vertex
        for(int j=0; j < this->n; j++){
            Vertex otherV(j);
            // if the edge exists
            if(v.isEdgeExists(otherV)){
                edges.insert(v.getEdge(otherV)); // adds the edge to the list
            }
        }
    }
    // returns the list of edges
    return edges;
}

void Graph::addEdge(Edge e){
    this->al.addEdge(e.getVertex1(), e.getVertex2(), e.getWeight());
}
