// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/
// this class uses a default value for the generic value, i used the following prompet in chatgpt to learn that it is an option:
// "I have a class in c++ that works on a generic T, I want it to have a default value"

template <typename T>

// this is a basic node class
class Node{
    private:
    T value; // the value in this node
    Node<T> *next; // the next node

    public:
    // constructor
    Node(T value=T(), Node<T> *next=nullptr){
        this->value = value;
        this->next = next;
    }
    // destructor
    ~Node(){
        delete this->next;
        this->next = nullptr;
    }
    #pragma region getters
    // gets the value of the node
    T getValue(){
        return this->value;
    }

    // gets the next node
    Node<T>* getNext(){
        return this->next;
    }
    #pragma endregion
    #pragma region setters
    // sets the value of the node
    void setValue(T value){
        this->value = value;
    }

    // sets the next node
    void setNext(Node<T> *next){
        this->next = next;
    }
    #pragma endregion
};