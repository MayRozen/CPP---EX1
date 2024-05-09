/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {
    class Graph { // our namespace
        Graph::Graph(int n) : numVertices(n) {
        adjMatrix.resize(n, std::vector<int>(n, 0));
        }
    private:
        int numVertices;
        std::vector<std::vector<int>> adjMatrix;

    public:
        Graph(int n); // constructor
        int getNumVertices() const;
        std::vector<std::vector<int>> getAdjMatrix() const;
        void loadGraph(const std::vector<std::vector<int>>& adjMat);
        void printGraph();
    };
}

#endif // GRAPH_HPP
