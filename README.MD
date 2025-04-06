<h1> Project 1 - System Programing 2</h1>
<h3> By: Ido Ron <br/>
 ID: 215312729</h3>

<h2> This Project Includes: </h2>

### **Features**

1.  **A [Main](main.cpp) file which allows you to run either a prebuilt graph or build your own graph.**<br/>
    With that graph you are given the option to add or remove edges from it or run the following algorithms on it:<br/>
    * BFS Algorithm for creating an Un-Weighted Tree.
    * DFS Algorithm for creating an Un-Weighted Forest.
    * Dijkstra Algorithm for Shortest Weighted Path.
    * Prim's Algorithm for MST.
    * Kruskal Algorithm for MST.
2. **A [Tests](Tests) folder** which runs tests on all data structures and functions in the project.
3. **A [Data Structure](DSs) Folder** with the following data structures that were used in the project:<br/>
    * [List](DSs/list.hpp)
    * [Node](DSs/node.hpp)
    * [Priority Queue](DSs/priorityQueue.hpp) (Higher Priority -> More Important)
    * [Reverse Priority Queue](DSs/reversePriorityQueue.hpp) (Lower Priority -> More Important)
    * [Tuple](DSs/tuple.hpp)
    * [UnionFind](DSs/unionFind.cpp)
4. **A [MAKEFILE](Makefile)** allowing to run the following commands: <br/>
    * **make Main** <br/>
    Which creates a Main executable file that runs the main.cpp file.
    * **make valgrind** <br/>
    Which runs the Main exectuable with Valgrind to check for Memory Leaks.
    * **make test** <br/>
    Which creates a test executable file that runs all the test files in the project.
    * **make valgrind-test** <br/>
    Which runs the test executable file with Valgrind to check for Memory Leaks (Some of the tests are built to check for Mmemory Leaks).
    * **make clean** <br/>
    Which removes all object and executable files from the project.


---

<h2>List of sites and places i used for help:</h2>
1. On Filtering input:<br/>
    https://stackoverflow.com/questions/3875780/filtering-out-invalid-user-inputs <br/>
2. On using Generics in C++:<br/>
    https://www.geeksforgeeks.org/generics-in-c/
3. The usual functions for an Implementation of List:<br/>
    https://www.geeksforgeeks.org/list-methods-python/ <br/>
4. The implementations of the Different Algorithms are based on the implementations shown in the Algorithms 1 course in semester 1 <br/>
5. The Adjacency List implementation is based on the implementation presented at: <br/>
https://en.wikipedia.org/wiki/Adjacency_list

6. To figure out how to use ['doctest.h'](Tests/doctest.h) i used github's copilot with the following prompt: <br/>
"please give me an example on how to create a test using doctest"<br/>
It's reply was:<br/>
Here’s an example of how to create a test using `doctest`. This example demonstrates how to test a simple function using the `doctest` framework.

---

### **Example: Testing a Function**

#### **Code to Test**
Suppose you have a function `add` that adds two integers:

```cpp
int add(int a, int b) {
    return a + b;
}
```

#### **Test Case**
You can write a test case for the `add` function using `doctest` as follows:

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Source/math_utils.cpp"

TEST_CASE("Testing the add function") {
    CHECK(add(1, 1) == 2);  // Test case 1: 1 + 1 = 2
    CHECK(add(-1, 1) == 0); // Test case 2: -1 + 1 = 0
    CHECK(add(0, 0) == 0);  // Test case 3: 0 + 0 = 0
    CHECK(add(100, 200) == 300); // Test case 4: 100 + 200 = 300
}
```

---

### **Explanation**

1. **Include doctest.h**:
   - The `#include "doctest.h"` line includes the `doctest` testing framework.

2. **Define the Main Function**:
   - The `#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN` macro tells `doctest` to generate the `main()` function automatically.

3. **Write Test Cases**:
   - Use `TEST_CASE` to define a test case. Each `TEST_CASE` block can contain multiple `CHECK` statements.
   - Use `CHECK` to verify that the function behaves as expected. If a `CHECK` fails, `doctest` will report the failure.

4. **Run the Tests**:
   - Compile and run the test file. For example:
     ```bash
     g++ -std=c++17 -o test_math_utils test_math_utils.cpp
     ./test_math_utils
     ```

---

### **Output**
When you run the test, you’ll see output like this:

```
===============================================================================
[doctest] test cases:      1 |      1 passed |      0 failed |      0 skipped
[doctest] assertions:      4 |      4 passed |      0 failed |
===============================================================================
```

If any test fails, `doctest` will show the failing assertion, the expected value, and the actual value.

---

### **Additional Features**

- **Subcases**:
  Use `SUBCASE` to test different scenarios within the same `TEST_CASE`:
  ```cpp
  TEST_CASE("Testing edge cases for add function") {
      SUBCASE("Adding zero") {
          CHECK(add(0, 0) == 0);
          CHECK(add(5, 0) == 5);
      }
      SUBCASE("Adding negatives") {
          CHECK(add(-5, -5) == -10);
          CHECK(add(-5, 5) == 0);
      }
  }
  ```

- **Exception Testing**:
  Use `CHECK_THROWS` to verify that a function throws an exception:
  ```cpp
  TEST_CASE("Testing exception handling") {
      CHECK_THROWS_AS(throw std::runtime_error("error"), std::runtime_error);
  }
  ```

Let me know if you need further clarification!

