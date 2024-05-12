/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

namespace ariel {
    using IndexType = typename std::vector<int>::size_type; // Define a type alias for vector index type
    class Graph { // our namespace
    private:
        int numVertices;
        std::vector<std::vector<int>> adjMatrix;

    public:
        Graph() : numVertices(), adjMatrix(0, std::vector<int>(0, 0)) {} // empty graph

        // Constructor taking the adjacency matrix
        Graph(const std::vector<std::vector<int>>& Mat) : adjMatrix(Mat) {
            this->numVertices = Mat.size();
        }

       std::vector<int>& operator[](size_t i) {
            if (i >= numVertices) {
                throw std::out_of_range("Index out of bounds");
            }
            return adjMatrix[i];
        }

        const std::vector<int>& operator[](size_t i) const {
            if (i >= numVertices) {
                throw std::out_of_range("Index out of bounds");
            }
            return adjMatrix[i];
        }

        int getNumVertices() const;
        std::vector<std::vector<int>> getAdjMatrix() const;
        void loadGraph(const std::vector<std::vector<int>>& adjMat);
        void printGraph();
    };
}

#endif // GRAPH_HPP
