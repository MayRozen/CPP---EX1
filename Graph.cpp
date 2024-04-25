/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <iostream>
#include <vector>
#include "Graph.hpp"
using namespace ariel;

Graph::Graph(int n) : numVertices(n) {
    adjMatrix.resize(n, std::vector<int>(n, 0));
}

// getter to numVertices
int Graph::getNumVertices() const{
    return numVertices;
}

// getter to adjMatrix
std::vector<std::vector<int>> Graph::getAdjMatrix() const{
    return adjMatrix;
}

void Graph::loadGraph(const std::vector<std::vector<int>>& adjMat) {
    if (adjMat.size() != numVertices || adjMat[0].size() != numVertices) {
        std::cout << "Error: Incorrect matrix." << std::endl;
        return;
    }

    adjMatrix = adjMat;
}

void Graph::printGraph() {
    int edges = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if(adjMatrix[i][j]!=0){ // Assuming the lack of an edge is expressed by 0
                edges++;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Graph with "<<numVertices<<" vertices and "<<edges<<" edges." << std::endl;
}



