#ifndef QUEUE
#define QUEUE
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/
// used https://www.geeksforgeeks.org/basic-operations-for-queue-in-data-structure/ for the basic functions of queue (just looked at what they were, not how they are written)
#include "node.hpp"
#include <stdexcept>

template <typename T>

// this is a basic queue class
class Queue{
    private:
    int size; // the size of the queue
    Node<T> *head; // the head of the queue
    Node<T> *last; // the end of the queue

    public:
    // constructor
    Queue(){
        this->size = 0;
        this->head = nullptr;
        this->last = nullptr;
    }
    // destructor
    ~Queue(){
        // delete the head if it is not already disconnected
        if(this->head != nullptr)
            delete this->head;
    }

    // returns true if queue is empty, else false
    bool isEmpty(){
        if(this->size == 0)
            return true;
        return false;
    }

    // returns the size of the queue
    int size(){
        return this->size;
    }

    // returns the top value in the queue without removing it
    T top(){
        if(this->isEmpty())
            throw std::underflow_error{"queue is empty"};
        
        return (this->head)->getValue();
    }

    void enqueue(T value){
        // creates a new node
        Node<T> *temp = new Node<T>(value);
        // sets temp in the start of the queue if it is empty
        if(this->head == nullptr)
            this->head = temp;
        // if the queue is not empty sets the next node after last to be temp
        else{
            (this->last)->setNext(temp); 
        }

        // sets the end of the queue to temp
        this->last = temp;
        
        // increases size of the queue by 1
        this->size++;
    }
    
    T dequeue(){
        // if the queue is empty throws an error
        if(this->isEmpty())
            throw std::exception{"queue is empty"};
        
        // removes the head of the queue

        Node<T> *temp = (this->head); // gets the head of the queue
        this->head = temp->getNext(); // makes the next node the head of the queue
        T value = temp->getValue(); // gets the value stored in temp
        delete temp; // deletes temp
        
        // decreases the size of the queue by 1
        this->size--;

        return value;
    }
};
#endif