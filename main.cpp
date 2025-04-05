#include "main.hpp"

int choose_vertex(const Graph &g){
    int v;
    while(true){
        // recieves input from user
        std::cout << "Please enter the vertex:" << std::endl;
        std::cin >> v;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid non-negative integer for the vertex:" << std::endl;
        }
        else if(v < 0 ||v >= g.numVertices()){
            std::cout << "Please enter a valid vertex number:" << std::endl;
        }
        else{
            break;
        }
    }
    return v;
}

void add_edges(Graph& g){
    std::cout << "The graph has " << g.numVertices() << " vertices" << std::endl;
    std::cout << "Please enter the edge you would like to add:" << std::endl;
    int v1, v2;
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
            #endif

            // makes sure for valid input for v2
            std::cout << "Vertex Two:" << std::endl;
            v2 = choose_vertex(g);
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
            std::cout << "Please enter the weight of the edge:" << std::endl;
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

void remove_edges(Graph &g){
    std::cout << "The graph has " << g.numVertices() << " vertices" << std::endl;
    std::cout << "Please enter the edge you would like to remove:" << std::endl;
    int v1, v2;

    bool remove_edge = true;
    while(remove_edge){
        bool valid_edge = false;
        // makes sure to not allow input of the same vertex twice
        while(!valid_edge){
            // makes sure for valid input for v1
            std::cout << "Vertex One:" << std::endl;
            v1 = choose_vertex(g);

            #ifdef DEBUG
            std::cout << "v1: " << v1 << std::endl;
            #endif

            // makes sure for valid input for v2
            std::cout << "Vertex Two:" << std::endl;
            v2 = choose_vertex(g);
            #ifdef DEBUG
            std::cout << "v2: " << v2 << std::endl;
            #endif

            // makes sure the vertices are not the same
            if(v1 == v2){
                std::cout << "Please enter two different vertices" << std::endl;
            }
            else if(!g.isEdgeExists(v1, v2)){ // makes sure the edge exists in the graph
                std::cout << "Please enter an edge that exists in the graph" << std::endl;
            }
            else{
                valid_edge = true;
            }
        }

        // removes the edge from the graph
        g.removeEdge(v1, v2);

        // asks the user if they would like to add another edge
        std::cout << "Would you like to add another edge? (y/n)" << std::endl;
        char answer;
        while(true){
            std::cin >> answer;
            if (answer == 'n' || answer == 'N')
            {
                remove_edge = false;
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

void run_bfs(const Graph &g){
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

void run_dfs(const Graph &g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // runs dfs on the graph
    Graph dfsGraph = a.dfs(g);

    // prints the graph
    std::cout << "The DFS graph is:" << std::endl;
    dfsGraph.print_graph();
}

void run_dijkstras(const Graph &g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // gets the starting vertex from the user
    std::cout << "Starting vertex:" << std::endl;
    unsigned int s = choose_vertex(g);

    // runs dijkstras using the starting vertex
    try{
        Graph dijkstrasGraph = a.dijakstra(g, s);

        // prints the graph
        std::cout << "The graph of shortest paths from vertex " << s << " is:" << std::endl;
        dijkstrasGraph.print_graph();
    }
    catch(std::invalid_argument){ // if the dijakstra was attempted to run with an invalid vertex
        std::cout << "Problematic Vertex" << std::endl;
    }
    catch(std::runtime_error){ // if the graph contains a negative edge
        std::cout << "The Dijakstra algorithm doesn't run on graphs with negative edges" << std::endl;
    }
}

void run_prims(const Graph &g){
    // creates an instance of an algorithms object
    Algorithms a = Algorithms();

    // runs prims on the graph
    Graph primsGraph = a.prim(g);

    // prints the graph
    std::cout << "The minimal spanning tree based on Prim's algorithm is:" << std::endl;
    primsGraph.print_graph();
}

void run_kruskals(const Graph &g){
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
    // asks if the user wants a pre-made graph or a personally made graph
    std::cout << "Would you like a pre-made graph, or to make your own? (1 for pre-made, 2 for self-made)" << std::endl;
    int answer;
    
    // makes sure for valid input
    while(true){
        std::cin >> answer;

        // checks for valid input
        if(std::cin.fail() || (answer != 1 && answer != 2)){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a 1 for pre-made or, 2 for self-made" << std::endl;
        }
        else{
            break;
        }
    }

    // creates a graph variable
    Graph *g;

    if(answer == 1){
        // creates the premade graph 
        g = new Graph(8);

        // adds the edges to the graph
        g->addEdge(0, 2, 2);
        g->addEdge(0, 3, 3);
        g->addEdge(0, 4, 4);
        g->addEdge(1, 5, 5);
        g->addEdge(1, 7, 1);
        g->addEdge(2, 3, 1);
        g->addEdge(2, 6, 2);
        g->addEdge(4, 7, 0);
        g->addEdge(5, 6, 0);
    }
    else{
        std::cout << "Please enter the number of vertices in the graph" << std::endl;
        // gets the size of the graph
        int n;
        
        // makes sure for valid input
        while(true){
            std::cin >> n;
    
            // checks for valid input
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Please enter a valid positive integer for the amount of vertices:" << std::endl;
            }
            else if(n <= 0){
                // the graph must have at least one vertex
                std::cout << "Please enter a valid positive integer for the amount of vertices:" << std::endl;
            }
            else{
                break;
            }
        }
    
        // creates a graph
        g = new Graph(n);
    }

    print_options();

    #ifdef DEBUG
    std::cout << "prints graph" << std::endl;
    g.print_graph();
    #endif

    // receives what the user wants to do
    int option;
    std::cin >> option;
    // run on a loop while the user does not want to end the program
    while(option != 9){
        // makes sure the user entered a valid option
        while(std::cin.fail() || option < 1 || option > 9){
            std::cin.clear(); // clear the fail state
            std::cin.ignore(1000, '\n'); // removes invalid input
            std::cout << "Please enter a valid option" << std::endl;
            std::cin >> option;
        }

        if(option != 9){
            // runs the option the user selected
            select_option(*g, option);

            // asks the user what they would like to do next
            print_options();
            std::cin >> option;
        }
    }

    // deletes the graph g
    delete g;

    std::cout << "Thank you for using this program" << std::endl;

    return 0;
}