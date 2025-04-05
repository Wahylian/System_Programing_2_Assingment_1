#include "algorithm.hpp"
namespace graph{
    Graph Algorithms::bfs(const Graph &g, int s){
        // checks that s is a valid edge
        if(s < 0 || s>= g.numVertices())
            throw std::invalid_argument{"Vertex " + std::to_string(s) + " is not a legal vertex in the graph"};
    
        // assumes all edges in the graph have a weight of 1, and so it will ignore all weights
    
        // creates a list of edges for the bfs graph
        List<Edge> edges = List<Edge>();
    
        // creates a list for white vertices, gray vertices, and black vertices
        List<int> whites = List<int>();
        List<int> grays = List<int>();
        List<int> blacks = List<int>();
    
        // adds all vertices in g to the list of white vertices
        for(int i = 0; i < g.numVertices(); i++){
            whites.insert(i);
        }
    
        // removes the starting vertex from the list
        int v = whites.pop(s);
        // insert it into the grays list
        grays.insert(v);
    
        // while there are still gray vertices, run the algorithm
        while(!grays.isEmpty()){
            v = grays.pop(); // removes the first vertex in grays
            Vertex vx = g.getVertex(v); // gets vertex v
    
            List<Edge> vx_edges = vx.getEdges(); // get all the edges connected to vx
    
            // goes over each edge in vx 
            for(int i=0; i<vx_edges.size(); i++){
                // gets an edge from vx
                Edge e = vx_edges.getValue(i); 
                int v2 = e.getVertex2();
    
                // if the other vertex connected to the edge is white
                if(whites.isExists(v2)){
                    // remove it from the white list and add it to the grays
                    whites.remove(v2);
                    grays.insert(v2);
                    
                    // sets the edges weight to 1
                    e.setWeight(1);

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
        Graph newGraph = Graph(g.numVertices());
    
        // adds all the edges in edges
        for(int i=0; i<edges.size(); i++)
            newGraph.addEdge(edges.getValue(i));
    
        // returns the graph
        return newGraph;
    }
    
    Graph Algorithms::dfs(const Graph &g){
        // assumes all edges in the graph have a weight of 1, and so it will ignore all weights
    
        // creates a list of edges for the bfs graph
        List<Edge> edges = List<Edge>();
    
        // creates a list for white vertices, gray vertices, and black vertices
        List<int> whites = List<int>();
        List<int> grays = List<int>();
        List<int> blacks = List<int>();

        // adds all the vertices to whites
        for(int i=0; i<g.numVertices(); i++)
            whites.insert(i);
    
        // going over every white vertex in the graph
        while(!whites.isEmpty()){
            int v = whites.pop();
            dfsVisit(g, v, whites, grays, blacks, edges);
        }
    
        // after no vertices were left undiscovered
        // there is a list of all edges in the dfs graph
        // creates a new graph of size |g|
        Graph newGraph = Graph(g.numVertices());
        
        // adds all edges in edges to newGraph
        for(int i=0; i<edges.size(); i++)
            newGraph.addEdge(edges.getValue(i));
    
        // returns the new graph
        return newGraph;
    }
    
    void Algorithms::dfsVisit(const Graph& g, int v, List<int>& whites, List<int>& grays, List<int>& blacks, List<Edge>& edges){
        // checks v is a valid vertex, if not throw error
        if(v<0 || v>g.numVertices())
            throw std::invalid_argument{"vertex "+std::to_string(v)+" is not a legal vertex"};
    
        // adds vx to the list of gray vertices
        grays.insert(v);
    
        Vertex vx = g.getVertex(v); // gets the vertex from graph g
    
        List<Edge> vx_edges = vx.getEdges(); // get all the edges connected to vx
    
        // goes over each edge in vx 
        for(int i=0; i<vx_edges.size(); i++){
            // gets an edge from vx
            Edge e = vx_edges.getValue(i); 
            unsigned int v2 = e.getVertex2();
    
            // if v2 is white, remove it from the whites, and do a dfs visit using it
            if(whites.isExists(v2)){
                // remove v2 from the whites
                whites.remove(v2);
                
                // set's the edges weight to 1
                e.setWeight(1);

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

    Graph Algorithms::dijakstra(const Graph &g, int s){
        // checks that s is a valid vertex
        if(s < 0 || s >= g.numVertices())
            throw std::invalid_argument{"Vertex " + std::to_string(s) + " is not a legal vertex in the graph"};
        
        // creates a priority queue to place the vertices into with their distance being their key
        RevPriorityQueue<int> pQ = RevPriorityQueue<int>();
        
        // creates a list for the distances of each vertex and a list for their parent 
        List<int> d = List<int>();  // d[v] the distance of v from s
        List<int> pi = List<int>(); // pi[v] is the parent vertex of v

        // going over each vertex in g, to set up their default distance and parents
        for(int i=0; i<g.numVertices(); i++){
            d.insert(__INT32_MAX__); // insert the default value as INT_MAX32 which will act as infinity
            pi.insert(-1); // insert the default parent value as -1 which represents no parent

            // enqueues the vertex with the distance it has from s
            pQ.enqueue(i, d.getValue(i));
        }

        // sets the distance of s to 0
        d.pop(s);
        d.insert(0, s); // the distance of s from itself is 0
        
        // going over the queue while it is not empty
        while(!pQ.isEmpty()){
            int u = pQ.dequeue(); // gets the vertex with the lowest distance from s
            // gets the vertex u from g
            Vertex ux = g.getVertex(u);
            // gets all the edges of u
            List<Edge> u_edges = ux.getEdges();
            
            // going over each edge in u
            for(int i=0; i<u_edges.size(); i++){
                // gets an edge
                const Edge &e = u_edges.getValue(i);
                // if e has a negative weight, throws an error
                if(e.getWeight() < 0)
                    throw std::runtime_error{"negative weight found!"};
                
                // relaxes the edge
                relax(e, pi, d, pQ);
            }
        }

        // creates a new graph of size |g|
        Graph newGraph = Graph(g.numVertices());

        // going over every vertex in g
        for(int i=0; i<g.numVertices(); i++){
            // if the vertex is not s
            if(i != s){
                // if the vertex has a parent
                if(pi.getValue(i) != -1){
                    // gets the edge between i and pi[i] to the new graph
                    const Edge &e = g.getVertex(i).getEdge(pi.getValue(i));

                    // adds the edge to the new graph
                    newGraph.addEdge(e);
                }
            }
        }
        // returns the new graph
        return newGraph;
    }

    void Algorithms::relax(const Edge &e, List<int> &pi, List<int> &d, RevPriorityQueue<int> &q){
        // gets the vertices of e
        int u = e.getVertex1();
        int v = e.getVertex2();

        // checks if the edge the vertex hasn't converged already
        if(q.isEmpty() || !q.contains(v))
            return; // if the queue is empty or v is not in the queue, it means it has converged

        // calculates the possible new distance of v from s
        int newDistance = d.getValue(u) + e.getWeight(); 

        // checks if the distance of v from s is bigger than the distance of u from s + the weight of e
        if(d.getValue(v) > newDistance){
            // decreases the priority of v in the queue
            q.changePriority(v, newDistance);
            // changes the parent of v to u
            pi.pop(v);
            pi.insert(u, v);
            // changes the distance of v to the new distance
            d.pop(v);
            d.insert(newDistance);
        }
    }
    
    Graph Algorithms::prim(const Graph &g){
        // creates a priority queue
        RevPriorityQueue<int> q = RevPriorityQueue<int>();
    
        // creates a list pi in which pi[v] is the parent of vertex v in g
        List<int> pi = List<int>();
        // creates a list key holding the priorities of each vertex v in g
        List<int> key = List<int>();
        
        for(int i=0; i<g.numVertices(); i++){
            // sets the pi of each vertex v to -1 as a default value, representing it has no parent so far
            pi.insert(-1);
    
            // sets the key of each vertex v to INT32_MAX, as that is the default priority in q
            key.insert(__INT32_MAX__);
        }
        for(int i=0; i<g.numVertices(); i++)
            // inserts each vertex of g to q with the default priority
            q.enqueue(i);
    
        // sets the priority of vertex 0 in g to 0
        q.changePriority(0, 0);
        key.pop(0);
        key.insert(0, 0); // inserts priority 0 for vertex 0
    
        // while q is not empty
        while(!q.isEmpty()){
            // remove vertex v from q
            int v = q.dequeue();
            Vertex vx = g.getVertex(v);
    
            // get all the edges in vx
            List<Edge> vx_edges = vx.getEdges();
    
            // going over each adjacent vertex to v
            for(int i=0; i<vx_edges.size(); i++){ 
                // gets an adjacent vertex to v
                Edge e = vx_edges.getValue(i);
                int u = e.getVertex2();
    
                // check if q contains u
                if(q.contains(u)){
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
        for(int i=1; i<g.numVertices(); i++){
            
            Vertex vx = g.getVertex(i);
            // gets the edge bewteen i and pi[i]
            if(vx.isEdgeExists(pi.getValue(i))){
                Edge e = vx.getEdge(pi.getValue(i));
    
                // adds the edge to newEdges
                newEdges.insert(e);
            }
        }
    
        // creates a new graph
        Graph newGraph = Graph(g.numVertices());
    
        // adds the edges to the graph
        for(int i=0; i<newEdges.size(); i++)
            newGraph.addEdge(newEdges.getValue(i));
        
        // returns the new Graph
        return newGraph;
    }
    
    Graph Algorithms::kruskal(const Graph &g){
        // get all edges of g
        List<Edge> edges = g.getEdges();
    
        // places the edges in a reverse priority queue
        RevPriorityQueue<Edge> q = RevPriorityQueue<Edge>();
        for(int i=0; i<edges.size(); i++){
            Edge e = edges.getValue(i);
            // inserts e to q with it's weight as its priority
            q.enqueue(e, e.getWeight());
        }
    
        // creates a unionfind for the vertices in g
        UnionFind uf = UnionFind(g.numVertices());
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
        Graph newGraph = Graph(g.numVertices());
        // adds the new edges to newGraph
        for(int i=0; i<newEdges.size(); i++)
            newGraph.addEdge(newEdges.getValue(i));
        
        return newGraph;
    }
}
