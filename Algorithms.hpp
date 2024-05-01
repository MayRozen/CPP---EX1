/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Graph.hpp"

namespace ariel {
    class Algorithms{ // our namespace
    public:
        // return 1 if the graph is a 'connected graph' and 0 else
        bool isConnected(Graph g);

        // return the shortest path between 'start' ans 'end', else -> -1.
        std::vector<int> shortestPath(Graph g,int start,int end);

        // Prints a circle if exist, 0 else
        int isContainsCycle(Graph g);

        // return the partition of the graph in a bipartite graph. else -> print that there is no negative circle
        std::vector<int> isBipartite(Graph g);

        // return a vector which include the Vertices of a negative circle if exist. If not -> return 0.
        std::vector<int> negativeCycle(Graph g);
    };
}
