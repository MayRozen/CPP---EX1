/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph { // our namespace
private:
    int numVertices;
    std::vector<std::vector<int>> adjMatrix; // ~array[][]

public:
    Graph(int n); // constructor
    void loadGraph(const std::vector<std::vector<int>>& adjMat);
    void printGraph();
};

#endif // GRAPH_HPP
