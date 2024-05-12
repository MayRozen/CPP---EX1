/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "Graph.hpp"
#include "Algorithms.hpp"
enum Color { UNCOLORED, WHITE, BLACK };
using namespace ariel;
namespace Algorithms{

    static void dfs(Graph &g, IndexType v, std::vector<bool>& visited);
    static std::vector<int> dijkstra(const Graph& g, IndexType start, IndexType end);
    void printShortest(std::vector<int> shortest);

    bool isConnected(Graph &g){
        size_t size = g.getAdjMatrix().size();
        std::vector<bool> visited(size, false); // This array will tell us whether we run over all the vertices or not
            
        dfs(g, 0, visited); // Perform DFS traversal from the first vertex
        
        for (bool v : visited) { // Check if all vertices were visited
            if (!v) {
                std::cout<<"0"<<std::endl;
                return false; // Graph is not connected
            }
        }

        std::cout << "1" << std::endl;
        return true; // if 'false' were not return -> Graph is connected
    }

    std::vector<int> shortestPath(const Graph &g,IndexType start,IndexType end){
        std::vector<int> shortest; // First of all, our vector includes only one vertex -> start
        shortest.push_back(start);

        if (start == end) {
            printShortest(shortest);
            return shortest;
        }

        shortest = dijkstra(g, start, end);
        if (shortest.size()==1) {
            std::cout<<"-1"<<std::endl;
            shortest = {-1};
            return shortest; // If no path found between start and end, return -1
        }
        
        printShortest(shortest);
        return shortest;
    }

    int isContainsCycle(const Graph &g) {
        auto numVertices = g.getNumVertices();
        std::vector<int> dist(static_cast<IndexType>(numVertices), std::numeric_limits<int>::max());
        std::vector<int> prev(static_cast<IndexType>(numVertices), -1);

        int hasCycle = 0;

        // Relax all edges repeatedly
        for (IndexType i = 0; i < numVertices - 1; ++i) {
            for (IndexType u = 0; u < numVertices; ++u) {
                for (IndexType v = 0; v < numVertices; ++v) {
                    // Check if there is an edge
                    if (g.getAdjMatrix()[static_cast<IndexType>(u)][static_cast<IndexType>(v)] != 0) {
                        if (dist[static_cast<size_t>(u)] + g.getAdjMatrix()[u][v] < dist[static_cast<size_t>(v)]) {
                            dist[static_cast<size_t>(v)] = dist[u] + g.getAdjMatrix()[static_cast<size_t>(u)][static_cast<size_t>(v)];
                            prev[static_cast<IndexType>(v)] = static_cast<int>(u);
                        }
                    }
                }
            }
        }

        // Check for cycles
        for (IndexType u = 0; u < numVertices; ++u) {
            for (IndexType v = 0; v < numVertices; ++v) {
                // Check if there is an edge
                if (g.getAdjMatrix()[static_cast<IndexType>(u)][static_cast<IndexType>(v)] != 0) {
                    if (dist[u] + g.getAdjMatrix()[u][v] < dist[v]) {
                        // Cycle found
                        std::cout<<"The cycle is: ";
                        int vertex = v;
                        do {
                            std::cout << vertex << "->";
                            vertex = prev[static_cast<IndexType>(vertex)];
                        } while (vertex != v);
                        std::cout<<v<<std::endl;
                        hasCycle = 1;
                    }
                }
            }
        }

        if (!hasCycle) {
            std::cout<<"0"<<std::endl; //Print if no cycle found
        }
        
        return hasCycle; //Return whether a cycle is found
    }


    int isBipartite(const Graph &g){
        // If there is a cycle in the graph -> it can't be a bipartite graph
        if( isContainsCycle(g) != 0){
            std::cout<<"0"<<std::endl;
            return 0;
        }

        auto numVer = g.getNumVertices();
        std::vector<int> A, B; // Vertices of group A and group B
        std::queue<int> Q; // Queue for BFS traversal 
        std::vector<Color> colors(static_cast<std::vector<Color>::size_type>(numVer), UNCOLORED); // First of all, all the vertices are uncolored
        for (IndexType i = 0; i < numVer; ++i) { // Start BFS traversal from each uncolored vertex
            if (colors[static_cast<size_t>(i)] == UNCOLORED){ // Every vertice we pass on will be printed BLACK
                colors[static_cast<std::vector<Color>::size_type>(i)] = BLACK;
                A.push_back(i); // Add the first vertex to group A
                Q.push(i);
                
                while (!Q.empty()) {
                    IndexType curr = (IndexType)Q.front();
                    Q.pop();

                    for (IndexType neighbor = 0; neighbor < numVer; ++neighbor) {
                        if (g.getAdjMatrix()[curr][neighbor] == 1) {
                            if (colors[static_cast<size_t>(neighbor)] == UNCOLORED) {
                               colors[static_cast<size_t>(neighbor)] = (colors[curr] == BLACK) ? WHITE : BLACK; // Alternate between group A (black) and group B (white)
                                Q.push(neighbor);
                                if (colors[static_cast<size_t>(neighbor)] == BLACK){
                                    A.push_back(neighbor);
                                } else {
                                    B.push_back(neighbor);
                                }
                            } else if (colors[static_cast<size_t>(neighbor)] == colors[curr]) {
                                std::cout << "0" << std::endl;
                                return 0; // Graph is not bipartite
                            }
                        }
                    }
                }
            }
        }   
        std::cout << "The graph is bipartite: A={";
        for(IndexType i=0; i<A.size()-1; i++){
            std::cout << A[static_cast<size_t>(i)] << ", ";
        }
        std::cout << A[A.size()-1]<<"}, B={"; // The last vertex
        for(IndexType i=0; i<B.size()-1; i++){
            std::cout << B[static_cast<size_t>(i)];
        }
        std::cout << B[B.size()-1]<<"}."<<std::endl; // The last vertex
        return 1; // Graph is bipartite
    }

    std::vector<int> negativeCycle(const Graph &g){  
        // If there is no cycle in the graph -> there is no reason to continue. So print "0"
        if(isContainsCycle(g) == 0){
            std::cout<<"0"<<std::endl;
            return std::vector<int>(); // Return an empty vector if no negative cycle found
        }

        // Using Bellman-Ford algorithm to find the negative cycle
        int numVertices = g.getNumVertices();

        // Intialize the distance and π(v) of the starting vertex
        std::vector<int> dist(static_cast<size_t>(numVertices), std::numeric_limits<int>::max());
        // Initialize distances to infinity
        std::vector<int> prev(static_cast<size_t>(numVertices), -1); // Store predecessors

        // Relax all edges repeatedly
        for (IndexType i = 0; i < numVertices - 1; i++) {
            for (IndexType u = 0; u < numVertices; u++) {
                for (IndexType v = 0; v < numVertices; v++) {
                    if ((g[u][v] != 0) && (dist[u] + g[u][v] < dist[v])){ // Check if there is an edge
                            dist[v] = dist[u] + g[u][v];
                            prev[v] = u;
                    }
                        
                }
            }
        }

        // Check for negative cycles
        for (IndexType u = 0; u < numVertices; ++u) {
            for (IndexType v = 0; v < numVertices; ++v) {
                if (g.getAdjMatrix()[u][v] != 0) { // Check if there is an edge
                    if (dist[u] + g.getAdjMatrix()[u][v] < dist[v]) {
                        // Negative cycle found, construct the cycle and return it
                        std::vector<int> cycle;
                        IndexType vertex = v;
                        do {
                            cycle.push_back(vertex);
                            vertex = (IndexType)prev[vertex];
                        } while (vertex != v);

                        std::cout<<"The cycle is: "<<std::endl;
                        for(IndexType i=0; i<cycle.size()-1; i++){
                            std::cout<<cycle[i]<<"->"<<std::endl;
                        }
                        std::cout<<cycle[cycle.size()-1]<<std::endl;
                        return cycle;
                    }
                }
            }  
        } 

        std::cout<<"0"<<std::endl;
        return std::vector<int>(); // No negative cycle found
        
    }

    //---------------------------Here are all the auxiliary functions---------------------------

    // Depth-first search (DFS)
    static void dfs(Graph &g, IndexType v, std::vector<bool>& visited) {
        visited[v] = true; // Sign that we run over this vertice
        for (IndexType i = 0; i < g.getNumVertices(); i++) {
            if (g.getAdjMatrix()[v][i] && !visited[i]) { // Run over all tha existing paths from this vertex
                dfs(g, i, visited); // Recursion = depth
            }
        }
    }

    static std::vector<int> dijkstra(const Graph& g, IndexType start, IndexType end) {
        IndexType n = (IndexType)g.getNumVertices();
        std::vector<IndexType> dist(n, std::numeric_limits<int>::max()); // Initialize distances to infinity
        std::vector<IndexType> prev(n, std::numeric_limits<IndexType>::max()); // Store the previous vertex on the shortest path
        std::priority_queue<std::pair<int, int>,
                std::vector<std::pair<int, int>>,
                std::less<std::pair<int, int>>> pq;

        dist[start] = 0; // Distance from start vertex to itself is 0
        pq.push({0, start});

        while (!pq.empty()) {
            IndexType u = (IndexType)pq.top().second;
            pq.pop();

            for (IndexType v = 0; v < n; ++v) {
                if (g.getAdjMatrix()[u][v] && dist[u] != std::numeric_limits<int>::max()) {
                    IndexType newDist = dist[u] + (IndexType)g.getAdjMatrix()[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        prev[v] = u; // Update previous vertex
                        pq.push({dist[v], v});
                    }
                }
            }
            
            if (u == end) {
                break; // Stop once the shortest path to the end vertex is found
            }
        }

        // Reconstruct the shortest path
        std::vector<int> path;
        for (IndexType v = end; v !=std::numeric_limits<IndexType>::max(); v = (IndexType)prev[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());

        return path;
    }

    void printShortest(std::vector<int> shortest){
        for(IndexType i=0; i<shortest.size()-1; i++){
            std::cout<<shortest[i];
            std::cout<<"->";
        }
        std::cout<<shortest[shortest.size()-1]<<std::endl;
    }
    
};


