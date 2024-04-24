/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Graph.hpp"
#include "Algorithms.hpp"

namespace Algorithems{
    public:
        int isConnected(Graph g){
            int numVertices = g.adjMatrix.size();
            std::vector<bool> visited(numVertices, false);
            
            // Perform DFS traversal from the first vertex
            dfs(0, visited);

            // Check if all vertices were visited
            for (bool v : visited) {
                if (!v) {
                    return false; // Graph is not connected
                }
            }
            return true; // if 'false' were not return -> Graph is connected
        }

    private:
        // Depth-first search (DFS)
        void dfs(int v, std::vector<bool>& visited) {
            visited[v] = true;
            for (int i = 0; i < g.adjMatrix[v].size(); ++i) {
                if (adjMatrix[v][i] && !visited[i]) {
                    dfs(i, visited);
                }
            }
        }
}





