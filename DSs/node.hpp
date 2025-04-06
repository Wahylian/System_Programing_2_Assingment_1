// rido1607@gmail.com
#pragma once

template <typename T>
class Node{
    private:
    T _value;
    Node<T> *_next;

    public:
    #pragma region Ctors & Dtors
    // default constructor
    Node():
    _value{T()},
    _next{nullptr}
    {
        // nothing to do
    }
    // constructor
    Node(T value, Node<T> *next=nullptr):
    _value{value},
    _next{next}
    {
        // nothing to do
    }
    #pragma endregion


    #pragma region Getters
    // returns the value of the node
    T& getValue() {return this->_value;}

    // returns the next node
    Node<T>* getNext() {return this->_next;}

    #pragma endregion




    #pragma region Setters
    // sets the value of the node
    void setValue(T value){this->_value = value;}

    // sets the next node
    void setNext(Node<T> *next){this->_next = next;}
    #pragma endregion
};