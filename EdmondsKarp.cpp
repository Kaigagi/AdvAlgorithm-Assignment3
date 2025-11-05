#include "EdmondsKarp.h"
#include <queue>
#include <climits>
#include <stdexcept>

// Helper function: uses BFS to find an augmenting path in the residual graph.
// Returns true if a path from source to sink is found.
static bool bfs_find_augmenting_path(FlowGraph& graph, int source, int sink, std::vector<Edge*>& parent) {
    std::fill(parent.begin(), parent.end(), nullptr);
    std::vector<bool> visited(graph.adjacencyList.size(), false);
    std::queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Explore edges with remaining capacity to find a path to sink
        for (Edge* edge : graph.adjacencyList[u]) {
            int v = edge->to;
            int residual = edge->capacity - edge->flow;
            if (!visited[v] && residual > 0) {
                parent[v] = edge;
                visited[v] = true;
                if (v == sink) return true; // Path found
                q.push(v);
            }
        }
    }
    return false; // No path found
}

// Main function: computes maximum flow using the Edmonds–Karp algorithm (BFS-based Ford–Fulkerson).
int EdmondsKarpMaxFlow(FlowGraph& graph, int source, int sink) {
    if (source < 0 || sink < 0 ||
        source >= static_cast<int>(graph.adjacencyList.size()) ||
        sink >= static_cast<int>(graph.adjacencyList.size())) {
        throw std::out_of_range("Source or sink vertex index out of bounds.");
    }

    int maxFlow = 0;
    std::vector<Edge*> parent(graph.adjacencyList.size(), nullptr);

    // Repeatedly find augmenting paths and update flow until none remain
    while (bfs_find_augmenting_path(graph, source, sink, parent)) {
        int bottleneck = INT_MAX;

        // Find minimum residual capacity (bottleneck) along the path
        for (int v = sink; v != source; v = parent[v]->from)
            bottleneck = std::min(bottleneck, parent[v]->capacity - parent[v]->flow);

        // Update forward and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]->from) {
            parent[v]->flow += bottleneck;
            parent[v]->reversedEdge->flow -= bottleneck;
        }

        maxFlow += bottleneck; // Accumulate total flow
    }

    return maxFlow;
}
