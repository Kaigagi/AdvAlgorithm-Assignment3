#pragma once
#include "FlowGraph.h"
#include "UnionFind.h"
#include <random>

//Return the max flow
int KargerSTMinCut(FlowGraph& graph, int s, int t);