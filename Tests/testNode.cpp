#include "doctest.h"
#include "../DSs/node.hpp"

TEST_CASE("Test Initialization"){
    SUBCASE("Default Constructor"){
        Node<int> node;

        // checks that the node points to null
        CHECK(node.getNext() == nullptr);
        // checks that the value is the default int value
        CHECK(node.getValue() == int());
    }
    SUBCASE("Constructor with value"){
        Node<int> node = Node<int>(5);

        // checks that the node points to null
        CHECK(node.getNext() == nullptr);
        // checks that the value is 5
        CHECK(node.getValue() == 5);
    }
    SUBCASE("Constructor with value and next"){
        Node<int> node1 = Node<int>(1);
        Node<int> node2 = Node<int>(2, &node1);

        // checks that node2 points to node1
        CHECK(node2.getNext() != nullptr);
        // checks that node2's value is 2
        CHECK(node2.getValue() == 2);
        // checks that node2's next is node1
        CHECK(&node1 == node2.getNext());
    }
}


TEST_CASE("Test Getters"){
    SUBCASE("Get Value"){
        Node<int> node = Node<int>(5);

        // checks that the value is 5
        CHECK(node.getValue() == 5);
    }
    SUBCASE("Get Next"){
        Node<int> node1 = Node<int>(5);
        Node<int> node2 = Node<int>(2, &node1);

        // checks that the next pointer is not null
        CHECK(node2.getNext() != nullptr);
        // checks that the next pointer is node1
        CHECK(&node1 == node2.getNext());
    }
}

TEST_CASE("Test Setters"){
    SUBCASE("Set Value"){
        Node<int> node = Node<int>(5);

        // checks that the value is 5
        CHECK(node.getValue() == 5);
        // sets the value to 10
        node.setValue(10);
    }
    SUBCASE("Set Next"){
        Node<int> node1 = Node<int>(1);
        Node<int> node2 = Node<int>(2);

        // checks that node1's next pointer is null
        CHECK(node1.getNext() == nullptr);

        // sets the next of node1 to node2
        node1.setNext(&node2);

        // checks that node1's next pointer is now to node2
        CHECK(node1.getNext() == &node2);
    }
}