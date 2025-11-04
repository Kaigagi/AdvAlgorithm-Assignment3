#include "EdmondsKarp.h"
#include <queue>
#include <climits>
#include <stdexcept>

static bool bfs_find_augmenting_path(FlowGraph& graph, int source, int sink, std::vector<Edge*>& parent) {
    std::fill(parent.begin(), parent.end(), nullptr);
    std::vector<bool> visited(graph.adjacencyList.size(), false);
    std::queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (Edge* edge : graph.adjacencyList[u]) {
            int v = edge->to;
            int residual = edge->capacity - edge->flow;

            if (!visited[v] && residual > 0) {
                parent[v] = edge;
                visited[v] = true;
                if (v == sink) return true;
                q.push(v);
            }
        }
    }
    return false;
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

        while (v != source) {
            Edge* edge = parent[v];
            bottleneck = std::min(bottleneck, edge->capacity - edge->flow);
            v = edge->from;
        }

        v = sink;
        while (v != source) {
            Edge* edge = parent[v];
            edge->flow += bottleneck;
            edge->reversedEdge->flow -= bottleneck;
            v = edge->from;
        }

        maxFlow += bottleneck;
    }

    return maxFlow;
}
