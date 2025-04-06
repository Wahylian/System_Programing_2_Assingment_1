// rido1607@gmail.com
#include "Graphs/graph.hpp"
#include "Graphs/algorithm.hpp"
#include <iostream>

using namespace graph;

// this function adds edges to graph g
void add_edges(Graph& g);

// this function removes edges from graph g 
void remove_edges(Graph &g);

// this function runs the bfs algorithm on graph g, and prints the bfs graph that was created
void run_bfs(const Graph &g);

// this function runs the dfs algorithm on graph g, and prints the dfs graph that was created
void run_dfs(const Graph &g);

// this function runs the dijkstra algorithm on graph g, and prints the graph of shortest paths that was created
void run_dijkstras(const Graph &g);

// this function runs the prims algorithm on graph g, and prints the minimal spanning tree that was created
void run_prims(const Graph &g);

// this function runs the kruskals algorithm on graph g, and prints the minimal spanning tree that was created
void run_kruskals(const Graph &g);

// a function that lets the user choose a vertex from the graph
int choose_vertex(const Graph &g);

// prints what options the user has
void print_options(){
    std::cout << "Please select an option about what to do with the graph:" << std::endl;
    std::cout << "1. Print the graph" << std::endl;
    std::cout << "2. Add edges to the graph" << std::endl;
    std::cout << "3. Remove edges from the graph" << std::endl;
    std::cout << "4. Run BFS on the graph" << std::endl;
    std::cout << "5. Run DFS on the graph" << std::endl;
    std::cout << "6. Run Dijkstras on the graph" << std::endl;
    std::cout << "7. Run Prims on the graph" << std::endl;
    std::cout << "8. Run Kruskals on the graph" << std::endl;
    std::cout << "9. End the program" << std::endl;
}

// runs the option the user selected
void select_option(Graph& g, int option){
    #ifdef DEBUG
    std::cout << "prints graph" << std::endl;
    g.print_graph();
    #endif
    // the option must be a vaild option, otherwise the program wouldn't have called this function
    switch(option){
        case 2:
            // adds edges to the graph
            add_edges(g);
            break;
        case 3:
            // removes edges from the graph
            remove_edges(g);
            break;
        case 4:
            // runs BFS on the graph
            run_bfs(g);
            break;
        case 5:
            // runs DFS on the graph
            run_dfs(g);
            break;
        case 6:
            // runs Dijkstras on the graph
            run_dijkstras(g);
            break;
        case 7:
            // runs Prims on the graph
            run_prims(g);
            break;
        case 8:
            // runs Kruskals on the graph
            run_kruskals(g);
            break;
        default:
            // prints the graph
            g.print_graph();
            break;
    }
}
