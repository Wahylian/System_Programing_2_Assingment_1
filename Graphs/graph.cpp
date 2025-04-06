// rido1607@gmail.com
#include "graph.hpp"
namespace graph{
    Graph::Graph(int n):
    _n{n},
    _al{AdjacencyList(n)}
    {
        // nothing to do here
    }
    
    Graph::Graph(const Graph &g):
    _n{g._n},
    _al{g._al}
    {
        // nothing to do here
    }
    
    void Graph::addEdge(int v, int u, int weight){
        // checks if v and u are the same vertex
        // if they are, throw an error, as this is a simple non-directional graph
        if(v == u)
            throw std::invalid_argument{"v and u cannot be the same vertex"};
    
        // since the graph is non-directional,
        // adds both (v, u) and (u, v)
        this->_al.addEdge(v, u, weight); 
        this->_al.addEdge(u, v, weight);
    }
    
    void Graph::addEdge(const Edge &e){
        // adds the edge to the graph
        this->addEdge(e.getVertex1(), e.getVertex2(), e.getWeight()); 
    }
    
    void Graph::removeEdge(int v, int u){
        // since the graph is non-directional,
        // remove both (v, u) and (u, v)
        this->_al.removeEdge(v, u);
        this->_al.removeEdge(u, v);
    }
    
    void Graph::print_graph() const{
        std::cout << "Graph:" << std::endl;
        // prints the adjacency list
        this->_al.print(); 
    }
    
    List<Edge> Graph::getEdges() const{
        // creates a list to save all the edges
        List<Edge> edges = List<Edge>();
    
        // goes over each vertex in the adjacency list
        for(int i=0; i<this->_n; i++){
            // gets a reference to to vertex i in the adjacency list
            const Vertex &v = this->_al.getVertex(i);
            // gets a reference to the list of all vertices in v
            const List<Edge> &v_edges = v.getEdges();
    
            // gets a copy of all edges in v
            for(int j=0; j<v.getNumEdges(); j++){
                // gets the j-th edge in v
                edges.insert(v_edges.getValue(j));
            }
        }
    
        // returns edges
        return edges;
    }
    
    int Graph::numEdges() const{
        // since the graph is not directional, each edge is stored twice, once for each direction
        // so the amount of edges of the graph is the number of edges divided by 2
        return (this->getEdges().size()/2);
    }
    
    bool Graph::isEdgeExists(int v, int u) const{
        return this->_al.isEdgeExists(v, u);
    }
    
    bool Graph::isEdgeExists(const Edge &e) const{
        return this->_al.isEdgeExists(e.getVertex1(), e.getVertex2());
    }

    bool Graph::operator== (const Graph &g) const{
        // checks if both graphs have the same amount of vertices
        if(this-> _n != g._n)
            return false;
        
        // checks if both graphs have the same amount of edges
        if(this->numEdges() != g.numEdges())
            return false;
        
        // checks if both graphs have the same edges
        List<Edge> this_edges = this->getEdges();
        List<Edge> g_edges = g.getEdges();

        // going over each edge in this graph
        for(int i=0; i<this_edges.size(); i++){
            // gets the i-th edge in this graph
            const Edge &e_this = this_edges.getValue(i);

            bool found = false;
            // checks if e_this exists in g_edges
            for(int j=0; j<g_edges.size(); j++){
                const Edge &e_g = g_edges.getValue(j);
                // checks that e is the same as e_g
                if(e_this == e_g && e_this.getWeight() == e_g.getWeight()){
                    found = true;
                    break;
                }
            }

            // if e was not found return false
            if(!found)
                return false;
        }
        // if all edges were found return true
        return true;
    }
}
