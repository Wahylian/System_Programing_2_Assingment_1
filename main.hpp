#include "graph.hpp"
#include "algorithm.hpp"
#include <iostream>

// this function adds edges to graph g based on 
void add_edges(Graph& g);

// this function runs the bfs algorithm on graph g, and prints the bfs graph that was created
void run_bfs(Graph g);

// this function runs the dfs algorithm on graph g, and prints the dfs graph that was created
void run_dfs(Graph g);

// this function runs the dijakstra algorithm on graph g, and prints the graph of shortest paths that was created
void run_dijkstras(Graph g);

// this function runs the prims algorithm on graph g, and prints the minimal spanning tree that was created
void run_prims(Graph g);

// this function runs the kruskals algorithm on graph g, and prints the minimal spanning tree that was created
void run_kruskals(Graph g);

// a function that lets the user choose a vertex from the graph
unsigned int choose_vertex(Graph g);

// prints what options the user has
void print_options(){
    std::cout << "Please select an option about what to do with the graph:" << std::endl;
    std::cout << "1. Add edges to the graph" << std::endl;
    std::cout << "2. Run BFS on the graph" << std::endl;
    std::cout << "3. Run DFS on the graph" << std::endl;
    std::cout << "4. Run Dijkstras on the graph" << std::endl;
    std::cout << "5. Run Prims on the graph" << std::endl;
    std::cout << "6. Run Kruskals on the graph" << std::endl;
    std::cout << "7. Print the graph" << std::endl;
    std::cout << "8. End the program" << std::endl;
}

// runs the option the user selected
void select_option(Graph& g, int option){
    #ifdef DEBUG
    std::cout << "prints graph" << std::endl;
    g.print_graph();
    #endif
    // the option must be a vaild option, otherwise the program wouldn't have called this function
    switch(option){
        case 1:
            // adds edges to the graph
            add_edges(g);
            break;
        case 2:
            // runs BFS on the graph
            run_bfs(g);
            break;
        case 3:
            // runs DFS on the graph
            run_dfs(g);
            break;
        case 4:
            // runs Dijkstras on the graph
            run_dijkstras(g);
            break;
        case 5:
            // runs Prims on the graph
            run_prims(g);
            break;
        case 6:
            // runs Kruskals on the graph
            run_kruskals(g);
            break;
        default:
            // prints the graph
            g.print_graph();
            break;
    }
}