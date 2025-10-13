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

    vector<Edge*> edgeList = graph.GetAllEdge();
    
    while (currentVertices > 2)
    {
        Edge* chosenEdge = GetRandomEdgeOnce(edgeList);

        int fromRoot = uf->Find(chosenEdge->from);
        int toRoot = uf->Find(chosenEdge->to);

        if (fromRoot != toRoot)
        {
            uf->Union(chosenEdge->from, chosenEdge->to);
            currentVertices--;
        }
    }

    //count cut capacity
    int cutCapacity = 0;
    for(vector<Edge*> vertex : graph.adjacencyList){
        for (Edge* edge : vertex)
        {
            int fromRoot = uf->Find(edge->from);
            int toRoot = uf->Find(edge->to);

            if (fromRoot != toRoot)
            {
                cutCapacity += edge->capacity;
            }
        }
    }
    
    return cutCapacity;
}