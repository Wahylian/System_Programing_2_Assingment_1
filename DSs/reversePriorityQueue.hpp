#include "priorityQueue.hpp"
#ifndef DEBUG
// debug check
#include "../debug.hpp"
#endif
#ifndef MAX_VAL 
// defines a max value
#define MAX_VAL __INT32_MAX__
#endif


template <typename T>
class RevPriorityQueue{
    // the lower the priority the closer to the head of the queue
    private:
    PriorityQueue<T> pQ;

    public:
    #pragma region Ctors & Dtors
    // constructor
    RevPriorityQueue():
    pQ{PriorityQueue<T>()}
    {
        #ifdef DEBUG
        std::cout << "RevPriorityQueue constructor" << std::endl;
        #endif
    }
    #pragma endregion





    #pragma region Basic Utils
    // returns true if the queue is empty, else false
    bool isEmpty() const{return this->pQ.isEmpty();}

    // returns the size of the queue
    int size() const{return this->pQ.size();}

    // returns a reference to the top value in the queue
    T& top(){return this->pQ.top();}
    
    // returns true if this queue contains value, else false
    bool contains(const T &value) const{return this->pQ.contains(value);}
    #pragma endregion





    #pragma region Queueing
    // queues the value based on it's priority, by default priority will be INT32_MAX
    void enqueue(T value, int priority=MAX_VAL){
        // if priority is negative throws error
        if(priority<0)
            throw std::invalid_argument{"priority must be non-negative"};
        
        // queues the value
        this->pQ.enqueue(value, MAX_VAL-priority);
    }

    // removes the top value from the queue
    T dequeue(){return this->pQ.dequeue();}

    // changes the priority of value
    void changePriority(T value, int priority=MAX_VAL){
        // if priotiry is negative throws error
        if(priority<0)
            throw std::invalid_argument{"priority must be non-negative"};
        
        // changes the priority of the value
        this->pQ.changePriority(value, MAX_VAL-priority);
    }
    #pragma endregion
};