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

namespace ariel {
class Algorithms{
public:
    int isConnected(Graph g){
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

    std::vector<int> shortestPath(Graph g,int start,int end){
        std::vector<int> shortest; // First of all, our vector includes only one vertex -> start
        shortest.push_back(start);

        if (start == end) {
            return shortest;
        }

        shortest = dijkstra(g, start, end);

        return std::vector<int>{-1}; // If no path found between start and end, return -1
    }

    void isContainsCycle(Graph g){
        int numVertices = g.getNumVertices();
        std::vector<int> dist(numVertices, std::numeric_limits<int>::max()); // Initialize distances to infinity
        std::vector<int> prev(numVertices, -1);   // Store predecessors

        // Relax all edges repeatedly
        for (int i = 0; i < numVertices - 1; ++i) {
            for (int u = 0; u < numVertices; ++u) {
                for (int v = 0; v < numVertices; ++v) {
                    if (g.getAdjMatrix()[u][v] != 0) { // Check if there is an edge
                        if (dist[u] + g.getAdjMatrix()[u][v] < dist[v]) {
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
                        print = 1; // There is a negative cycle
                    }
                }
            }
        }
        if(print == 0){
            std::cout<<"0"<<std::endl; // No negative cycle found
        }
    }

// Here are all the auxiliary functions
private: 
    // Depth-first search (DFS)
    void dfs(Graph g, int v, std::vector<bool>& visited) {
        visited[v] = true; // Sign that we run over this vertice
        for (int i = 0; i < v; i++) {
            if (g.getAdjMatrix()[v][i] && !visited[i]) { // Run over all tha existing paths from this vertex
                dfs(g, i, visited); // Recursion = depth
            }
        }
    }

    std::vector<int> dijkstra(const Graph& g, int start, int end) {
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
            
            if (u == end) break; // Stop once the shortest path to the end vertex is found
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
}
