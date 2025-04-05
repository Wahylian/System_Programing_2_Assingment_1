#include "unionFind.hpp"

UnionFind::UnionFind(int num_vx):   
_n{num_vx},
_vertices{nullptr} 
{   
    #ifdef DEBUG
    std::cout << "UnionFind constructor" << std::endl;
    #endif
    // if n is non positive, throw an error, as there must be at least one vertex in the unionFind
    if(this->_n <= 0)
        throw std::invalid_argument{"there must be at least one vertex in the UnionFind"};

    // creates an array of n nodes
    this->_vertices = new Node<int>[this->_n];
    // initializes the value in each node
    for(int i=0; i<this->_n; i++){
        this->_vertices[i].setValue(i); // sets the value of the node to the corrisponding vertex number
    }
}

UnionFind::UnionFind(const UnionFind &uf):
_n{uf._n},
_vertices{nullptr}
{
    // creates an array of n nodes
    this->_vertices = new Node<int>[this->_n];
    // goes over each node in uf, checks which node it points to, and copies the correct index
    for(int i=0; i<this->_n; i++){
        // sets the value of the node
        this->_vertices[i].setValue(i);

        // gets a pointer to the node uf._vertices[i] points to
        Node<int> *temp = uf._vertices[i].getNext();
        // checks if its not null
        if(temp != nullptr){
            // saves the index in that node's value
            int index = temp->getValue();
            // point's this->_vertices[i]'s next to this->_vertices[index]
            this->_vertices[i].setNext(&(this->_vertices[index]));
        }
    }
}

UnionFind::~UnionFind(){
    delete[] this->_vertices; // deletes the array
}

int UnionFind::Find(int vertex){
    // if the vertex is not in the unionFind class at all, throw an exception
    if(vertex<0 || vertex >= this->_n)
        throw std::out_of_range{"the vertex doesn't exist"};
    
    // goes to the index of the node corrisponding to vertex
    Node<int> *temp = &(this->_vertices[vertex]);
    // while temp has a next, advance temp
    while(temp->getNext()!=nullptr)
        temp = temp->getNext();
    
    // returns the value of temp, as it is the head of the set vertex is in
    return temp->getValue();
}

void UnionFind::Union(int v, int u){
    // finds the head of the set of v and the head of the set of u
    // if either v or u are illegal vertices, find will throw an error
    int head_v = this->Find(v);
    int head_u = this->Find(u);
    
    // check if v and u are both in the same set
    if(head_v == head_u)
        return; // as there is no need to union the two 

    // else, points the head of the set of u to the head of the set of v
    this->_vertices[head_u].setNext(&(this->_vertices[head_v]));
}