#ifndef LIST
#define LIST
// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/
// inspired by the list of functions in the python implementation of list https://www.geeksforgeeks.org/list-methods-python/
#include "node.hpp"
#include <stdexcept>

template <typename T>

// this is a basic implementation of a list
class List{
    private:
    Node<T> *start;
    Node<T> *end;
    int size;

    public:
    // constructor
    List(){
        this->start = nullptr;
        this->end = nullptr;
        this->size = 0;
    }
    // destructor
    ~List(){
        // while the list is not empty, save the start node temporerily, remove it from the list
        // and delete it 
        Node<T> *temp = this->start;
        while(temp != nullptr){
            Node<T> *next = temp->getNext();
            // seperates temp from the list
            temp->setNext(nullptr);
            delete temp;

            // advances the pointer
            temp = next;
        }
    }

    // returns true if the list is empty, else false
    bool isEmpty(){
        if(this->size == 0)
            return true;
        return false;
    }

    // returns the size of the list
    int getSize(){
        return this->size;
    }

    // inserts the value at the end of the list
    void insert(T value){
        // inserts at the end of the list
        this->insert(value, this->size);
    }

    // inserts the value at the provided index
    void insert(T value, int index){
        // checks if index is out of range, allow for index to be equal to size, since that will add at the end of the list
        if(index < 0 || index > this->size)
            throw std::out_of_range{"index out of range"};

        // creates a temp pointer to the node
        Node<T> *temp = new Node<T>(value);

        // there are 3 cases:
        // 1) index is 0
        if(index == 0){
            // points temp to the start of the current list
            temp->setNext(this->start);
            // sets the start of the list to point at temp
            this->start = temp;
        }
        // 2) index is size
        else if(index == this->size){
            // points the end of the current list to temp
            (this->end)->setNext(temp);
            // sets the end of the list to point at temp
            this->end = temp;
        }
        // 3) index is in the middle of the list
        else{
            Node<T> *before = this->start;
            // reaching the node that will be right before temp after the insertion
            for(int i=0; i < index-1; i++){
                before = before->getNext();
            }
            // getting the node that will be after temp
            Node<T> *after = before->getNext();

            // inserting temp
            temp->setNext(after);
            before->setNext(temp);
        }

        // increases the size of the list by 1
        this->size++;
    }

    // removes first instance of value T, returns true if the value was removed, else false
    bool remove(T value){
        // if the list is empty throw an error
        if(this->isEmpty())
            throw std::underflow_error{"list is empty"};

        // check the case for if the value is saved in start
        if((this->start)->getValue() == value){
            Node<T> *temp = this->start;
            // advances the start by one
            this->start = (this->start)->getNext();
            // seperates temp from the list
            temp->setNext(nullptr);

            // decrease size by 1
            this->size--;

            // the value was removed
            return true;
        }

        // goes over the list and removes the first instance of value T
        Node<T> *temp = this->start;
        Node<T> *next = temp->getNext(); // gets the next value after temp
        // advance temp and next while next is not null
        while(next != nullptr){
            // if next's value is equal to value
            // remove next from the list
            if(next->getValue() == value){
                temp->setNext(next->getNext());
                // sets next's next to null
                next->setNext(nullptr);

                // decrease size by 1, as the value was removed
                this->size--;

                // after seperating next, return true
                return true;
            }

            // moves both pointers one step forward
            temp = next;
            next = next->getNext();
        }

        // if this part was reached, the value was not in the list, and so returns false
        return false;
    }
 
    // removes value at index, and returns a reference to the value stored there, pop's the first index by default
    T& pop(int index=0){
        // checks if index is out of range, does not allow for index to be equal to size
        if(index < 0 || index >= this->size)
            throw std::out_of_range{"index out of range"};

        // in the case of removing start
        if(index == 0){
            Node<T> *temp = this->start;
            // if temp is also the end, points end at nullptr
            if(temp == this->end)
                this->end = nullptr;

            // advances start to the next node
            this->start = temp->getNext();

            // seperates temp from the list
            temp->setNext(nullptr);

            // decrease size of list by 1
            this->size--;
        
            // returns the value stored in temp
            return temp->getValue();
        }

        int i = 0;
        Node<T> *temp = this->start;
        // advancing until temp points to the node at index-1
        while(i < index-1){
            temp = temp->getNext();
            i++;
        }
        
        // now we need the node at index+1
        // we know that next exists since index is in range
        Node<T> *next = temp->getNext();
        Node<T> *nnext = next->getNext();

        // check if next is the end of the list
        if(next == this->end){
            // if next is the end, points end at temp
            this->end = temp;
        }

        // seperates next from the list
        temp->setNext(nnext);
        next->setNext(nullptr);

        // decreases size by 1  
        this->size--;

        // returns the value at index
        return next->getValue();
    }

    // returns the reference to the value at index i
    T& getValue(int index){
        // checks if index is out of range, does not allow for index to be equal to size
        if(index < 0 || index >= this->size)
            throw std::our_of_range{"index out of range"};

        int i = 0;
        Node<T> *temp = this->start;
        // advancing until temp points to the node at index-1
        while(i < index){
            temp = temp->getNext();
            i++;
        }
        
        return temp->getValue();
    }

    // returns the index of the first instance of value, or -1 if it is not in the list
    int getIndex(T value){
        Node<T> *temp = this->start;
        for(int i=0; i < this->size; i++){
            if(temp->getValue() == value)
                return i;
            temp = temp->getNext();
        }
        // if the loop ends, the value is not in the list
        return -1;
    }
    // returns true if the value is in the list, else false
    bool isExists(T value){
        int i = this->getIndex(value);
        // i == -1 only if value is not in the list
        return i != -1;
    }
};
#endif