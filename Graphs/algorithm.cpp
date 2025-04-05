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
        #define DEBUG_Dijakstra
        #ifdef DEBUG_Dijakstra
        std::cout << "start vertex: " << s <<std::endl;
        std::cout << "size of graph: " << g.numVertices()<< std::endl;
        std::cout << (s < 0 || s>= g.numVertices()) <<std::endl;
        #endif

        // checks that s is a valid vertex
        if(s < 0 || s>= g.numVertices())
            throw std::invalid_argument{"Vertex " + std::to_string(s) + " is not a legal vertex in the graph"};
    
        // we will create 2 lists of size |g|:
        // pi, and d
        // for vertex v in g, pi[v] will be the vertex u that comes before u on the shortest path found so far from s to u
        // for vertex v in g, d[v] will be the shortest distance found so far from s to u 
        List<int> pi = List<int>();
        List<int> d = List<int>();
        
        #ifdef DEBUG_Dijakstra
        std::cout<< "created the 2 lists"<<std::endl;
        #endif

        // setting up pi and d with default values
        for(int i=0; i<g.numVertices(); i++){
            pi.insert(-1); // -1 will signify that there is no path from s to u
            d.insert(__INT32_MAX__); // int32 max will signify that the distance from s to u is infinite
        }
        
        #ifdef DEBUG_Dijakstra
        std::cout<<"set base values for pi and d" <<std::endl;
        #endif

        // s's distance from itself is 0, but it's pi is -1 as it has no parents
        d.pop(s); // removes the distance at index s
        d.insert(0, s); // insert distance 0 at index s
        
        #ifdef DEBUG_Dijakstra
        std::cout<<"set s with a distance of 0, and reinserted it" <<std::endl;
        #endif

        // creating a priority queue of all vertices in g, with their priority being based on their distance from s
        RevPriorityQueue<int> q = RevPriorityQueue<int>();
        for(int i=0; i < g.numVertices(); i++){
            int priority = d.getValue(i); // gets the priority of vertex i
            
            #ifdef DEBUG_Dijakstra
            std::cout<<"enqueueing vertex "<< i << "with priority "<< priority <<std::endl;
            #endif

            // enqueues each vertex with the distance it has from s
            q.enqueue(i, priority);
        }

        #ifdef DEBUG_Dijakstra
        std::cout<< "size of queue"<<q.size()<<std::endl;
        
        #endif
        #ifdef DEBUG_Dijakstra
        std::cout<<"entering loop" <<std::endl;
        #endif

        #ifdef DEBUG_Dijakstra
        std::cout<<"check if the queue is empty"<< q.isEmpty() <<std::endl;
        #endif

        while(!q.isEmpty()){
            #ifdef DEBUG_Dijakstra
            std::cout<<2<<std::endl;
            break;
            #endif
        }

        // as long as the queue is not empty, go over it
        while(!q.isEmpty()){
            #ifdef DEBUG_Dijakstra
            std::cout<<"attempt to dequeue:" <<std::endl;
            #endif


            // removes the closest vertex to s in the queue
            int u = q.dequeue();

            #ifdef DEBUG_Dijakstra
            std::cout << "next vertex out is: "<< u<<std::endl;

            #endif
    
            // get's all of u's edges in g
            Vertex vx = g.getVertex(u);
            List<Edge> u_edges = vx.getEdges();

            #ifdef DEBUG_Dijakstra
            std::cout << "got the edges of vx"<<std::endl;
            #endif
    
            // relaxes all edges going out of u
            for(int i=0; i<u_edges.size(); i++){
                // gets an edge from u
                Edge& e = u_edges.getValue(i); 
                
                #ifdef DEBUG_Dijakstra
                std::cout << "got edge from v: "<< e.to_string() <<std::endl;
                #endif

                // if e has a negative value, throw an error, as dijakstra does not allow negative weights
                if(e.getWeight()<0){
                    #ifdef DEBUG_Dijakstra
                    std::cout << "found a problematic edge: "<< e.to_string() << std::endl;
                    #endif
                    throw std::runtime_error{"negative weight found!"};
                }
    
                // relaxes edge e
                relax(e, pi, d, q);
                #ifdef DEBUG_Dijakstra
                std::cout<<"after e got relaxed"<<std::endl;
                std::cout<<"d(v) = "<<d.getValue(e.getVertex2())<<std::endl;
                std::cout<<"w(e) = "<<e.getWeight()<<std::endl;
                std::cout<<"d(u) = "<<d.getValue(e.getVertex1())<<std::endl;

                std::cout<<"pi(v) = "<<pi.getValue(e.getVertex2())<<std::endl;
                #endif
            }
        }
        #ifdef DEBUG_Dijakstra
        std::cout<<"test"<<3<<std::endl;
        #endif
        
        // after finishing going over all the vertices in g
        // creates a new graph
        Graph newGraph = Graph(g.numVertices());
    
        // for each vertex v in the original g (as long as it's not s), adds the edge between v and pi[v] to newGraph
        for(int i=0; i<g.numVertices(); i++){
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
    
    void Algorithms::relax(Edge& e, List<int>& pi, List<int>& d, RevPriorityQueue<int>& q){
        // gets the 2 vertices comprising e
        int u = e.getVertex1();
        int v = e.getVertex2();

        #ifdef DEBUG_Dijakstra
        std::cout<<"u: "<< u << " v: "<< v <<std::endl;
        std::cout<<"attempting to relax"<<std::endl;
        #endif
    
        // if the distance from v to s is bigger than the distance from u to s + the weight of e
        // relaxes e
        if(d.getValue(v) > d.getValue(u) + e.getWeight()){

            #ifdef DEBUG_Dijakstra
            std::cout<<"requires relaxation"<<std::endl;
            std::cout<<"d(v) = "<<d.getValue(v)<<std::endl;
            std::cout<<"w(e) = "<<e.getWeight()<<std::endl;
            std::cout<<"d(u) = "<<d.getValue(u)<<std::endl;
            #endif
            // change the distance of v 
            d.remove(v); // removes the old distance of v

            // gets the distance of vertex u from the s
            int d_u = d.getValue(u);
            d.insert(d_u + e.getWeight(), v); // inserts the new distance of v in the correct index
            
            #ifdef DEBUG_Dijakstra
            std::cout<<"relaxed e"<<std::endl;
            std::cout<<"d(v) = "<<d.getValue(v)<<std::endl;
            std::cout<<"w(e) = "<<e.getWeight()<<std::endl;
            std::cout<<"d(u) = "<<d.getValue(u)<<std::endl;

            std::cout<<"pi(v) = "<<pi.getValue(v)<<std::endl;
            #endif

            // changes the pi of v
            pi.remove(v); // removes the old pi of v
            pi.insert(u, v); // inserts u as the new pi of v
            
            #ifdef DEBUG_Dijakstra
            std::cout<<"pi(v) changed to"<<std::endl;
            std::cout<<"pi(v) = "<<pi.getValue(v)<<std::endl;
            std::cout<<"change's v's priority to =" << d.getValue(v)<<std::endl;

            std::cout<<"isqueue empty? "<<q.isEmpty()<<std::endl;

            #endif
            // decrease the priority of v to it's new distance
            q.changePriority(v, d.getValue(v));

            #ifdef DEBUG_Dijakstra
            std::cout<<"test"<<std::endl;
            #endif
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
