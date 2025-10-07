#include <vector>

using namespace std;


class Vertex
{
public:
    int index;
    Vertex(/* args */);
    ~Vertex();
};

Vertex::Vertex(/* args */)
{
}

Vertex::~Vertex()
{
}


class Edge
{
private:
    /* data */
public:
    Vertex* from;
    Vertex* to;
    int capacity;
    int flow;
    Edge* reversedEdge;
    Edge(Vertex* from, Vertex* to, int capacity, int flow);
    ~Edge();
};

class FlowGraph
{
public:
    vector<vector<Vertex*>> adjacencyList;
    FlowGraph(/* args */);
    ~FlowGraph();
    void AddEdge(Edge* edge);
    void MergeEdge(Edge* edge);
};

FlowGraph::FlowGraph(/* args */)
{
}

FlowGraph::~FlowGraph()
{
}

