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
    PriorityQueue(){
        this->size = 0;
        this->head = nullptr;
        this->last = nullptr;
    }
    // destructor
    ~PriorityQueue(){
        // deletes the head of the priority queue if it is not already disconnected
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
        // gets the value from the tuple and returns it
        Tuple<int, T> t = (this->head)->getValue();
        return t.valTwo;
    }

    // adds a value to the queue based on its priority, by default priority will be 0
    void enqueue(T value, unsigned int priority=0){
        // creates a new tuple
        Tuple<int, T> t;
        t.valOne = priority;
        t.valTwo = value;

        // creates a new node
        Node<Tuple<int, T>> *temp = new Node<Tuple<int, T>>(t);
        
        // sets temp in the start of the queue if it is empty
        if(this->head == nullptr){
            this->head = temp;
            this->last = temp;
            
            // increase the size of the queue by 1
            this->size++;
            return;
        }

        // if t has a higher priority than head, make it the new head of the queue
        Tuple<int, T> headVal = this->head->getValue();
        if(headVal.valOne < t.valOne){
            temp->setNext(this->head);
            this->head = temp;
                
            // increase the size of the queue by one
            this->size++;    

            return;
        }

        // if the queue is not empty, and the priority of t is not higher than the head,
        // run along the queue until the next tuple that has a priority lower than value
        Node<Tuple<int, T>> *tNode = this->head;
        while(tNode->getNext() != nullptr){
            Node<Tuple<int, T>> *tNext = tNode->getNext();
            Tuple<int, T> nextVal = tNext->getValue();
            if(nextVal.valOne < t.valOne){
                temp->setNext(tNext);
                tNode->setNext(temp);

                // increase the size of the queue by one
                this->size++;

                return;
            }
            // advances tNode by one;
            tNode = tNext;
        }

        // if no value has a lower priority than value, place it at the end
        this->last->setNext(temp);
        this->last = temp;

        // increase the size of the queue by one
        this->size++;

        return;
    }

    T dequeue(){
        // if the queue is empty throws an error
        if(this->isEmpty())
            throw std::exception{"queue is empty"};
        
        // removes the head of the queue

        Node<T> *temp = (this->head); // gets the head of the queue

        // if the queue is of size 1
        if(this->size == 1){
            // point head and last to nullptr
            this->head = nullptr;
        }


        this->head = temp->getNext(); // makes the next node the head of the queue
        T value = temp->getValue(); // gets the value stored in temp
        delete temp; // deletes temp
        
        // decreases the size of the queue by 1
        this->size--;

        return value;
    }

    // changes the priority of value 
    void changePriority(T value, unsigned int priority=0){
        Node<Tuple<int, T>> *temp = this->head;
        
        // if the value is in the head of the queue, remove the head and change the priority
        Tuple<int, T> tVal = temp->getValue();
        if(tVal.valTwo == value){
            // dequeue the head of the queue
            this->dequeue();
            // enqueue the value with the new priority
            this->enqueue(value, priority);
            return;
        }

        // if the value was not in the head of the queue
        // go over the next value in the queue until it is found
        while(temp->getNext() != nullptr){
            Node<Tuple<int, T>> *next = temp->getNext();
            // get the value of next
            Tuple<int, T> nextVal = next->getValue();
            
            // if next holds the value
            if(nextVal.valTwo == value){
                // remove next from the queue
                temp->setNext(next->getNext());
                next->setNext(nullptr);
                // decrease the size of the queue by 1
                this->size--;

                // enqueue the value with the new priority
                this->enqueue(value, priority);
                return;
            }
        }

        // if the value was not found in the loop, value was not in the queue
        // and so throws an error
        throw std::invalid_argument{"the value was not in the queue"};
    }
};
