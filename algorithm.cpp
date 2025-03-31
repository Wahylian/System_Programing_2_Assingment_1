#include "algorithm.hpp"

Graph Algorithms::bfs(Graph g, unsigned int s){
    // assumes all edges in the graph have a weight of 1, and so it will ignore all weights

    // creates a list of edges for the bfs graph
    List<Edge> edges = List<Edge>();

    // creates a list for white vertices, gray vertices, and black vertices
    List<unsigned int> whites = List<unsigned int>();
    List<unsigned int> grays = List<unsigned int>();
    List<unsigned int> blacks = List<unsigned int>();

    // adds all vertices in g to the list of white vertices
    for(int i = 0; i < g.getSize(); i++){
        whites.insert(i);
    }

    // removes the starting vertex from the list
    unsigned int v = whites.pop(s);
    // insert it into the grays list
    grays.insert(v);

    // while there are still gray vertices, run the algorithm
    while(!grays.isEmpty()){
        v = grays.pop(); // removes the first vertex in grays
        Vertex vx = g.getVertex(v); // gets vertex v

        List<Edge> vx_edges = vx.getEdges(); // get all the edges connected to vx

        // goes over each edge in vx 
        for(int i=0; i<vx_edges.getSize(); i++){
            // gets an edge from vx
            Edge e = vx_edges.getValue(i); 
            unsigned int v2 = e.getVertex2();

            // if the other vertex connected to the edge is white
            if(whites.isExists(v2)){
                // remove it from the white list and add it to the grays
                whites.remove(v2);
                grays.insert(v2);

                // and adds the edge to the list of edges in the bfs graph
                edges.insert(e);
            }
        }
        // once all the edges of vx were accounted for
        // adds v to the blacks list
        blacks.insert(v);
    }

    // after going over all the vertices reachable from s
    // creates a bfs graph from the edges the vertices in the blacks

    // creates a graph with the same amounts of vertices as g
    Graph newGraph = Graph(g.getSize());

    // adds all the edges in edges
    for(int i=0; i<edges.getSize(); i++)
        newGraph.addEdge(edges.getValue(i));

    // returns the graph
    return newGraph;
}

Graph Algorithms::dfs(Graph g){
    // assumes all edges in the graph have a weight of 1, and so it will ignore all weights

    // creates a list of edges for the bfs graph
    List<Edge> edges = List<Edge>();

    // creates a list for white vertices, gray vertices, and black vertices
    List<unsigned int> whites = List<unsigned int>();
    List<unsigned int> grays = List<unsigned int>();
    List<unsigned int> blacks = List<unsigned int>();

    // going over every white vertex in the graph
    while(!whites.isEmpty()){
        unsigned int v = whites.pop();
        dfsVisit(g, v, whites, grays, blacks, edges);
    }

    // after no vertices were left undiscovered
    // there is a list of all edges in the dfs graph
    // creates a new graph of size |g|
    Graph newGraph = Graph(g.getSize());
    
    // adds all edges in edges to newGraph
    for(int i=0; i<edges.getSize(); i++)
        newGraph.addEdge(edges.getValue(i));

    // returns the new graph
    return newGraph;
}

void Algorithms::dfsVisit(Graph& g, unsigned int v, List<unsigned int>& whites, List<unsigned int>& grays, List<unsigned int>& blacks, List<Edge>& edges){
    // adds vx to the list of gray vertices
    grays.insert(v);

    Vertex vx = g.getVertex(v); // gets the vertex from graph g

    List<Edge> vx_edges = vx.getEdges(); // get all the edges connected to vx

    // goes over each edge in vx 
    for(int i=0; i<vx_edges.getSize(); i++){
        // gets an edge from vx
        Edge e = vx_edges.getValue(i); 
        unsigned int v2 = e.getVertex2();

        // if v2 is white, remove it from the whites, and do a dfs visit using it
        if(whites.isExists(v2)){
            // remove v2 from the whites
            whites.remove(v2);

            // and then add edge e to edges
            edges.insert(e);

            // dfs visits using v2
            dfsVisit(g, v2, whites, grays, blacks, edges);
        }
    }
    // after finishing to go over all of v's edges, removes it from the grays and puts it in the blacks
    grays.remove(v);
    blacks.insert(v);
}

Graph Algorithms::dijakstra(Graph g, unsigned int s){
    // we will create 2 lists of size |g|:
    // pi, and d
    // for vertex v in g, pi[v] will be the vertex u that comes before u on the shortest path found so far from s to u
    // for vertex v in g, d[v] will be the shortest distance found so far from s to u 
    List<int> pi = List<int>();
    List<unsigned int> d = List<unsigned int>();
    

    // setting up pi and d with default values
    for(int i=0; i<g.getSize(); i++){
        pi.insert(-1); // -1 will signify that there is no path from s to u
        d.insert(__INT32_MAX__); // int32 max will signify that the distance from s to u is infinite
    }

    // s's distance from itself is 0, but it's pi is -1 as it has no parents
    d.pop(s); // removes the distance at index s
    d.insert(0, s); // insert distance 0 at index s

    // creating a priority queue of all vertices in g, with their priority being based on their distance from s
    RevPriorityQueue<unsigned int> q = RevPriorityQueue<unsigned int>();
    for(int i=0; i < g.getSize(); i++){
        // enqueues each vertex with the distance it has from s
        q.enqueue(i, d.getValue(i));
    }

    // as long as the queue is not empty, go over it
    while(!q.isEmpty()){
        // removes the closest vertex to s in the queue
        unsigned int u = q.dequeue();

        // get's all of u's edges in g
        Vertex vx = g.getVertex(u);
        List<Edge> u_edges = vx.getEdges();

        // relaxes all edges going out of u
        for(int i=0; i<u_edges.getSize(); i++){
            // gets an edge from u
            Edge& e = u_edges.getValue(i); 
            
            // if e has a negative value, throw an error, as dijakstra does not allow negative weights
            if(e.getWeight()<0){
                throw std::invalid_argument{"negative weight found!"};
            }

            // relaxes edge e
            relax(e, pi, d, q);
        }
    }

    // after finishing going over all the vertices in g
    // creates a new graph
    Graph newGraph = Graph(g.getSize());

    // for each vertex v in the original g (as long as it's not s), adds the edge between v and pi[v] to newGraph
    for(int i=0; i<g.getSize(); i++){
        // if s does not have a pi, and so it will be excluded
        if(i != s){
            // gets a vertex from g
            Vertex vx = g.getVertex(i);

            // get's the pi of i
            int pi_vx = pi.getValue(i);

            // adds the edge between vx and pi_vx
            newGraph.addEdge(vx.getEdge(Vertex(pi_vx)));
        }
    }

    // returns the new graph
    return newGraph;
}

void Algorithms::relax(Edge& e, List<int>& pi, List<unsigned int>& d, RevPriorityQueue<unsigned int>& q){
    // gets the 2 vertices comprising e
    unsigned int u = e.getVertex1();
    unsigned int v = e.getVertex2();

    // if the distance from v to s is bigger than the distance from u to s + the weight of e
    // relaxes e
    if(d.getValue(v) > d.getValue(u) + e.getWeight()){
        // change the distance of v 
        d.remove(v); // removes the old distance of v
        d.insert(d.getValue(u) + e.getWeight(), v); // inserts the new distance of v in the correct index

        // changes the pi of v
        pi.remove(v); // removes the old pi of v
        pi.insert(u, v); // inserts u as the new pi of v

        // decrease the priority of v to it's new distance
        q.changePriority(v, d.getValue(v));
    }
}

Graph Algorithms::prim(Graph g){
    // creates a priority queue
    RevPriorityQueue<unsigned int> q = RevPriorityQueue<unsigned int>();

    // creates a list pi in which pi[v] is the parent of vertex v in g
    List<unsigned int> pi = List<unsigned int>();
    // creates a list key holding the priorities of each vertex v in g
    List<int> key = List<int>();
    
    for(int i=0; i<g.getSize(); i++){
        // sets the pi of each vertex v to -1 as a default value, representing it has no parent so far
        pi.insert(-1);

        // sets the key of each vertex v to INT32_MAX, as that is the default priority in q
        key.insert(__INT32_MAX__);
    }
    for(int i=0; i<g.getSize(); i++)
        // inserts each vertex of g to q with the default priority
        q.enqueue(i);

    // sets the priority of vertex 0 in g to 0
    q.changePriority(0, 0);
    key.pop(0);
    key.insert(0, 0); // inserts priority 0 for vertex 0

    // while q is not empty
    while(!q.isEmpty()){
        // remove vertex v from q
        unsigned int v = q.dequeue();
        Vertex vx = g.getVertex(v);

        // get all the edges in vx
        List<Edge> vx_edges = vx.getEdges();

        // going over each adjacent vertex to v
        for(int i=0; i<vx_edges.getSize(); i++){ 
            // gets an adjacent vertex to v
            Edge e = vx_edges.getValue(i);
            unsigned int u = e.getVertex2();

            // check if q contains u
            if(q.isIn(u)){
                // checks if the weight of e is smaller than the key of u
                if(e.getWeight() < key.getValue(u)){
                    // if it is, changes the parent of u to v
                    pi.remove(u);
                    pi.insert(v, u); // sets the parent of u to v
                    // and sets the priority of u to the weight of e
                    key.pop(u);
                    key.insert(e.getWeight(), u);
                    q.changePriority(u, e.getWeight()); // changes it in the queue as well
                }
            }
        }
    }
    
    // the edges of the MST will be the edges from each v to pi[v]
    List<Edge> newEdges = List<Edge>();

    // since i = 0 is the starting point, it has no pi and so it is skipped
    for(int i=1; i<g.getSize(); i++){
        
        Vertex vx = g.getVertex(i);
        // gets the edge bewteen i and pi[i]
        if(vx.isEdgeExists(pi.getValue(i))){
            Edge e = vx.getEdge(pi.getValue(i));

            // adds the edge to newEdges
            newEdges.insert(e);
        }
    }

    // creates a new graph
    Graph newGraph = Graph(g.getSize());

    // adds the edges to the graph
    for(int i=0; i<newEdges.getSize(); i++)
        newGraph.addEdge(newEdges.getValue(i));
    
    // returns the new Graph
    return newGraph;
}

Graph Algorithms::kruskal(Graph g){
    // get all edges of g
    List<Edge> edges = g.getEdges();

    // places the edges in a reverse priority queue
    RevPriorityQueue<Edge> q = RevPriorityQueue<Edge>();
    for(int i=0; i<edges.getSize(); i++){
        Edge e = edges.getValue(i);
        // inserts e to q with it's weight as its priority
        q.enqueue(e, e.getWeight());
    }

    // creates a unionfind for the vertices in g
    UnionFind uf = UnionFind(g.getSize());
    // creates a list to store the edges in the MST
    List<Edge> newEdges = List<Edge>();

    // for each vertex (v,w) in q, if v and w do not belong in the same component, 
    // create a union between them, and add (v,w) to newEdges
    while(!q.isEmpty()){
        // removes the top value from q
        Edge e = q.dequeue();

        // gets the vertices of e
        unsigned int v1 = e.getVertex1();
        unsigned int v2 = e.getVertex2();

        // if v1 and v2 do not belong to the same set in uf
        // connects their sets
        if(uf.Find(v1) != uf.Find(v2)){
            uf.Union(v1, v2);
            // adds e to newEdges
            newEdges.insert(e);
        }
    }

    // creates a new Graph
    Graph newGraph = Graph(g.getSize());
    // adds the new edges to newGraph
    for(int i=0; i<newEdges.getSize(); i++)
        newGraph.addEdge(newEdges.getValue(i));
    
    return newGraph;
}