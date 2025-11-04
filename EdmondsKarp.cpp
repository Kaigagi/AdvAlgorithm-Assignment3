#include "EdmondsKarp.h"
#include <queue>
#include <climits>
#include <stdexcept>

static bool bfs_find_augmenting_path(FlowGraph& graph, int source, int sink, std::vector<Edge*>& parent) {
    std::fill(parent.begin(), parent.end(), nullptr);
    std::queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (Edge& edge : graph.adjacencyList[u]) {
            if (parent[edge.to] == nullptr && edge.to != source && edge.capacity > edge.flow) {
                parent[edge.to] = &edge;
                if (edge.to == sink) {
                    return true; // Found path to sink
                }
                q.push(edge.to);
            }
        }
    }
    return false; // No path found
}

int EdmondsKarpMaxFlow(FlowGraph& graph, int source, int sink) {
    if (source < 0 || sink < 0 || source >= static_cast<int>(graph.adjacencyList.size()) || sink >= static_cast<int>(graph.adjacencyList.size())) {
        throw std::out_of_range("Source or sink vertex index out of bounds.");
    }

    int maxFlow = 0;
    std::vector<Edge*> parent(graph.adjacencyList.size(), nullptr);

    while (bfs_find_augmenting_path(graph, source, sink, parent)) {
        int bottlenexkt = INT_MAX;
        int v = sink;

        while (v != source) {
            Edge* edge = parent[v];
            bottlenexkt = std::min(bottlenexkt, edge->capacity - edge->flow);
            v = edge->from;
        }

        if (bottlenexkt == 0 || bottlenexkt == INT_MAX) {
            break; // No more augmenting path
        }

        v = sink;
        while (v != source) {
            Edge* edge = parent[v];
            edge->flow += bottlenexkt;
            edge->reversedEdge->flow -= bottlenexkt;
            v = edge->from;
        }

        maxFlow += bottlenexkt;
    }

    return maxFlow;

}