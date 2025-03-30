#ifndef UNIONFIND
#define UNIONFIND
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/
#include "node.hpp"
#include <stdexcept>

// this class is a basic implementation of a unionFind
class UnionFind{
    private:
    // a pointer to an array of all the nodes
    Node<int> *vertices;
    int n; // the number of vxs

    public:
    // constructor
    UnionFind(unsigned int num_vx){
        this->n = num_vx;
        this->vertices = new Node<int>[n];
        
        // initiallizes the array
        for(int i = 0; i < n; i++){
            this->vertices[i].setValue(i); // sets the value of the node correctly to the vertix number
            this->vertices[i].setNext(nullptr); // makes sure that all nodes point to null
        }
    }
    // destructor
    ~UnionFind(){
        delete[] this->vertices; // deletes the array
    }

    // finds the head of the set vx is in
    int Find(unsigned int vx){
        if(vx >= this->n) 
            throw std::out_of_range{"vertex not found"};
        int k = vx;

        // continues moving from vertex to vertex while there is a next vertex
        while(this->vertices[k].getNext()!=nullptr)
            // saves the value (the number) of the next vertex in the set (the parent of k)
            k = this->vertices[k].getNext()->getValue();
        
        // once exiting the loop, k now holds the ancestor of all vxs in the set
        return k;
    }

    // creates a union between the set of u and the set of v
    void Union(unsigned int u, unsigned int v){
        // finds the parents of both u and v
        int k = this->Find(u); // if u is out of range will throw an error as intended
        int l = this->Find(v); // if v is out of range will throw an error as intended

        // if k == l, u and v are part of the same set
        if(k == l) return;

        // else, the sets can be unioned
        this->vertices[k].setNext(&(this->vertices[l])); // points the parent of u at the parent of v
    }
};
#endif