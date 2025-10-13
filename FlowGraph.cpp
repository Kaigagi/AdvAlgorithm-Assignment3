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
