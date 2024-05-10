/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

namespace ariel {
    class Graph { // our namespace
    private:
        int numVertices;
        std::vector<std::vector<int>> adjMatrix;

    public:

        // Constructor taking the number of vertices
        Graph() : numVertices(), adjMatrix(0, std::vector<int>(0, 0)) {} // empty graph

        // Constructor taking the adjacency matrix
        Graph(const std::vector<std::vector<int>>& Mat) : adjMatrix(Mat) {
            numVertices = Mat.size();
        }

        int getNumVertices() const;
        std::vector<std::vector<int>> getAdjMatrix() const;
        void loadGraph(const std::vector<std::vector<int>>& adjMat);
        void printGraph();
    };
}

#endif // GRAPH_HPP
