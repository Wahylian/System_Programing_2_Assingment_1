// rido1607@gmail.com
#include "doctest.h"
#include "../DSs/priorityQueue.hpp"
#include "../Graphs/edge.hpp"

TEST_CASE("Initiating the Priority Queue"){
    // creating an instance of a queue
    PriorityQueue<int> pQ = PriorityQueue<int>();

    // checks that the queue is empty
    SUBCASE("Queue is Empty"){
        CHECK(pQ.isEmpty() == true);
    }

    // checks that the size of the queue is 0
    SUBCASE("Size is 0"){
        CHECK(pQ.size() == 0);
    }

    // checks that the top value throws an error, as the queue is empty
    SUBCASE("Top in empty Queue"){
        CHECK_THROWS(pQ.top());
    }
}

TEST_CASE("Test Copy Constructor"){
    // using edge as it is a complex data type

    PriorityQueue<Edge> *pQ = new PriorityQueue<Edge>();

    // enqueues multiple edges into it
    pQ->enqueue(Edge(3, 5, 2), 5);
    pQ->enqueue(Edge(2, 0, 10), 8);
    pQ->enqueue(Edge(0, 8, -3), 0);
    pQ->enqueue(Edge(5,10, 0), 3);

    // copies the priority Queue
    PriorityQueue<Edge> *copy = new PriorityQueue<Edge>(*pQ);

    // checks each pointer points to a different address
    CHECK(pQ != copy);

    // checks the size of both queues is the same
    CHECK(pQ->size() == pQ->size());

    // checks that for each value in the queue is the same
    while(!pQ->isEmpty()){
        const Edge &e_og = pQ->top();
        const Edge &e_copy = copy->top();

        // compares each edge in the queues
        CHECK(&e_og != &e_copy); // checks the edges are stored in a different address
        // checks the values in the edges are the same
        CHECK(e_og.getVertex1() == e_copy.getVertex1());
        CHECK(e_og.getVertex2() == e_copy.getVertex2());
        CHECK(e_og.getWeight() == e_copy.getWeight());

        // dequeues both queues
        pQ->dequeue();
        copy->dequeue();
    }


    // deletes both lists
    delete pQ;
    delete copy;
}

TEST_CASE("Dequeueing"){
    PriorityQueue<int> pQ = PriorityQueue<int>();

    // checking dequeuing an empty queue
    SUBCASE("Dequeueing Empty Queue"){
        // checks the queue is empty
        CHECK(pQ.isEmpty() == true);

        // checks an error is thrown
        CHECK_THROWS(pQ.dequeue());
    }

    // checking dequeueing from a queue with values
    SUBCASE("Dequeueing from a non-Empty Queue"){
        // enqueueing values to the queue
        for(int i=0; i<10; i++)
            pQ.enqueue(i);
        
        // checks the queue is not empty
        CHECK(pQ.isEmpty() != true);

        // checks that the size is equal to 10
        CHECK(pQ.size() == 10);

        // checks that the dequeueing decreases the size of the queue
        for(int i=0; i<10; i++){
            // checks that the dequeued value is correct
            CHECK(pQ.dequeue() == i);

            // checks the size of the queue decreased
            CHECK(pQ.size() == 9-i);
        }
    }
}

TEST_CASE("Checking Top"){
    SUBCASE("Top in an Empty Queue"){
        PriorityQueue<int> pQ = PriorityQueue<int>();
        // checks that the queue is empty
        CHECK(pQ.isEmpty() == true);

        // checks an error is thrown on top call
        CHECK_THROWS(pQ.top());
    }

    SUBCASE("Top in a non empty queue"){
        PriorityQueue<int> pQ = PriorityQueue<int>();
        
        // enqueue a value into the queue
        pQ.enqueue(5, 1);
        CHECK(pQ.top() == 5);
    
        // enqueue another value with a higher priority
        pQ.enqueue(8,3);
        CHECK(pQ.top() == 8);
        
        // enqueue another value with a lower priority
        pQ.enqueue(1, 2);
        CHECK(pQ.top() == 8);

        // checks that all 3 values are in the queue
        CHECK(pQ.size() == 3);
    }
}

TEST_CASE("Checking Contains"){
    SUBCASE("Contains in Empty Queue"){
        PriorityQueue<int> pQ = PriorityQueue<int>();
        // checks that the queue is empty
        CHECK(pQ.isEmpty() == true);

        // checks an error is thrown on contains call
        CHECK_THROWS(pQ.contains(3));
    }

    SUBCASE("Contains an existing value"){
        PriorityQueue<int> pQ = PriorityQueue<int>();
        // checks that the queue is empty
        CHECK(pQ.isEmpty() == true);

        // enqueues a value into the queue
        pQ.enqueue(10, 4);

        // checks that the queue contains the value
        CHECK(pQ.contains(10) == true);
    }

    SUBCASE("Contains a non-existing value"){
        PriorityQueue<int> pQ = PriorityQueue<int>();
        // checks that the queue is empty
        CHECK(pQ.isEmpty() == true);

        // enqueues a value into the queue
        pQ.enqueue(10, 4);

        // checks that the queue contains a non-existing value
        CHECK(pQ.contains(3) != true);
    }
}

TEST_CASE("Checking priority"){
    // Enqueueing values into the queue with default priorities
    SUBCASE("Enqueuing into Queue with Default Priority"){
        PriorityQueue<int> pQ = PriorityQueue<int>();
        
        // checks the queue is empty
        CHECK(pQ.isEmpty() == true);

        // enqueuing multiple values with default priority
        for(int i=0; i<10; i++)
            pQ.enqueue(i); // default priority is 0

        // checks the size is correct
        CHECK(pQ.size() == 10);
        
        // checking all values are in the queue
        for(int i=0; i<10; i++)
            CHECK(pQ.contains(i) == true);

        // since all values are with the same priority,
        // the priority queue should act like a normal queue
        for(int i=0; i<10; i++)
            CHECK(pQ.dequeue() == i);   

        // checks the queue is empty
        CHECK(pQ.isEmpty() == true);
    }

    // Enqueueing values into the queue with a priority
    SUBCASE("Enqueueing into Queue with Priority"){
        PriorityQueue<int> pQ = PriorityQueue<int>();

        // check that the queue is empty
        CHECK(pQ.isEmpty() == true);

        // enqueuing multiple values into the queue with increasing priorities
        for(int i=-10; i<10; i++)
            pQ.enqueue(i, i);
        
        // checks the size is correct
        CHECK(pQ.size() == 20);

        // checking all values are in the queue
        for(int i=-10; i<10; i++)
            CHECK(pQ.contains(i) == true);
        
        // since the values are enqueued with a priority equal to them, 
        // the priority queue should act like a stack
        for(int i=-10; i<10; i++)
            CHECK(pQ.dequeue() == -i-1);
        
        // checks the queue is empty
        CHECK(pQ.isEmpty() == true);
    }
}

TEST_CASE("Change Priority"){
    SUBCASE("Changing priority on empty queue"){
        PriorityQueue<int> pQ = PriorityQueue<int>();

        // attempts to change priority
        CHECK_THROWS(pQ.changePriority(5, 10));
    }

    SUBCASE("Changing the Priority of existing values"){
        PriorityQueue<int> pQ = PriorityQueue<int>();

        // enqueueing values into the queue, with a default priority
        for(int i=0; i<10; i++)
            pQ.enqueue(i);
    
        // checks that the top value has is correct
        CHECK(pQ.top() == 0);
    
        // checks the value 3 is in the queue
        CHECK(pQ.contains(3) == true);
    
        // changes the priority of the value 3 to 10
        // should cause it to move to the start
        pQ.changePriority(3, 10);
        // checks that 3 is at the top of the queue
        CHECK(pQ.top() == 3);
    
        // changes the priority of multiple values
        pQ.changePriority(8, 4);
        pQ.changePriority(2, 2);
    
        // changes the priority of 3 to 3
        pQ.changePriority(3, 3);
        // checks that 8 is at the top
        CHECK(pQ.top() == 8);
    
        // checks that the order of the top 3 values is 8, 3, 2
        CHECK(pQ.dequeue() == 8);
        CHECK(pQ.dequeue() == 3);
        CHECK(pQ.dequeue() == 2);
    }
    
    SUBCASE("Changes priority of non-existing value"){
        PriorityQueue<int> pQ = PriorityQueue<int>();

        // checks the queue is empty
        CHECK(pQ.isEmpty() == true);

        // enqueuing values to queue
        for(int i=0; i<10; i++)
            pQ.enqueue(i);

        // checks that the value -5 doesn't exist
        CHECK(pQ.contains(-5) == false);

        // attempts to change the priority of -5
        CHECK_THROWS(pQ.changePriority(-5, 10));
    }
}

TEST_CASE("Memory Leak Tests"){
    // creates a new instance of priority queue
    PriorityQueue<int> *pQ = new PriorityQueue<int>();
    
    // checks the queue is empty
    CHECK(pQ->isEmpty() == true);

    // enqueues multiple values into the queue
    pQ->enqueue(2,4);
    pQ->enqueue(5,2);
    pQ->enqueue(10);
    pQ->enqueue(8, 6);
    pQ->enqueue(1, 5);

    // checks the size is 5
    CHECK(pQ->size() == 5);

    // dequeues multiple values from the queue
    CHECK(pQ->dequeue() == 8);
    CHECK(pQ->dequeue() == 1);

    // checks the size is 3
    CHECK(pQ->size() == 3);

    // deletes the queue
    delete pQ;
}