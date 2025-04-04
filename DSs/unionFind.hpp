#ifndef UNIONFIND
#define UNIONFIND
#ifndef DEBUG
// debug check
#include "../debug.hpp"
#endif
#include <stdexcept>
#include "node.hpp"
class UnionFind{
    private:
    int n; // the number of vertices
    Node<int> *vertices;

    public:
    #pragma region Ctors & Dtors
    // constructor
    UnionFind(int num_vx);

    // destructor
    ~UnionFind();
    #pragma endregion

    // finds the head of the set vertex is in
    int Find(int vertex);

    // creates a union between the sets of v and u 
    void Union(int v, int u);
};
#endif