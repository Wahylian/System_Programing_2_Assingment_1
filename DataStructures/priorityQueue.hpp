#ifndef PRIOQUEUE
#define PRIOQUEUE
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/

#include "node.hpp"
#include "tuple.hpp"
#include <stdexcept>

template <typename T>

class PriorityQueue{
    // the higher the priority of a value in the queue, the faster it will get out

    private:
    int size;
    Node<Tuple<int,T>> *head; // the head of the priority queue
    Node<Tuple<int,T>> *last; // the last node in the priority queue

    public:
    // constructor
    PriorityQueue();

    // destructor
    ~PriorityQueue();

    // returns true if queue is empty, else false
    bool isEmpty();

    // returns the size of the queue
    int getSize(){return this->size;}

    // returns the top value in the queue without removing it
    T top();

    // adds a value to the queue based on its priority, by default priority will be 0
    void enqueue(T value, unsigned int priority=0);

    // removes the top value from the queue 
    T dequeue();

    // changes the priority of value 
    void changePriority(T value, unsigned int priority=0);
};
#endif