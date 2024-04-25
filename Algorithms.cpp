/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Graph.hpp"
#include "Algorithms.hpp"

class Algorithems{
public:
    int isConnected(Graph g){
        int size = g.getAdjMatrix().size();
        std::vector<bool> visited(size, false); // This array will tell us whether we run over all the vertices or not
            
        // Perform DFS traversal from the first vertex
        dfs(g, 0, visited);

        // Check if all vertices were visited
        for (bool v : visited) {
            if (!v) {
                return false; // Graph is not connected
            }
        }
        return true; // if 'false' were not return -> Graph is connected
    }

    std::vector<int> shortestPath(Graph g,int start,int end){
        
    }

private:
    // Depth-first search (DFS)
    void dfs(Graph g, int v, std::vector<bool>& visited) {
        visited[v] = true; // Sign that we run over this vertice
        for (int i = 0; i < g.getAdjMatrix()[v].size(); i++) {
            if (g.getAdjMatrix()[v][i] && !visited[i]) { // Run over all tha existing paths from this vertex
                dfs(g, i, visited); // Recursion = depth
            }
        }
    }
};
