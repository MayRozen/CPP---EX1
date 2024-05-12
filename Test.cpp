/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/
#include "doctest.h"
using namespace std;
#include "Graph.hpp"
#include "Algorithms.hpp"

using IndexType = typename std::vector<int>::size_type; // Define a type alias for vector index type

TEST_CASE("Test isConnected")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isConnected(g) == false);

    // Checking with negative edges
    vector<vector<int>> graph3 = {
        {0, -1, 0},
        {-1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    vector<int> ans = {0,1,2};
    CHECK(Algorithms::shortestPath(g, 0, 2) == ans);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    vector<int> ans2 = {-1};
    CHECK(Algorithms::shortestPath(g, 0, 4) == ans2);
}
TEST_CASE("Test isContainsCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isContainsCycle(g) == true);
}
TEST_CASE("Test isBipartite")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == 1);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isBipartite(g) == 0);

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(Algorithms::isBipartite(g) == 1);
}
TEST_CASE("Test invalid graph")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {{0}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph3 = {};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test invalid graph")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {{0}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph3 = {};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test negativeCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {-2, 0, -2, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    vector<int> ans = {0,1,2};
    CHECK(Algorithms::negativeCycle(graph)==ans);

}

TEST_CASE("Test large graph")
{
    Graph g;
    // Create a large graph with 100 vertices and edges connecting every pair of vertices
    IndexType numVertices = 100;
    vector<vector<int>> largeGraph(numVertices, vector<int>(numVertices, 0));
    for (IndexType i = 0; i < numVertices; ++i) {
        for (IndexType j = i + 1; j < numVertices; ++j) {
            largeGraph[i][j] = 1;
            largeGraph[j][i] = 1;
        }
    }
    g.loadGraph(largeGraph);
    
    CHECK(Algorithms::isConnected(g) == true);

    // Test shortestPath algorithm
    vector<int> expectedPath;
    for (int i = 0; i < numVertices; ++i) {
        expectedPath.push_back(i);
    }

    vector<int> shortestPath = Algorithms::shortestPath(g, 0, numVertices - 1);
    CHECK(shortestPath == expectedPath);
}

TEST_CASE("Test disconnected graph")
{
    Graph g;
    // Create a graph with multiple disconnected components
    vector<vector<int>> disconnectedGraph = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(disconnectedGraph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test directed graph")
{
    Graph g;
    // Create a directed graph
    vector<vector<int>> directedGraph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(directedGraph);
}

TEST_CASE("Test weighted graph")
{
    Graph g;
    // Create a weighted graph
    vector<vector<int>> weightedGraph = {
        {0, 5, 0},
        {0, 0, 10},
        {0, 0, 0}};
    g.loadGraph(weightedGraph);
}

TEST_CASE("Test unweighted graph")
{
    Graph g;
    // Create an unweighted graph
    vector<vector<int>> unweightedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(unweightedGraph);
}

TEST_CASE("Test invalid graph input")
{
    Graph g;
    vector<vector<int>> invalidGraph = {
        {0, -1, 0},
        {-1, 0, 1},
        {0, 1, 0}};
    CHECK_THROWS(g.loadGraph(invalidGraph));
}



