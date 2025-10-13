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
int KargerLoop(FlowGraph& graph){
    //The amount of vertices is the graph vertices at beginning
    int currentVertices = graph.adjacencyList.size();
    UnionFind* uf = new UnionFind(currentVertices);

    vector<Edge*> edgeList
    
    while (currentVertices > 2)
    {
        int random
    }
    
}