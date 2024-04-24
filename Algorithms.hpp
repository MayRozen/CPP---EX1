/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <vector>

class Algorithms{ // our namespace
    public:

    // return 1 if the graph is a 'connected graph' and 0 else
    int isConnected(Graph g);

    // return the shortest path between 'start' ans 'end', else -> -1.
    vector<int> shortestPath(Graph g,int start,int end);

    // Prints a circle if exist
    void isContainsCycle(Graph g);


    isBipartite(Graph g);

    // return a vector which include the Vertices of a negative circle if exist. If not -> return 0.
    vector<int> negativeCycle(Graph g);
}


