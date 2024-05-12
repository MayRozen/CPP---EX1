/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Graph.hpp"

using namespace ariel;
namespace Algorithms{ // our namespace
    using IndexType = typename std::vector<int>::size_type; // Define a type alias for vector index type

    // return 1 if the graph is a 'connected graph' and 0 else
    bool isConnected(Graph &g);

    // return the shortest path between 'start' ans 'end', else -> -1.
    std::vector<int> shortestPath(const Graph &g,IndexType start,IndexType end);

    // Prints a circle if exist, 0 else
    int isContainsCycle(const Graph &g);

    // return the partition of the graph in a bipartite graph. else -> print that there is no negative circle
    // 0 if fail, 1 if success.
    int isBipartite(const Graph &g);

    // return a vector which include the Vertices of a negative circle if exist. If not -> return 0.
    std::vector<int> negativeCycle(const Graph &g);
};
    
