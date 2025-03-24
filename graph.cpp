// implementation for graph

#include "graph.hpp"
#include <iostream> // cout and cin were not found - found this solution on https://stackoverflow.com/questions/11375949/cout-is-not-a-member-of-std

// constructor
Graph::Graph(unsigned int num_vx){
    this->n = num_vx;
        this->matrix = new int*[this->n]; // creaing an array of pointers of size n
        // each of these pointers now needs to point to an array of ints of size n
        for(int i = 0; i < this->n; i++){
            (this->matrix)[i] = new int[this->n]; // creating the int array
            // initiating the values
            for(int j =0; j < this->n; j++){
                (this->matrix)[i][j] = __INT32_MAX__; // INT_MAX represents an edge of infinite weight, meaning there is no edge
            }
        }
}

// destructor
Graph::~Graph(){
    // destroys the pointer arrays
        for(int i = 0; i < this->n; i++){
            delete[] (this->matrix)[i]; // deletes the array
        }
        delete[] (this->matrix); // deletes the array of pointers
}

