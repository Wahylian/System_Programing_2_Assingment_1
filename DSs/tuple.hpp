#pragma once
#ifndef DEBUG
// debug check
#include "../debug.hpp"
#endif
template <typename T, typename U>
class Tuple{
    private:
    T _first;
    U _second;

    public:
    #pragma region Ctors & Dtors
    // default constructor
    Tuple():
    _first{T()},
    _second{U()}
    {
        #ifdef DEBUG
        std::cout << "Tuple Default constructor" << std::endl;
        #endif
    }
    // constructor
    Tuple(T first, U second):
    _first{first},
    _second{second}
    {
        #ifdef DEBUG
        std::cout << "Tuple constructor" << std::endl;
        #endif
    }

    // copy constructor
    Tuple(const Tuple<T, U> &tuple):
    _first{tuple._first},
    _second{tuple._second}
    {
        // nothing to do
    }
    #pragma endregion

    #pragma region Getters
    // returns a reference to the first value
    T& getFirst(){return this->_first;}

    // returns a reference to the second value
    U& getSecond(){return this->_second;}
    #pragma endregion


    #pragma region Setters
    // sets the first value
    void setFirst(T first){this->_first = first;}

    // sets the second value
    void setSecond(U second){this->_second = second;}
    #pragma endregion
};