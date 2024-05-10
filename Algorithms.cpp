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


static void dfs(Graph &g, int v, std::vector<bool>& visited);
static std::vector<int> dijkstra(const Graph& g, int start, int end);
namespace Algorithms{
    static bool isConnected(Graph &g){
        int size = g.getAdjMatrix().size();
        std::vector<bool> visited(size, false); // This array will tell us whether we run over all the vertices or not
            
        dfs(g, 0, visited); // Perform DFS traversal from the first vertex
        
        for (bool v : visited) { // Check if all vertices were visited
            if (!v) {
                return false; // Graph is not connected
            }
        }

        return true; // if 'false' were not return -> Graph is connected
    }

    static std::vector<int> shortestPath(const Graph &g,int start,int end){
        std::vector<int> shortest; // First of all, our vector includes only one vertex -> start
        shortest.push_back(start);

        if (start == end) {
            return shortest;
        }

        shortest = dijkstra(g, start, end);

        return std::vector<int>{-1}; // If no path found between start and end, return -1
    }

    static int isContainsCycle(const Graph &g){
        int numVertices = g.getNumVertices();
        std::vector<int> dist(numVertices, std::numeric_limits<int>::max()); // Initialize distances to infinity
        std::vector<int> prev(numVertices, -1);   // Store predecessors

        // Relax all edges repeatedly
        for (int i = 0; i < numVertices - 1; ++i){
            for (int u = 0; u < numVertices; ++u){
                for (int v = 0; v < numVertices; ++v){
                    if (g.getAdjMatrix()[u][v] != 0){ // Check if there is an edge
                        if (dist[u] + g.getAdjMatrix()[u][v] < dist[v]){
                            dist[v] = dist[u] + g.getAdjMatrix()[u][v];
                            prev[v] = u;
                        }
                    }
                }
            }
        }

        int print = 0;
        // Check for negative cycles
        for (int u = 0; u < numVertices; ++u) {
            for (int v = 0; v < numVertices; ++v) {
                if (g.getAdjMatrix()[u][v] != 0) { // Check if there is an edge
                    if (dist[u] + g.getAdjMatrix()[u][v] < dist[v]) {
                        // Negative cycle found, print it
                        std::cout << "Negative cycle found: ";
                        int vertex = v;
                        for (int i = 0; i < numVertices; ++i) {
                            vertex = prev[vertex];
                        }
                        int startVertex = vertex;
                        do {
                            std::cout << vertex << " ";
                            vertex = prev[vertex];
                        } while (vertex != startVertex);
                        std::cout << startVertex << std::endl;
                        return;
                    }
                }
            }
        }
        if(print == 0){
            std::cout<<"There is no negative cycle"<<std::endl; // No negative cycle found
            return 0;
        }
    }

    static int isBipartite(const Graph &g){
        // If there is a cycle in the graph -> it can't be a bipartite graph
        if( isContainsCycle(g) != 0){
            std::cout<<"0"<<std::endl;
            return 0;
        }

        int numVer = g.getNumVertices();
        std::vector<int> A, B; // Vertices of group A and group B
        std::queue<int> Q; // Queue for BFS traversal 
        std::vector<Color> colors(numVer, UNCOLORED); // First of all, all the vertices are uncolored
        for (int i = 0; i < numVer; ++i) { // Start BFS traversal from each uncolored vertex
            if (colors[i] == UNCOLORED) { // Every vertice we pass on will be printed BLACK
                colors[i] = BLACK;
                A.push_back(i); // Add the first vertex to group A
                Q.push(i);
                
                while (!Q.empty()) {
                    int curr = Q.front();
                    Q.pop();

                    for (int neighbor = 0; neighbor < numVer; ++neighbor) {
                        if (g.getAdjMatrix()[curr][neighbor] == 1) {
                            if (colors[neighbor] == UNCOLORED) {
                                colors[neighbor] = (colors[curr] == BLACK) ? WHITE : BLACK; // Alternate between group A (black) and group B (white)
                                Q.push(neighbor);
                                if (colors[neighbor] == BLACK) {
                                    A.push_back(neighbor);
                                } else {
                                    B.push_back(neighbor);
                                }
                            } else if (colors[neighbor] == colors[curr]) {
                                std::cout << "0" << std::endl;
                                return 0; // Graph is not bipartite
                            }
                        }
                    }
                }
            }
        }   
        std::cout << "The graph is bipartite: A={";
        for(int i=0; i<A.size()-1; i++){
            std::cout << A[i]<<", ";
        }
        std::cout << A[A.size()-1]<<"}, B={"; // The last vertex
        for(int i=0; i<B.size(); i++){
            std::cout << B[i];
        }
        std::cout << B[B.size()-1]<<"}."<<std::endl; // The last vertex
        return 1; // Graph is bipartite
    }

    static std::vector<int> negativeCycle(const Graph &g){  
        // If there is no cycle in the graph -> there is no reason to continue. So print "0"
        if( isContainsCycle(g) == 0){
            std::cout<<"0"<<std::endl;
            return std::vector<int>(); // Return an empty vector if no negative cycle found
        }

        // Using Bellman-Ford algorithm to find the negative cycle
        int numVertices = g.getNumVertices();

        // Intialize the distance and π(v) of the starting vertex
        std::vector<int> dist(numVertices, std::numeric_limits<int>::max()); // Initialize distances to infinity
        std::vector<int> prev(numVertices, -1);   // Store predecessors

        // Relax all edges repeatedly
        for (int i = 0; i < numVertices - 1; i++) {
            for (int u = 0; u < numVertices; u++) {
                for (int v = 0; v < numVertices; v++) {
                    if ((g.getAdjMatrix()[u][v] != 0)&&(dist[u] + g.getAdjMatrix()[u][v] < dist[v])) { // Check if there is an edge
                            dist[v] = dist[u] + g.getAdjMatrix()[u][v];
                            prev[v] = u;
                    }
                        
                }
            }
        }

        // Check for negative cycles
        for (int u = 0; u < numVertices; ++u) {
            for (int v = 0; v < numVertices; ++v) {
                if (g.getAdjMatrix()[u][v] != 0) { // Check if there is an edge
                    if (dist[u] + g.getAdjMatrix()[u][v] < dist[v]) {
                        // Negative cycle found, construct the cycle and return it
                        std::vector<int> cycle;
                        int vertex = v;
                        do {
                            cycle.push_back(vertex);
                            vertex = prev[vertex];
                        } while (vertex != v);

                        std::cout<<"The cycle is: "<<std::endl;
                        for(int i=0; i<cycle.size()-1; i++){
                            std::cout<<cycle[i]<<"->"<<std::endl;
                        }
                        std::cout<<cycle[cycle.size()+1]<<std::endl;
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
    static void dfs(Graph &g, int v, std::vector<bool>& visited) {
        visited[v] = true; // Sign that we run over this vertice
        for (int i = 0; i < v; i++) {
            if (g.getAdjMatrix()[v][i] && !visited[i]) { // Run over all tha existing paths from this vertex
                dfs(g, i, visited); // Recursion = depth
            }
        }
    }

    static std::vector<int> dijkstra(const Graph& g, int start, int end) {
        int n = g.getNumVertices();
        std::vector<int> dist(n, std::numeric_limits<int>::max()); // Initialize distances to infinity
        std::vector<int> prev(n, -1); // Store the previous vertex on the shortest path
        std::priority_queue<std::pair<int, int>,
                std::vector<std::pair<int, int>>,
                std::less<std::pair<int, int>>> pq;

        dist[start] = 0; // Distance from start vertex to itself is 0
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < n; ++v) {
                if (g.getAdjMatrix()[u][v] && dist[u] != std::numeric_limits<int>::max()) {
                    int newDist = dist[u] + g.getAdjMatrix()[u][v];
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
        for (int v = end; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());

        return path;
    }
    
};


