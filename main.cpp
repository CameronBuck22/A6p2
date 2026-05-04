#include "graph.h"

int main() {
    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 9);

    std::cout << "Dijkstra:\n";
    g.dijkstra(0);

    std::cout << "\nKruskal MST:\n";
    g.kruskal();

    std::cout << "\nPrim MST:\n";
    g.prim();

    return 0;
}
