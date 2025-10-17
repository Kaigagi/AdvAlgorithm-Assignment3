#include "FlowGraph.h"

Edge::Edge(int from, int to, int capacity, int flow)
{
    this->from = from;
    this->to = to;
    this->capacity = capacity;
    this->flow = flow;
}

Edge::~Edge()
{
}

FlowGraph::FlowGraph(int vertexCount)
{
    adjacencyList.resize(vertexCount);
}

FlowGraph::~FlowGraph()
{
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

void FlowGraph::AddEdge(int from, int to, int capacity)
{
    // Create forward and backward edges
    Edge* forward = new Edge(from, to, capacity, 0); 
    Edge* backward = new Edge(to, from, 0, 0);       

    // Link the edges
    forward->reversedEdge = backward;
    backward->reversedEdge = forward;

    // Add them to the adjacency list
    adjacencyList[from].push_back(forward);
    adjacencyList[to].push_back(backward);
}
