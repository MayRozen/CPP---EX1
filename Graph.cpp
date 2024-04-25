/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <iostream>
#include <vector>
#include "Graph.hpp"

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
    std::cout << "The Graph:" << std::endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



