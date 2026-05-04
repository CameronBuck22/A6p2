#include "graph.h"
#include <queue>
#include <algorithm>
#include <climits>

Graph::Graph(int vertices) {
    numVertices = vertices;
    adj.resize(vertices);
}

void Graph::addEdge(int src, int dest, int weight) {
    adj[src].push_back({dest, weight});
    adj[dest].push_back({src, weight});
}

// ---------------- Dijkstra ----------------
void Graph::dijkstra(int start) {
    std::vector<int> dist(numVertices, INT_MAX);

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << " distance: " << dist[i] << std::endl;
    }
}

// ---------------- Union-Find Helpers ----------------
int findParent(std::vector<int>& parent, int v) {
    if (parent[v] == v)
        return v;
    return parent[v] = findParent(parent, parent[v]);
}

void unionSet(std::vector<int>& parent, std::vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rank[rootU] < rank[rootV])
        parent[rootU] = rootV;
    else if (rank[rootU] > rank[rootV])
        parent[rootV] = rootU;
    else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

// ---------------- Kruskal ----------------
void Graph::kruskal() {
    std::vector<std::vector<int>> edges;

    for (int u = 0; u < numVertices; u++) {
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (u < v)
                edges.push_back({w, u, v});
        }
    }

    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(numVertices);
    std::vector<int> rank(numVertices, 0);

    for (int i = 0; i < numVertices; i++)
        parent[i] = i;

    int totalCost = 0;

    for (auto e : edges) {
        int w = e[0], u = e[1], v = e[2];

        if (findParent(parent, u) != findParent(parent, v)) {
            std::cout << u << " - " << v << " weight: " << w << std::endl;
            totalCost += w;
            unionSet(parent, rank, u, v);
        }
    }

    std::cout << "Total cost: " << totalCost << std::endl;
}

// ---------------- Prim ----------------
void Graph::prim() {
    std::vector<bool> inMST(numVertices, false);

    std::priority_queue<
        std::vector<int>,
        std::vector<std::vector<int>>,
        std::greater<std::vector<int>>
    > pq;

    pq.push({0, 0, -1});

    int totalCost = 0;

    while (!pq.empty()) {
        int w = pq.top()[0];
        int u = pq.top()[1];
        int parent = pq.top()[2];
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;
        totalCost += w;

        if (parent != -1)
            std::cout << parent << " - " << u << " weight: " << w << std::endl;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v]) {
                pq.push({weight, v, u});
            }
        }
    }

    std::cout << "Total cost: " << totalCost << std::endl;
}
