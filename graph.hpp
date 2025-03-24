using namespace std;


// a class representing a graph
class Graph{
    private:
    int n; // the amount of vertices in the graph

    public:

    // construction function
    Graph(unsigned int num_vx);
    // destruction function
    ~Graph();

    // base functions:

    // adds an edge between v and u of the provided weight
    void addEdge(unsigned int v, unsigned int u, unsigned int weight=1);
    // removes an edge between v and u, throws an error if there is no edge between them
    void removeEdge(unsigned int v, unsigned int u);

    // prints the graph (the neighbourhood matrix of the graph)
    void print_graph();
};

// throwing a none_existant_vertex object in case a user attempts to add an edge to a none existant vertex
class none_existant_vertex{};

// throwsing a none_existant_edge object in case the user attempts to remove an edge that does'nt exist
class none_existant_edge{};