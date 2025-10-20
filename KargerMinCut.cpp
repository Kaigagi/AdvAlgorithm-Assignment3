#include "KargerMinCut.h"

Edge* GetRandomEdgeOnce(vector<Edge*>& allEdges)
{
    if (allEdges.empty())
        return nullptr;

    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<> dist(0, allEdges.size() - 1);
    int index = dist(gen);

    Edge* chosen = allEdges[index];

    // remove it from list so it's not picked again
    allEdges.erase(allEdges.begin() + index);

    return chosen;
}

//return the cut flow capacity
int KargerSTMinCut(FlowGraph& graph, int s, int t) {
    int currentVertices = graph.adjacencyList.size();
    UnionFind* uf = new UnionFind(currentVertices);

    vector<Edge*> edgeList = graph.GetAllEdge();

    if (currentVertices <= 1)
    {
        return 0;
    }

    // If there is only one edge in the graph, return its capacity
    vector<Edge*> edges = graph.GetAllEdge();
    if (edges.size() == 1){
        return edges[0]->capacity;
    }

    while (true) {
        // Stop when s and t are in different groups AND 
        // there are only two distinct supernodes left
        int sRoot = uf->Find(s);
        int tRoot = uf->Find(t);
        if (sRoot != tRoot && currentVertices <= 2) break;

        if (edgeList.empty()) break;

        Edge* chosenEdge = GetRandomEdgeOnce(edgeList);
        if (!chosenEdge) break;

        int fromRoot = uf->Find(chosenEdge->from);
        int toRoot = uf->Find(chosenEdge->to);

        // Skip if it merges s and t into the same supernode
        if ((fromRoot == uf->Find(s) && toRoot == uf->Find(t)) ||
            (fromRoot == uf->Find(t) && toRoot == uf->Find(s))) {
            continue;
        }

        // Contract the edge
        if (fromRoot != toRoot) {
            uf->Union(chosenEdge->from, chosenEdge->to);
            currentVertices--;
        }

        // Stop when only two groups remain and s,t are separate
        sRoot = uf->Find(s);
        tRoot = uf->Find(t);
        if (sRoot != tRoot && currentVertices <= 2) break;
    }

    // Count capacity of edges that connect s-supernode and t-supernode
    int cutCapacity = 0;
    int sRoot = uf->Find(s);
    int tRoot = uf->Find(t);

    for (const auto& vertexEdges : graph.adjacencyList) {
        for (Edge* edge : vertexEdges) {
            int fromRoot = uf->Find(edge->from);
            int toRoot = uf->Find(edge->to);

            if ((fromRoot == sRoot && toRoot == tRoot) ||
                (fromRoot == tRoot && toRoot == sRoot)) {
                cutCapacity += edge->capacity;
            }
        }
    }

    delete uf;
    return cutCapacity;
}
