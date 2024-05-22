/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"
using namespace ariel;

// getter to numVertices
int Graph::getNumVertices() const{
    return numVertices;
}

// getter to adjMatrix
std::vector<std::vector<int>> Graph::getAdjMatrix() const{
    return adjMatrix;
}

// setter to adjMatrix
void Graph::loadGraph(const std::vector<std::vector<int>>& adjMat) {
    if(adjMat.size() != adjMat[0].size()||adjMat.size() == 0){
        throw std::invalid_argument("Error! The graph is not a square matrix or is empty.");
    }

    this->adjMatrix = adjMat;
    this->numVertices = adjMat.size();
}

void Graph::printGraph(){
    int edges = 0;
    for (IndexType i = 0; i < numVertices; i++) {
        for (IndexType j = 0; j < numVertices; j++) {
            if(adjMatrix[i][j]!=0){ // Assuming the lack of an edge is expressed by 0
                edges++;
            }
        }
    }
    std::cout << "Graph with "<<numVertices<<" vertices and "<<edges<<" edges." << std::endl;
}



