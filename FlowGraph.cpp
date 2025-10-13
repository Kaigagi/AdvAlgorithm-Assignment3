#include "FlowGraph.h"

Edge::Edge(int from, int to, int capacity, int flow)
{
}

Edge::~Edge()
{
}

FlowGraph::FlowGraph(int vertexCount)
{
    adjacencyList.resize(vertexCount);
}

int FlowGraph::GetEdgeCount()
{
    int count = 0;
    for (const auto& edges : adjacencyList)
        count += static_cast<int>(edges.size());
    return count;
}

vector<Edge*> FlowGraph::GetAllEdge()
{
    vector<Edge*> allEdges;

    for (const auto& edges : adjacencyList)
    {
        for (const auto& edge : edges)
        {
            // Optional: skip reverse edges to avoid duplicates
            if (edge->capacity > 0)
                allEdges.push_back(edge);
        }
    }

    return allEdges;
}
