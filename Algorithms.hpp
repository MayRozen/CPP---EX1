/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Graph.hpp"

using namespace ariel;
namespace Algorithms{ // our namespace
    // return 1 if the graph is a 'connected graph' and 0 else
    static bool isConnected(Graph &g);

    // return the shortest path between 'start' ans 'end', else -> -1.
    static std::vector<int> shortestPath(const Graph &g,int start,int end);

    // Prints a circle if exist, 0 else
    static int isContainsCycle(const Graph &g);

    // return the partition of the graph in a bipartite graph. else -> print that there is no negative circle
    // 0 if fail, 1 if success.
    static int isBipartite(const Graph &g);

    // return a vector which include the Vertices of a negative circle if exist. If not -> return 0.
    static std::vector<int> negativeCycle(const Graph &g);
};
    
