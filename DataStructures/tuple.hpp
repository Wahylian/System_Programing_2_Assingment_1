#ifndef TUPLE
#define TUPLE
//this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/

template <typename T, typename G>

// this is a basic implementation of a tuple
class Tuple{
    private:
    T valOne;
    G valTwo;

    public:
    // constructor
    Tuple(T valOne, G valTwo):
        valOne{valOne},
        valTwo{valTwo}
    {}

    #pragma region getters
    // returns the first value stored in the tuple
    T getValOne(){
        return this->valOne;
    }
    // returns the second value stored in the tuple
    G getValTwo(){
        return this->valTwo;
    }
    #pragma endregion
    #pragma region setters 
    // sets the value of valOne to valOne
    void setValOne(T valOne){
        this->valOne = valOne;
    }
    // sets the value of valTwo to valTwo
    void setValTwo(G valTwo){
        this->valTwo = valTwo;
    }
    #pragma endregion
};
#endif