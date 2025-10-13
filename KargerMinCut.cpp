#include "KargerMinCut.h"

//return the cut flow capacity
int KargerLoop(FlowGraph& graph){
    //The amount of vertices is the graph vertices at beginning
    int currentVertices = graph.adjacencyList.size();
    UnionFind* uf = new UnionFind(currentVertices);
    
    while (currentVertices > 2)
    {
        int random
    }
    
}