// rido1607@gmail.com
#pragma once
#include <stdexcept>
#include <string>
class Edge{
    private:
    int _v;
    int _u;
    int _weight;

    public:
    // constructor
    Edge(int vertex1, int vertex2, int weight=1); 
    // NOTE: since the edge is built for a directional graph, an edge from a vertex to itself is allowed

    // copy constructor
    Edge(const Edge &e);

    // returns vertex 1
    int getVertex1() const{return this->_v;}

    // returns vertex 2
    int getVertex2() const {return this->_u;}

    // returns the wieght of the edge
    int getWeight() const {return this->_weight;}

    // sets the weight of the edge
    void setWeight(int weight){this->_weight = weight;}

    // returns true if this and e are the same, else false
    bool operator==(const Edge &e) const;

    // returns false if this and e are the same, else true
    bool operator!=(const Edge &e) const;

    // returns a string representation of the edge
    std::string to_string() const;
};