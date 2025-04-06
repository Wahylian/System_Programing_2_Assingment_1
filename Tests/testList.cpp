// rido1607@gmail.com
#include "doctest.h"
#include "../DSs/list.hpp"
#include "../Graphs/edge.hpp"

TEST_CASE("Testing List Initiallization"){
    // creates an instance of a list
    List<int> list;

    // checks if the list is empty
    SUBCASE("List is empty"){
        CHECK(list.isEmpty() == true);
    }

    // checks the list has a size of 0
    SUBCASE("List size is 0"){
        CHECK(list.size() == 0);
    }
}

TEST_CASE("Test Copy Constructor"){
    // test with edges as they are a complex object type
    List<Edge> *og_list = new List<Edge>();

    // inserts multiple edges
    og_list->insert(Edge(5, 4));
    og_list->insert(Edge(0, 9));
    og_list->insert(Edge(4, 5));
    og_list->insert(Edge(8, 2));

    // check that the list has 4 edges
    CHECK(og_list->size() == 4);

    // copies the list
    List<Edge> *copy_list = new List<Edge>(*og_list);

    // checks that the pointers point to different locations in the heap
    CHECK(og_list != copy_list);

    // checks that all the values in the original are in the copy
    // and that they are not in the same location
    CHECK(og_list->size() == copy_list->size());
    for(int i=0; i<og_list->size(); i++){
        // checks the values were copied in the correct order
        CHECK(og_list->getValue(i) == copy_list->getValue(i));
        // checks they are not stored in the same memory address
        CHECK(&(og_list->getValue(i)) != &(copy_list->getValue(i)));
    }

    // checking that removing a value from copy doesn't affect the original
    Edge e = copy_list->pop(2);

    // checks that only the copy was affected
    CHECK(og_list->size() == 4);
    CHECK(copy_list->size() == 3);
    CHECK(og_list->isExists(e) == true);
    CHECK(copy_list->isExists(e) == false);

    // deleting the lists
    delete og_list;
    delete copy_list;
}

TEST_CASE("Testing List Insert"){
    // creates an instance of a list
    List<int> list;

    // inserts a value to the list
    list.insert(5);

    // checks if the list is empty
    SUBCASE("List is not empty"){
        CHECK(list.isEmpty() == false);
    }

    // checks the list has a size of 1
    SUBCASE("List size is 1"){
        CHECK(list.size() == 1);
    }

    // checks if the value at index 0 is 5
    SUBCASE("Value at index 0 is 5"){
        CHECK(list.getValue(0) == 5);
    }

    // inserts multiple values to list
    for(int i = 0; i < 10; i++)
        list.insert(i);
    
    // makes sure the list is the correct size
    SUBCASE("List size is 11"){
        CHECK(list.size() == 11);
    }

    // checks insertion at index i
    SUBCASE("Inserting 10 at index 4"){
        // checking the value at index 4 (will be 3 since index 0 is 5)
        CHECK(list.getValue(4) == 3);

        // inserts 10 at index 4
        list.insert(10, 4);
        // checks that the value at index 4 is now 10
        CHECK(list.getValue(4) == 10);
        // checks that the value at index 5 is now 3 (as 3 was pushed one index back)
        CHECK(list.getValue(5) == 3);

        // checks that the size of the list is now 12
        CHECK(list.size() == 12);
    }

    // check insertion at the end of the list
    SUBCASE("Insertion at the end of the list"){
        int size = list.size(); // saves the size of the list

        // inserts 20 at the end of the list
        list.insert(20, size);
        // checks that the value at the last index is now 20
        CHECK(list.getValue(size) == 20);
        // checks that the size of the list is now size+1
        CHECK(list.size() == size+1);
    }

    // checking insertion at a negative index
    SUBCASE("Insertion at a negative index"){
        // attempts to insert at a negative index
        CHECK_THROWS(list.insert(20, -1));
    }

    // checking insertion at an index bigger than size
    SUBCASE("Insertion at an index outside of range"){
        int size = list.size(); // saves the size of the list

        // attempts to insert at size()+1
        CHECK_THROWS(list.insert(20, size+1));
    }
}

TEST_CASE("Testing List Remove"){
    // checks that the remove function fails on an empty list
    SUBCASE("Remove from empty list"){
        // creates an instance of a list
        List<int> list;

        CHECK_THROWS(list.remove(0));
    }
    
    // checks that the remove function returns true on removal of an existing value
    SUBCASE("Remove an existing value"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);

        CHECK(list.remove(5) == true);
    }

    // check that the remove function returns false on removal of a non-existing value
    SUBCASE("Remove a non-existing value"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);

        CHECK(list.remove(15) == false);
    }

    // checks that the remove function will not cause an error upon removing the final value
    SUBCASE("Remove the last value"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);

        // checks that the size of the list is 10
        CHECK(list.size() == 10);

        // removes the last value in the list
        CHECK(list.remove(9) == true);

        // checks that the size of the list is now 9
        CHECK(list.size() == 9);

        // attempt to insert a value to the queue
        CHECK_NOTHROW(list.insert(20));
        // checks that the list now has a size of 10
        CHECK(list.size() == 10);
        // checks that the value at index 9 is now 20
        CHECK(list.getValue(9) == 20);
    }

    SUBCASE("Removing everything and readding it"){
        // creates an instance of a list
        List<int> list = List<int>();

        // inserts multiple values to list
        for(int i=0; i<10; i++)
            list.insert(i);
        // checks that the size of the list is 10
        CHECK(list.size() == 10);
        // removes all values from the list
        for(int i=9; i>=0; i--)
            CHECK(list.remove(i)== true);
        // checks that the size of the list is 0
        CHECK(list.size() == 0);
        
        // attempts to reinsert the values
        for(int i=0; i<10; i++)
            CHECK_NOTHROW(list.insert(i)); // checks no error is thrown
        
        // checks that the size of the list is 10
        CHECK(list.size() == 10);
    }
}

TEST_CASE("Testing List Popping"){
    // checks that the pop function fails on an empty list
    SUBCASE("Pop from empty list"){
        // creates an instance of a list
        List<int> list;

        CHECK_THROWS(list.pop());
    }

    // checks that the pop function fails on an out of range index
    SUBCASE("Pop from out of range index"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);

        CHECK_THROWS(list.pop(15));
    }

    // checks that the pop function fails on a negative index
    SUBCASE("Pop at negative index"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);
        CHECK_THROWS(list.pop(-3));
    }

    // checks that the pop function returns the correct value
    SUBCASE("Pop value at index 4"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);
        // checks that the size of the list is 10
        CHECK(list.size() == 10);

        // attempts to pop the value at index 4
        CHECK(list.pop(4) == 4);

        // checks that the size of the list is now 9
        CHECK(list.size() == 9);
    }

    // popping at end of list
    SUBCASE("Pop at the end of the list"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);
        // saves the size of the list
        int size = list.size();
        // pops the last value in the list
        CHECK(list.pop(size-1) == size-1);
        // checks that the size of the list is now size-1
        CHECK(list.size() == size-1);

        // attempt to insert a value to the end of the list
        CHECK_NOTHROW(list.insert(20, size-1));
    }

    // popping all the values in the list 
    SUBCASE("Pop everything and Reinsert it"){
        // creates an instance of a list
        List<int> list;

        // inserts multiple values to list
        for(int i = 0; i < 10; i++)
            list.insert(i);
        
        // checks that the size of the list is 10
        CHECK(list.size() == 10);

        // pops all the values in the list from the end
        for(int i = 9; i >= 0; i--){
            // checks that the value popped is i
            CHECK(list.pop(i) == i);
        }

        // checks that the size of the list is 0
        CHECK(list.size() == 0);

        // attempts to reinsert the values
        for(int i = 0; i < 10; i++)
            CHECK_NOTHROW(list.insert(i));
    }
}

TEST_CASE("Test getValue"){
    List<int> list;

    // inserts multiple values to list
    for(int i = 0; i < 10; i++)
        list.insert(i);
    
    // checks that the get value function fails on an out of range index
    SUBCASE("Get value from out of range index"){
        CHECK_THROWS(list.getValue(15));
    }

    // checks that the get value function fails on an input of a negative index
    SUBCASE("Get value from a negative index"){
        CHECK_THROWS(list.getValue(-4));
    }

    // checks that the get value function returns the correct value
    SUBCASE("Get value at any index"){
        for(int i = 0; i < list.size(); i++){
            // checks that the value at index i is i
            CHECK(list.getValue(i) == i);
        }
    }
}

TEST_CASE("Test find function"){
    List<int> list;

    // checks that find throws an error when used on an empty list
    SUBCASE("Find on empty list"){
        CHECK_THROWS(list.find(0));
    }

    // inserts multiple values to list
    for(int i = 0; i < 10; i++)
        list.insert(i);
    
    // checks that the find function returns the correct index
    SUBCASE("Find correct index"){
        for(int i=0; i<list.size(); i++){
            // checks that the index of i is i
            CHECK(list.find(i) == i);
        }
    }

    // checks that the find function returns -1 on a non-existing value
    SUBCASE("Find non-existing value"){
        // checks that the index of 15 is -1
        CHECK(list.find(15) == -1);
    }
}

TEST_CASE("Test isExists function"){
    List<int> list;
    
    // checks that isExists returns false on an empty list
    SUBCASE("isExist on empty list"){
        CHECK(list.isExists(0) == false);
    }

    // inserts multiple values to list
    for(int i=0; i<10; i++)
        list.insert(i);
    
    // checks that the is exists function returns true for an existing value
    SUBCASE("isExists on existing value"){
        for(int i=0; i<list.size(); i++){
            // checks that the index of i is true
            CHECK(list.isExists(i) == true);
        }
    }
    
    // checks that the is exists function returns false for a non-existing value
    SUBCASE("isExists on non-existing value"){
        // checks that the index of 15 is false
        CHECK(list.isExists(15) == false);
    }
}

TEST_CASE("Memory Leak Tests"){
    // creates an instance of a list
    List<int> *list = new List<int>();

    // inserts multiple values to list
    for(int i = 0; i < 10; i++)
        list->insert(i);


    // checks that the list is not empty
    SUBCASE("List is not empty"){
        CHECK(list->isEmpty() == false);
    }

    // checks that the list has a size 10
    SUBCASE("List size is 10"){
        CHECK(list->size() == 10);
    }

    // deletes the list
    delete list;
}    
