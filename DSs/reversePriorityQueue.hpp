// rido1607@gmail.com
#pragma once
#include "priorityQueue.hpp"


template <typename T>
class RevPriorityQueue{
    // the lower the priority the closer to the head of the queue
    private:
    PriorityQueue<T> _pQ;

    public:
    #pragma region Ctors & Dtors
    // constructor
    RevPriorityQueue():
    _pQ{PriorityQueue<T>()}
    {
        // nothing to do
    }
    // copy constructor
    RevPriorityQueue(const RevPriorityQueue<T> &rPQ):
    _pQ{rPQ._pQ}
    {
        // nothing to do here
    }
    #pragma endregion





    #pragma region Basic Utils
    // returns true if the queue is empty, else false
    bool isEmpty() const{return this->_pQ.isEmpty();}

    // returns the size of the queue
    int size() const{return this->_pQ.size();}

    // returns a reference to the top value in the queue
    T& top(){return this->_pQ.top();}
    
    // returns true if this queue contains value, else false
    bool contains(const T &value) const{return this->_pQ.contains(value);}
    #pragma endregion





    #pragma region Queueing
    // queues the value based on it's priority, by default priority will be 0
    void enqueue(T value, int priority=0){
        // queues the value
        this->_pQ.enqueue(value,-priority);
    }

    // removes the top value from the queue
    T dequeue(){return this->_pQ.dequeue();}

    // changes the priority of value
    void changePriority(T value, int priority=0){
        // changes the priority of the value
        this->_pQ.changePriority(value, -priority);
    }
    #pragma endregion
};