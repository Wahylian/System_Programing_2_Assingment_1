#pragma once
#ifndef DEBUG
// debuging check
#include "../debug.hpp"
#endif

#include "node.hpp"
#include <stdexcept>

template <typename T>
class List{
    private:
    // The basic variables of a list
    Node<T> *_start;
    Node<T> *_end;
    int _size;

    public:
    #pragma region Ctors & Dtors
    // constructor
    List():
    _start{nullptr},
    _end{nullptr},
    _size{0}
    {
        #ifdef DEBUG
        std::cout << "List constructor" << std::endl;
        #endif
    }

    // copy constructor
    List(const List<T>& list):
    _start{nullptr},
    _end{nullptr},
    _size{0}
    {  
        // if list is empty, returns
        if(list._size == 0)
            return;

        Node<T> *temp_other = list._start; // gets a pointer to the start of the other list
        
        // copies the first value in list

        // creates a new node with the value at start
        this->_start = new Node<T>(T(temp_other->getValue()));

        // advances temp_other
        temp_other = temp_other->getNext();

        // points temp pointer at the start
        Node<T> *temp = this->_start;
        // points end at temp
        this->_end = temp;

        // copies over every other value in list
        for(int i=1; i<list._size; i++){
            // creates a new node with the value at temp_other
            Node<T> *tNode = new Node<T>(T(temp_other->getValue()));

            // advances temp_other
            temp_other = temp_other->getNext();

            // points temp's next at it
            temp->setNext(tNode);

            // points end at temp's next
            this->_end = temp->getNext();

            // advance temp
            temp = temp->getNext();
        }

        // sets the size of the list
        this->_size = list._size;
    }

    // destructor
    ~List(){
        #ifdef DEBUG
        std::cout << "List destructor" << std::endl;
        #endif
        // deletes all nodes in the list
        Node<T> *temp = this->_start;
        while(temp != nullptr){
            // gets the next node after temp
            Node<T> *next = temp->getNext();
            
            // separetes temp from the list
            temp->setNext(nullptr);
            delete temp;

            // moves to the next node
            temp = next;
        }

        // points start and end to null
        this->_start = nullptr;
        this->_end = nullptr;
    }

    #pragma endregion




    #pragma region Basic Util
    // returns true if the list is empty, else false
    bool isEmpty() const {
        return this->_size == 0;
    }

    // returns the size of the list
    int size() const {
        return this->_size;
    }
    #pragma endregion



    #pragma region Insert Functions
    // insert the value at the end of the list
    void insert(const T& value){
        // creates a new node with a copy of the original value
        Node<T> *node = new Node<T>(value);
        
        // if the list is empty, points start and end at the new node
        if(this->isEmpty()){
            this->_start = node;
            this->_end = node;
            // and increases size by one
            this->_size++;
            return;
        }

        // if the list is not empty, adds the node to the end of the list
        this->_end->setNext(node);
        this->_end = node;
        // increases size by one
        this->_size++;
        return;
    }

    // inserts the value at index i
    void insert(const T& value, int i){
        // if the index is out of range, throws an error
        if(i < 0 || i > this->_size) // allows for i == size, since that will add at the end of the list
            throw std::out_of_range{"index" + std::to_string(i) + " is out of range"};

        // if the list is empty, or i == size, calls the other insert function to add the value
        if(this->isEmpty() || i == this->_size){
            this->insert(value);
            return;
        }
        
        // if the node is inserted in the beginning of the list or in the middle
        // creates a new node, with a copy of the original value
        Node<T> *node = new Node<T>(value);

        // if the node is inserted in the beginning of the list
        if(i == 0){
            // sets the node's next to the start of the list
            node->setNext(this->_start);
            // sets the start of the list to the new node
            this->_start = node;
            // increases size by one
            this->_size++;
            return;
        }
        
        // else, the node is inserted in the middle of the list

        // finds the node that is one index before where node will be inserted
        Node<T> *before = this->_start;
        int j = 0;
        while(j < i-1){
            before = before->getNext();
            j++;
        }

        // saves the node that comes after it
        // we know it must exist since if it didn't, i would be equal to size
        Node<T> *after = before->getNext();

        // points node's next to after
        node->setNext(after);
        // points before's next to node
        before->setNext(node);
        // increases size by one
        this->_size++;
        return;
    }
    #pragma endregion




    #pragma region Remove Functions
    // removes the first instance of value in the list, returns true on removal and false if the value was not found
    bool remove(const T& value){
        // if the list is empty throw an error, as removing is not possible in an empty list
        if(this->isEmpty())
            throw std::underflow_error{"list is empty"};

        // if the value is in the first node, separate it from the rest of the list
        if(this->_start->getValue() == value){
            // save a pointer to start
            Node<T> *temp = this->_start;

            // if the list has only one node, points end to null
            if(this->_start == this->_end)
                this->_end = nullptr;

            // move start to the next node
            this->_start = this->_start->getNext();
            // separate temp from the list
            temp->setNext(nullptr);
            // decrease size by one
            this->_size--;

            // deletes temp from the memory
            delete temp;

            // return true, as the value was removed
            return true;
        }

        // saves a temporary pointer to the list
        Node<T> *temp = this->_start;
        // saves a pointer to the next node
        Node<T> *next = temp->getNext();

        // advances temp and next until next has an instance of value, or next is null
        while(next != nullptr){
            // gets the value stored in next
            T &val = next->getValue();

            // if the val is the same as value, separates next from the list
            if(value == val){
                // if next is the end of the list, points end to temp
                if(next == this->_end)
                    this->_end = temp;

                // separates next from the list
                temp->setNext(next->getNext());
                next->setNext(nullptr);
                // deletes next from the memory
                delete next;

                this->_size--;

                // return true, as the value was removed
                return true;
            }
            
            // advance temp and next
            temp = next;
            next = next->getNext();
        }

        // if value was not found in the list, return false
        return false;
    }

    // pops the value at index i, by default pops the first index
    T pop(int i=0) {
        // if the list is empty, throw an error
        if(this->isEmpty())
            throw std::underflow_error{"list is empty"};

        // if the index is out of range, throw an error
        if(i < 0 ||i >= this->_size)
            throw std::out_of_range{"index " + std::to_string(i) + " out of range"};

        // if the index is 0, pop the first value
        if(i == 0){
            // save a pointer to the start
            Node<T> *temp = this->_start;

            // if the start and the end are the same, points end to null
            if(this->_end == this->_start)
                this->_end = nullptr;
            
            // points start to the next node
            this->_start = this->_start->getNext();
            // separates temp from the list
            temp->setNext(nullptr);

            // decrease size by one
            this->_size--;

            // saves the value in temp
            T tVal = temp->getValue();
            // deletes temp from the memory
            delete temp;

            // returns the value stored in temp
            return tVal;
        }

        // finds the node that is one index before where node will be removed
        Node<T> *before = this->_start;
        int j = 0;
        while(j < i-1){
            before = before->getNext();
            j++;
        }

        // saves a pointer to the node that will be removed
        Node<T> *node = before->getNext();

        // saves a pointer to the node that comes after it
        // it must exist as i is in the range of the list
        Node<T> *after = node->getNext();

        // separates node from the list
        before->setNext(after);
        node->setNext(nullptr);

        // decrease size by one
        this->_size--;

        // saves the value in node
        T tVal = node->getValue();

        // deletes node from the memory
        delete node;

        // returns the value stored in node
        return tVal;
    }
    #pragma endregion

    // returns a reference to the value at index i
    T& getValue(int i) const {
        // if the index is out of range, throw an error
        if(i < 0 ||i >= this->_size)
            throw std::out_of_range{"index " + std::to_string(i) + " out of range"};

        // finds the node at index i
        Node<T> *temp = this->_start;
        int j = 0;
        while(j < i){
            temp = temp->getNext();
            j++;
        }

        // returns the value stored in the node
        return temp->getValue();
    }

    // retuurns the index of the first instance of value in the list, if the value is not in the list, returns -1
    int find(const T &value) const {
        // if the list is empty, throw an error, as searching is not possible in an empty list
        if(this->isEmpty())
            throw std::underflow_error{"list is empty"};
        
        // saves a pointer to the start of the list
        Node<T> *temp = this->_start;
        int i = 0;
        // advances temp until it finds the value or reaches the end of the list
        while(temp != nullptr){
            // if the value is found, return the index
            if(temp->getValue() == value)
                return i;
            
            // advance temp and i
            temp = temp->getNext();
            i++;
        }
        // if the end of the list is reached, return -1
        return -1;
    }

    // returns true if the value is in the list, else false
    bool isExists(const T &value) const {
        // if the list is empty, return false
        if(this->isEmpty())
            return false;

        // if the value is found in the list, return true
        return this->find(value) != -1;
    }
};