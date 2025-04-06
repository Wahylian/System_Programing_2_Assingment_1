// rido1607@gmail.com
#include "doctest.h"
#include "../DSs/tuple.hpp"

TEST_CASE("Test Initialization"){
    SUBCASE("Default Constructor"){
        Tuple<int, int> t = Tuple<int, int>();
        // checks that the first value is the default int value
        CHECK(t.getFirst() == int());
        // checks that the second value is the default int value
        CHECK(t.getSecond() == int());
    }
    SUBCASE("Constructor with values"){
        Tuple<int, int> t = Tuple<int, int>(5, 10);
        // checks that the first value is 5
        CHECK(t.getFirst() == 5);
        // checks that the second value is 10
        CHECK(t.getSecond() == 10);
    }
}

TEST_CASE("Test Copy Constructor"){
    // create a tuple
    Tuple<int, int> t1 = Tuple<int, int>(5, 10);
    // copies the tuple
    Tuple<int, int> t2 = Tuple<int, int>(t1);

    // checks that the tuples are not in the same address
    CHECK(&t1 != &t2);
    // checks that the first value in both is equal
    CHECK(t1.getFirst() == t2.getFirst());
    // checks that the second value in both is equal
    CHECK(t1.getSecond() == t2.getSecond());
    // checks that the first value in both is not the same address
    CHECK(&t1.getFirst() != &t2.getFirst());
    // checks that the second value in both is not the same address
    CHECK(&t1.getSecond() != &t2.getSecond());
}

TEST_CASE("Test Getters"){
    Tuple<int, int> t = Tuple<int, int>(5, 10);
    SUBCASE("Get First"){
        CHECK(t.getFirst() == 5); // check that get first returns the correct value
    }
    SUBCASE("Get Second"){
        CHECK(t.getSecond() == 10); // check that get second returns the correct value
    }
}

TEST_CASE("Test Setters"){
    Tuple<int, int> t = Tuple<int, int>(5, 10);
    SUBCASE("Set First"){
        t.setFirst(20); // set the first value to 20
        CHECK(t.getFirst() == 20); // check that get first returns the correct value
    }
    SUBCASE("Set Second"){
        t.setSecond(30); // set the second value to 30
        CHECK(t.getSecond() == 30); // check that get second returns the correct value
    }
}
