#include "KargerTest.h"

FlowGraph BuildTestGraph()
{
    FlowGraph graph(4);

    graph.AddEdge(0, 1, 1);
    graph.AddEdge(0, 2, 1);
    graph.AddEdge(1, 2, 1);
    graph.AddEdge(1, 3, 1);
    graph.AddEdge(2, 3, 1);

    return graph;
}

// Test that KargerLoop returns a valid min cut
TEST(KargerMinCutTest, SimpleGraph)
{
    FlowGraph graph = BuildTestGraph();

    // Karger is probabilistic, so run multiple times
    int minCut = INT_MAX;
    for (int i = 0; i < 50; ++i)
    {
        FlowGraph gCopy = BuildTestGraph();  // copy graph
        int cut = KargerLoop(gCopy);
        if (cut < minCut) minCut = cut;
    }

    // The minimum cut of this graph is 2
    EXPECT_EQ(minCut, 2);
}

// Test empty graph
TEST(KargerMinCutTest, EmptyGraph)
{
    FlowGraph graph(0);
    int cut = KargerLoop(graph);
    EXPECT_EQ(cut, 0);
}

// Test single edge graph
TEST(KargerMinCutTest, SingleEdge)
{
    FlowGraph graph(2);
    graph.AddEdge(0, 1, 5);
    int cut = KargerLoop(graph);
    EXPECT_EQ(cut, 5);
}