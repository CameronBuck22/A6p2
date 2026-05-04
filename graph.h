#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adj;

public:
    Graph(int vertices);

    void addEdge(int src, int dest, int weight);

    // Task 1
    void dijkstra(int start);

    // Task 2
    void kruskal();

    // Task 3
    void prim();
};

#endif
