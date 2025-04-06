// rido1607@gmail.com
#pragma once
#include <stdexcept>
#include "node.hpp"
class UnionFind{
    private:
    int _n; // the number of vertices
    Node<int> *_vertices;

    public:
    #pragma region Ctors & Dtors
    // constructor
    UnionFind(int num_vx);

    // copy constructor
    UnionFind(const UnionFind &uf);

    // destructor
    ~UnionFind();
    #pragma endregion

    // finds the head of the set vertex is in
    int Find(int vertex) const;

    // creates a union between the sets of v and u 
    void Union(int v, int u);

    // returns the number of vertices in the unionfind
    int size() const{return this->_n;}
};