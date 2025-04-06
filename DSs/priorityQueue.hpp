// rido1607@gmail.com
#pragma once
#include <stdexcept>
#include "node.hpp"
#include "tuple.hpp"

template <typename T>
class PriorityQueue{
    // the higher the priority the closer to the head of the queue
    private:
    Node<Tuple<int, T>> *_head;// the head of the priority queue
    Node<Tuple<int, T>> *_last;// the last node in the priority queue
    int _size;

    public:
    #pragma region Ctors & Dtors
    // constructor
    PriorityQueue():
    _head{nullptr},
    _last{nullptr},
    _size{0}
    {
        // nothing to do
    }

    // copy constructor
    PriorityQueue(const PriorityQueue<T> &pQ):
    _head{nullptr},
    _last{nullptr},
    _size{0}
    {
        // if pQ is empty, returns
        if(pQ._size == 0)
            return;

        Node<Tuple<int, T>> *temp_other = pQ._head; // gets a pointer to the head of the other list
        
        // copies the first value in list
    
        // creates a new node with the value at head
        this->_head = new Node<Tuple<int, T>>(Tuple(temp_other->getValue()));
    
        // advances temp_other
        temp_other = temp_other->getNext();
    
        // points temp pointer at the head
        Node<Tuple<int, T>> *temp = this->_head;
        // points last at temp
        this->_last = temp;
    
        // copies over every other value in queue
        for(int i=1; i<pQ._size; i++){
            // creates a new node with the value at temp_other
            Node<Tuple<int, T>> *tNode = new Node<Tuple<int, T>>(Tuple(temp_other->getValue()));
    
            // advances temp_other
            temp_other = temp_other->getNext();
    
            // points temp's next at it
            temp->setNext(tNode);
    
            // points last at temp's next
            this->_last = temp->getNext();
    
            // advance temp
            temp = temp->getNext();
        }
    
        // sets the size of the queue
        this->_size = pQ._size;
    }

    // destructor
    ~PriorityQueue(){
        #ifdef DEBUG
        std::cout << "Priority Queue destructor" << std::endl;
        #endif
        // deletes all nodes in the queue
        Node<Tuple<int, T>> *temp = this->_head;
        while(temp != nullptr){
            // gets the next node after temp
            Node<Tuple<int, T>> *next = temp->getNext();
            
            // separetes temp from the list
            temp->setNext(nullptr);
            delete temp;

            // moves to the next node
            temp = next;
        }

        // points start and end to null
        this->_head = nullptr;
        this->_last = nullptr;
    }
    #pragma endregion




    #pragma region Basic Util
    // returns true if queue is empty, else false
    bool isEmpty() const{
        if(this->_size == 0)
            return true;
        return false;
    }

    // returns the size of the queue
    int size() const {return this->_size;}

    // returns the a reference to the top value in the queue without removing it
    T& top() {
        // if the queue is empty throws an error
        if(this->isEmpty())
            throw std::underflow_error{"queue is empty"};

        // gets the value from the tuple and returns it
        Tuple<int, T> &t = (this->_head)->getValue();
        return t.getSecond();
    }

    // returns true if the queue contains this value
    bool contains(const T &value) const{
        // if the queue is empty throws an error
        if(this->isEmpty())
            throw std::underflow_error{"queue is empty"};

        // saves a pointer to the start of the queue
        Node<Tuple<int, T>> *temp = this->_head;

        // advances temp until it finds the value or reaches the end of the queue
        while(temp != nullptr){
            // gets the value stored in temp
            Tuple<int, T> &t = temp->getValue();

            // if the value is in t, return true
            if(t.getSecond() == value){
                return true;
            }
            
            // advances temp
            temp = temp->getNext();
        }   
        // returns false if the value was not found
        return false;
    }
    #pragma endregion



    #pragma region Queueing
    // queues the value based on it's priority, by default priority will be 0
    void enqueue(T value, int priority=0){
        // creates a new Tuple from the copy of value and its priority
        Tuple<int, T> t = Tuple<int, T>(priority, T(value));

        // creates a new node
        Node<Tuple<int, T>> *node = new Node<Tuple<int, T>>(t);

        // if the queue is empty, points head and last at the new node
        if(this->isEmpty()){
            this->_head = node;
            this->_last = node;
            // increase the size by one
            this->_size++;

            return;
        }

        // if the priority is higher than the head, make it the new head of the queue
        if(t.getFirst() > this->_head->getValue().getFirst()){
            node->setNext(this->_head);
            this->_head = node;

            // increase the size by one
            this->_size++;
            return;
        }

        // else, go over the queue until the next node has a lower priority than value
        Node<Tuple<int, T>> *temp = this->_head;
        // gets the next value in the queue
        Node<Tuple<int, T>> *next = this->_head->getNext();

        // while the next node is not null
        while(next != nullptr){
            // gets the value in next
            Tuple<int, T> nextVal = next->getValue();

            // if the value of next has a lower priority than value
            // value needs to be inserted before next
            if(t.getFirst() > nextVal.getFirst()){
                // sets the next node of temp to be node
                temp->setNext(node);
                // sets the next node of node to be next
                node->setNext(next);

                // increase the size by one
                this->_size++;
                return;
            }

            // advance temp and next
            temp = next;
            next = next->getNext();
        }

        // if the node was not inserted by the end of the loop, it is queued at the end of the queue
        this->_last->setNext(node);
        this->_last = node;
        
        // increases the size by one
        this->_size++;
        return;
    }
    
    // removes the top value from the queue
    T dequeue(){
        // if the queue is empty throws an error
        if(this->isEmpty())
            throw std::underflow_error{"queue is empty"};
        
        // removes the head of the queue
        Node<Tuple<int, T>> *temp = (this->_head); // gets the head of the queue

        // if the size of the queue is 1, the head and last nodes in the queue are the same node,
        // and so points last to null
        if(this->_size == 1)
            this->_last = nullptr;

        // advances the head to the next node
        this->_head = this->_head->getNext();

        // separates temp from the queue
        temp->setNext(nullptr);

        // decreases the size of the queue by 1
        this->_size--;

        // saves the value in temp
        T value = temp->getValue().getSecond();

        // deletes temp from the memory
        delete temp;

        // returns value
        return value;
    }

  
    // changes the priority of value
    void changePriority(T value, int priority=0){
        // if the queue is empty throws an error
        if(this->isEmpty())
            throw std::underflow_error{"queue is empty"};

        // if the value is stored in the head, separate the head and requeue the value with the new priority
        if(this->_head->getValue().getSecond() == value){
            // saves a pointer to the head
            Node<Tuple<int, T>> *temp = this->_head;
            // if the queue has only one node, points last to null
            if(this->_head == this->_last)
                this->_last = nullptr;
            
            // advances the head to the next node
            this->_head = this->_head->getNext();

            // separates temp from the queue
            temp->setNext(nullptr);
            // decreases the size of the queue by 1
            this->_size--;

            // deletes temp from the memory
            delete temp;

            // requeues the value with the new priority
            this->enqueue(value, priority);
            return;
        }

        // if the value was not in the head of the queue
        // go over the next value in the queue until it is found
        Node<Tuple<int, T>> *temp = this->_head;
        // saves a pointer to the next node
        Node<Tuple<int, T>> *next = temp->getNext();
        // advances temp and next until next has an instance of value, or next is null
        while(next != nullptr){
            // gets the value stored in next
            Tuple<int, T> nextT = next->getValue();

            // if next holds the value, separates next from the queue
            if(nextT.getSecond() == value){
                // if next is the last node in the queue, points last to temp
                if(next == this->_last)
                    this->_last = temp;
                
                // separates next from the queue
                temp->setNext(next->getNext());
                next->setNext(nullptr);

                // decreases the size of the queue by 1
                this->_size--;

                // deletes next from the memory
                delete next;

                // requeues the value with the new priority
                this->enqueue(value, priority);
                return;
            }

            // advances temp and next
            temp = next;
            next = next->getNext();
        }

        // if the value was not found in the loop, value was not in the queue
        // and so throws an error
        throw std::invalid_argument{"value not found in queue"};
    }
    #pragma endregion
};