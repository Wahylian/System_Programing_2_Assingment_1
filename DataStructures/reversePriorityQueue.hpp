#ifndef REVERSEPRIOQUEUE
#define REVERSEPRIOQUEUE
#define MAXVAL __INT32_MAX__ 
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/

#include "priorityQueue.hpp"
#include <stdexcept>

template <typename T>

class RevPriorityQueue{
    // the lower the priority of a value in the queue, the faster it will get out

    private:
    PriorityQueue<T> q;

    public:
    // constructor
    RevPriorityQueue():
        q{PriorityQueue<T>()}
    {}

    // destructor
    ~RevPriorityQueue(){}

    // returns true if queue is empty, else false
    bool isEmpty(){return this->q.isEmpty();}

    // returns the size of the queue
    int getSize(){return this->q.getSize();}

    // returns the top value in the queue without removing it
    T top(){return this->q.top();}

    // adds a value to the queue based on its priority, by default priority will be INT32_MAX
    void enqueue(T value, unsigned int priority=MAXVAL){this->q.insert(value, MAXVAL-priority);}

    // removes the top value from the queue 
    T dequeue(){return this->q.dequeue();}

    // changes the priority of value 
    void changePriority(T value, unsigned int priority=MAXVAL){this->q.changePriority(value, MAXVAL);}
};
#endif