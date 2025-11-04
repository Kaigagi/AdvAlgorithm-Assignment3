#include "EdmondsKarp.h"
#include <queue>
#include <climits>
#include <stdexcept>

static bool bfs_find_augmenting_path(FlowGraph& graph, int source, int sink, std::vector<Edge*>& parent) {
    std::fill(parent.begin(), parent.end(), nullptr);
    std::queue<int> q;
    q.push(source);
    parent[source] = reinterpret_cast<Edge*>(-1); // Mark source as visited

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (Edge* edge : graph.adjacencyList[u]) {
            int v = edge->to;

            // If not yet visited and residual capacity exists
            if (parent[v] == nullptr && edge->capacity > edge->flow) {
                parent[v] = edge;
                if (v == sink) {
                    return true; // Found path to sink
                }
                q.push(v);
            }
        }
    }
    return false; // No augmenting path found
}

int EdmondsKarpMaxFlow(FlowGraph& graph, int source, int sink) {
    if (source < 0 || sink < 0 ||
        source >= static_cast<int>(graph.adjacencyList.size()) ||
        sink >= static_cast<int>(graph.adjacencyList.size())) {
        throw std::out_of_range("Source or sink vertex index out of bounds.");
    }

    int maxFlow = 0;
    std::vector<Edge*> parent(graph.adjacencyList.size(), nullptr);

    while (bfs_find_augmenting_path(graph, source, sink, parent)) {
        int bottleneck = INT_MAX;
        int v = sink;

        // Trace back to find bottleneck capacity
        while (v != source) {
            Edge* edge = parent[v];
            bottleneck = std::min(bottleneck, edge->capacity - edge->flow);
            v = edge->from;
        }

        // Augment flow along the path
        v = sink;
        while (v != source) {
            Edge* edge = parent[v];
            edge->flow += bottleneck;
            edge->reversedEdge->flow -= bottleneck;
            v = edge->from;
        }

        // Add to total flow
        maxFlow += bottleneck;
    }

    return maxFlow;
}
