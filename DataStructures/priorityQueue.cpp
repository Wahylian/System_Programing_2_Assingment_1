#include "priorityQueue.hpp"

template <typename T>
PriorityQueue<T>::PriorityQueue():
    size{0}, 
    head{nullptr},
    last{nullptr}
{}

template <typename T>
PriorityQueue<T>::~PriorityQueue(){
    // deletes all the nodes and tuples still inside the queue
    while(this->head != nullptr){
        Node<Tuple<int, T>> *temp = this->head;
        Tuple<int, T>& tVal = temp->getValue()

        // advance head by one
        this->head = this->head->getNext();
        // decrease size by 1
        this->size--;

        // seperate temp from the queue
        temp->setNext(nullptr);

        // delete temp
        delete temp;

        // delete tVal
        delete tVal;
    }
}

template <typename T>
bool PriorityQueue<T>::isEmpty(){
    if(this->size == 0)
        return true;
    return false;
}

template <typename T>
T PriorityQueue<T>::top(){
    if(this->isEmpty())
        throw std::underflow_error{"queue is empty"};
    // gets the value from the tuple and returns it
    Tuple<int, T> t = (this->head)->getValue();
    return t.getValTwo();
}

template <typename T>
void PriorityQueue<T>::enqueue(T value, unsigned int priority=0){
    // creates a new Tuple
    Tuple<int, T> t = new Tuple<int, T>(priority, value);
    
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

    // if it has a higher priority than head, make it the new head of the queue
    Tuple<int, T> headVal = this->head->getValue();
    // checks if t has a higher priority
    if(headVal.getValOne() < t.getValOne()){
        temp->setNext(this->head);
        this->head = temp;

        // increase the size of the queue by 1
        this->size++;
        return;
    }

    // if the queue is not empty, and the priority of t is not higher than the head,
    // run along the queue until the next tuple that has a priority lower than value
    Node<Tuple<int, T>> *tNode = this->head;
    while(tNode->getNext() != nullprt){
        Node<Tuple<int, T>> *tNext = tNode->getNext();
        Tuple<int, T> nextVal = tNext->getValue();

        // if t has a higher priority then it will be inserted before next
        if(nextVal.getValOne() < t.getValOne){
            temp->setNext(tNext);
            tNode->setNext(temp);

            // increase the size of the queue by 1
            this->size++;
            return
        }

        // if not, advance the node by one and look at the next node
        tNode = tNext;
    }

    // if no value has a lower priority than value, place it at the end
    this->last->setNext(temp);
    this->last = temp;

    // increase the size of the queue by one
    this->size++;
    return;
}

template <typename T>
T PriorityQueue<T>::dequeue(){
    // if the queue is empty throws an error
    if(this->isEmpty())
        throw std::exception{"queue is empty"};
        
    // removes the head of the queue
    Node<Tuple<int, T>> *temp = (this->head); // gets the head of the queue

    // if the queue is of size 1, sets the last node to point to nullptr
    if(this->size == 1)
        this->last = nullptr;

    this->head = temp->getNext(); // makes the next node the head of the queue
    Tuple<int, T> tVal = temp->getValue(); // gets the tuple stored in the node

    // seperates temp from the queue
    temp->setNext(nullprt);

    // delete the node from the heap
    delete temp;
        
    // saves the value in tVal
    T value = tVal.getValTwo();

    // deletes the tuple from the heap
    delete tVal;
        
    // decreases the size of the queue by 1
    this->size--;

    return value;
}

template <typename T>
void PriorityQueue<T>::changePriority(T value, unsigned int priority=0){
    Node<Tuple<int, T>> *temp = this->head;
        
    // if the value is in the head of the queue, remove the head and change the priority
    Tuple<int, T> tVal = temp->getValue();
    if(tVal.getValTwo() == value){
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
