#include "KargerTest.h"

FlowGraph BuildTestGraph()
{
    // Node 0 = source (s)
    // Node 3 = sink (t)
    FlowGraph graph(4);

    graph.AddEdge(0, 1, 1);
    graph.AddEdge(0, 2, 1);
    graph.AddEdge(1, 2, 1);
    graph.AddEdge(1, 3, 1);
    graph.AddEdge(2, 3, 1);

    return graph;
}

// Test that KargerLoop returns a valid min cut when s=0 and t=3
TEST(KargerMinCutTest, SimpleGraphWithSourceSink)
{
    FlowGraph graph = BuildTestGraph();

    // Karger is probabilistic, so run multiple times to reduce chance of bad luck
    int minCut = INT_MAX;
    for (int i = 0; i < 100; ++i)
    {
        FlowGraph gCopy = BuildTestGraph();  // Rebuild for fresh random edges
        int cut = KargerSTMinCut(gCopy, 0, 3);   // Explicitly use source=s=0, sink=t=3
        if (cut < minCut) minCut = cut;
    }

    // The min cut between s=0 and t=3 in this graph is 2
    EXPECT_EQ(minCut, 2);
}

// Test when graph is empty (no vertices)
TEST(KargerMinCutTest, EmptyGraph)
{
    FlowGraph graph(0);
    int cut = KargerSTMinCut(graph, 0, 0);
    EXPECT_EQ(cut, 0);
}

// Test when graph has a single edge (s=0, t=1)
TEST(KargerMinCutTest, SingleEdge)
{
    FlowGraph graph(2);
    graph.AddEdge(0, 1, 5);

    int cut = KargerSTMinCut(graph, 0, 1);
    EXPECT_EQ(cut, 5);
}
