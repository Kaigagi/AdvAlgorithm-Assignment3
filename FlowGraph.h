#include <vector>

using namespace std;

class Edge
{
private:
    /* data */
public:
    int from;
    int to;
    int capacity;
    int flow;
    Edge* reversedEdge;
    Edge(int from, int to, int capacity, int flow);
    ~Edge();
};

class FlowGraph
{
public:
    vector<vector<Edge*>> adjacencyList;
    FlowGraph(int vertexCount);
    ~FlowGraph();
    void AddEdge(Edge* edge);
    int GetEdgeCount();
    vector<Edge*> GetAllEdge();
};

