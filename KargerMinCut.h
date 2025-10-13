#include "FlowGraph.h"
#include "UnionFind.h"
#include <random>

//Return the max flow
int KargerMaxFlow(FlowGraph& graph);

int KargerLoop(FlowGraph& graph);