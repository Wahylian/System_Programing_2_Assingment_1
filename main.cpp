#include "main.hpp"

unsigned int choose_vertex(Graph g){
    unsigned int v;
    while(true){
        // recieves input from user
        std::cout << "Please enter the vertex:" << std::endl;
        std::cin >> v;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid non-negative integer for the vertex:" << std::endl;
        }
        else if(v >= g.getSize()){
            std::cout << "Please enter a valid vertex number:" << std::endl;
        }
        else{
            break;
        }
    }
    return v;
}

void add_edges(Graph& g){
    std::cout << "The graph has " << g.getSize() << " vertices" << std::endl;
    std::cout << "Please enter the edge you would like to add:" << std::endl;
    unsigned int v1, v2;
    int weight;

    bool add_edge = true;
    while(add_edge){
        bool valid_edge = false;
        // makes sure to not allow input of the same vertex twice
        while(!valid_edge){
            // makes sure for valid input for v1
            std::cout << "Vertex One:" << std::endl;
            v1 = choose_vertex(g);

            #ifdef DEBUG
            std::cout << "v1: " << v1 << std::endl;
            g.print_graph();
            #endif

            // makes sure for valid input for v2
            std::cout << "Vertex Two:" << std::endl;
            v2 = choose_vertex(g);
            g.print_graph();
            #ifdef DEBUG
            std::cout << "v2: " << v2 << std::endl;
            #endif

            // makes sure the vertices are not the same
            if(v1 == v2){
                std::cout << "Please enter two different vertices" << std::endl;
            }
            else{
                valid_edge = true;
            }
        }
        // makes sure for valid input for weight
        while(true){
            // recieves input from user
            std::cin >> weight;
    
            if(std::cout.fail()){
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Please enter a valid integer for the weight:" << std::endl;
            }
            else{
                break;
            }
        }

        // adds the edge to the graph
        g.addEdge(v1, v2, weight);

        // asks the user if they would like to add another edge
        std::cout << "Would you like to add another edge? (y/n)" << std::endl;
        char answer;
        while(true){
            std::cin >> answer;
            if (answer == 'n' || answer == 'N')
            {
                add_edge = false;
                break;
            }
            else if (answer == 'y' || answer == 'Y')
            {
                break;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Please enter a valid answer" << std::endl;
            }
        }
    }
}

void run_bfs(Graph g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // gets the starting vertex from the user
    std::cout << "Starting vertex:" << std::endl;
    unsigned int s = choose_vertex(g);

    // runs bfs using the starting vertex
    Graph bfsGraph = a.bfs(g, s);

    // prints the graph
    std::cout << "The BFS graph from vertex " << s << " is:" << std::endl;
    bfsGraph.print_graph();
}

void run_dfs(Graph g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // runs dfs on the graph
    Graph dfsGraph = a.dfs(g);

    // prints the graph
    std::cout << "The DFS graph is:" << std::endl;
    dfsGraph.print_graph();
}

void run_dijkstras(Graph g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // gets the starting vertex from the user
    std::cout << "Starting vertex:" << std::endl;
    unsigned int s = choose_vertex(g);

    // runs dijkstras using the starting vertex
    Graph dijkstrasGraph = a.dijakstra(g, s);

    // prints the graph
    std::cout << "The graph of shortest paths from vertex " << s << " is:" << std::endl;
    dijkstrasGraph.print_graph();
}

void run_prims(Graph g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // runs prims on the graph
    Graph primsGraph = a.prim(g);

    // prints the graph
    std::cout << "The minimal spanning tree based on Prim's algorithm is:" << std::endl;
    primsGraph.print_graph();
}

void run_kruskals(Graph g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // runs kruskals on the graph
    Graph kruskalsGraph = a.kruskal(g);

    // prints the graph
    std::cout << "The minimal spanning tree based on Kruskals' algorithm is:" << std::endl;
    kruskalsGraph.print_graph();
}

int main(){
    std::cout << "Hello!, this program allows you to create a graph and run some algorithms on it" << std::endl;
    std::cout << "Please enter the number of vertices in the graph" << std::endl;
    // gets the size of the graph
    unsigned int n;
    
    // makes sure for valid input
    while(true){
        std::cin >> n;

        // checks for valid input
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid positive integer for the amount of vertices:" << std::endl;
        }
        else if(n == 0){
            // the graph must have at least one vertex
            std::cout << "Please enter a valid positive integer for the amount of vertices:" << std::endl;
        }
        else{
            break;
        }
    }

    // creates a graph
    Graph g = Graph(n);

    print_options();

    #ifdef DEBUG
    std::cout << "prints graph" << std::endl;
    g.print_graph();
    #endif

    // receives what the user wants to do
    int option;
    std::cin >> option;
    // run on a loop while the user does not want to end the program
    while(option != 8){
        // makes sure the user entered a valid option
        while(option < 1 || option > 8){
            std::cout << "Please enter a valid option" << std::endl;
            std::cin >> option;
        }

        if(option != 8){
            // runs the option the user selected
            select_option(g, option);

            // asks the user what they would like to do next
            print_options();
            std::cin >> option;
        }
    }
    std::cout << "Thank you for using this program" << std::endl;
    return 0;
}