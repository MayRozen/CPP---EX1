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
    cout << "isConnected test passed!" << endl;
}

TEST_CASE("Test shortestPath")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    vector<int> ans = {0,1,2}; // Chcking if we get the shortest path we expect to
    CHECK(Algorithms::shortestPath(g, 0, 2) == ans);
    cout << "shortestPath test passed!" << endl;
}

TEST_CASE("Test 2 shortestPath")
{
    Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    vector<int> ans2 = {-1}; // Checking what will happen if there is *no* shortest path
    CHECK(Algorithms::shortestPath(g, 0, 4) == ans2);
    cout << "shortestPath test 2 passed!" << endl;
}

TEST_CASE("Test isContainsCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == 0); // There is no cycle

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isContainsCycle(g) == 1); // There is a cycle
    cout << "isContainsCycle test passed!" << endl;
}

TEST_CASE("Test 2 isContainsCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 8, 0},
        {8, 0, 8},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == 0); // There is no cycle

    cout << "isContainsCycle test 2 passed!" << endl;
}

TEST_CASE("Test isBipartite")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == 1); // The graph is bipartite

    cout << "isBipartite test 1 passed!" << endl;
}

TEST_CASE("Test isBipartite 2")
{
    Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isBipartite(g) == 0); // The graph is not bipartite
}

TEST_CASE("Test isBipartite 3")
{
    Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(Algorithms::isBipartite(g) == 0); //  The graph is not bipartite
    cout << "isBipartite test 3 passed!" << endl;
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

    cout << "invalid graph first test passed!" << endl;
}

TEST_CASE("Test invalid graph 2")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 4, 2, 0},
        {1, 0, 3, 0},
        {2, 7, 0, 4},
        {0, 0, 4, 0},
        {8, 8, 8, 8}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {{0}}; // Edge case
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph3 = {}; // Edge case
    CHECK_THROWS(g.loadGraph(graph));
    cout << "invalid graph seconed test passed!" << endl;
}

TEST_CASE("Test 1 negativeCycle")  // Checking the method - 'negativeCycle'
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, -1},
        {-1, 0, -1},
        {-1, 1, 0}};
    g.loadGraph(graph);
    vector<int> ans = {1,1,1,1};
    
    CHECK(Algorithms::negativeCycle(g)!=ans);
    cout << "negativeCycle test 1 passed!" << endl;
}

TEST_CASE("Test large graph") // Testing our algorithms about a large graph
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
    cout << "Large graph test passed!" << endl;
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
    CHECK(Algorithms::isConnected(g) == false); // Checking if we get false
    cout << "Disconnected graph test passed!" << endl;
}

TEST_CASE("Test 2 disconnected graph")
{
    Graph g;
    // Create a graph with multiple disconnected components
    vector<vector<int>> disconnectedGraph = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(disconnectedGraph);
    CHECK(Algorithms::isConnected(g) == false); // Checking if we get false
    cout << "Disconnected test 2 passed!" << endl;
}

TEST_CASE("Disconnected directed graph")
{
    Graph g;
    // Create a directed graph
    vector<vector<int>> directedGraph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(directedGraph); // Checking if loadGraph working as we expect
    cout << "Disconnected directed graph test passed!" << endl;
}

TEST_CASE("Disconnected directed graph 2")
{
    Graph g;
    // Create a directed graph
    vector<vector<int>> directedGraph = {
        {0, -1, 0},
        {0, 0, -1},
        {0, 0, 0}};
    g.loadGraph(directedGraph); // Checking if loadGraph working as we expect
    cout << "Disconnected directed graph test 2 passed!" << endl;
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
    cout << "Weighted graph test passed!" << endl;
}

TEST_CASE("Test 2 weighted graph")
{
    Graph g;
    // Create an weighted graph
    vector<vector<int>> weightedGraph = {
        {0, -5, 0},
        {0, 0, -10},
        {0, 0, 0}};
    g.loadGraph(weightedGraph);
    cout << "weighted graph test 2 passed!" << endl;
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
    cout << "Unweighted graph test passed!" << endl;
}

TEST_CASE("Test 2 unweighted graph")
{
    Graph g;
    // Create an unweighted graph
    vector<vector<int>> unweightedGraph = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g.loadGraph(unweightedGraph);
    cout << "Unweighted graph test 2 passed!" << endl;
}

TEST_CASE("Test isConnected with negative edges") {
    Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {-1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true); // The graph is connected
    cout << "isConnected with negative edges test passed!" << endl;
}

TEST_CASE("Test isBipartite with negative weights") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, -1},
        {1, 0, 1},
        {-1, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == 0); // The graph is not bipartite due to it has negative weight
    cout << "isBipartite with negative weights test passed!" << endl;
}

TEST_CASE("Test isContainsCycle for acyclic graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == false); // There is no cycle
    cout << "isContainsCycle for acyclic graph test passed!" << endl;
}
