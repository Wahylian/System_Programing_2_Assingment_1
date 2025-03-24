// this class uses generics, example taken from https://www.geeksforgeeks.org/generics-in-c/
// this class uses a default value for the generic value, i used the following prompet in chatgpt to learn that it is an option:
// "I have a class in c++ that works on a generic T, I want it to have a default value"

template <typename T>

// a binary tree class
class BinNode{
    private:
    T value; // the value in this node
    BinNode<T> *left; // the left node
    BinNode<T> *right; // the right node

    public:
    // constructor
    BinNode(T value=T(), BinNode<T> *left=nullptr, BinNode<T> *right=nullptr){
        this->value = value;
        this->left = left;
        this->right = right;
    }
    // destructor
    ~BinNode(){
        delete this->left;
        this->left = nullptr;
        delete this->right;
        this->right = nullptr;
    }
    #pragma region getters
    // gets the value in the node
    T getValue(){
        return this->value;
    }

    // gets the left node
    BinNode<T>* getLeft(){
        return this->left;
    }

    // gets the right node
    BinNode<T>* getRight(){
        return this->right;
    }
    #pragma endregion
    #pragma region setters
    // sets the value in the node
    void setValue(T value){
        this->value = value;
    }
    
    // sets the left node
    void setLeft(BinNode<T> *left){
        this->left = left;
    }

    // sets the right node
    void setRight(BinNode<T> *right){
        this->right = right;
    }
    #pragma endregion
};
