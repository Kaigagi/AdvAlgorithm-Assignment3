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

// Run Karger 5 * n * (n-1) times for more reliability
int RunKargerMultipleTimes(FlowGraph baseGraph, int s, int t)
{
    int n = baseGraph.adjacencyList.size();
    int runs = 5 * n * (n - 1);

    int minCut = INT_MAX;

    for (int i = 0; i < runs; ++i)
    {
        FlowGraph gCopy = baseGraph; // fresh copy
        int cut = KargerSTMinCut(gCopy, s, t);
        if (cut < minCut) minCut = cut;
    }

    return minCut;
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

TEST(KargerMaxFlowTest, DiamondGraph)
{
    FlowGraph graph(4);

    graph.AddEdge(0, 1, 1);
    graph.AddEdge(1, 3, 1);
    graph.AddEdge(0, 2, 1);
    graph.AddEdge(2, 3, 1);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 3);
    EXPECT_EQ(maxFlow, 2);
}

TEST(KargerMaxFlowTest, ParallelEdges)
{
    FlowGraph graph(2);

    graph.AddEdge(0, 1, 2);
    graph.AddEdge(0, 1, 3); // parallel edge

    int maxFlow = RunKargerMultipleTimes(graph, 0, 1);
    EXPECT_EQ(maxFlow, 5);
}

TEST(KargerMaxFlowTest, CompleteGraph5)
{
    const int n = 5;
    FlowGraph graph(n);

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            graph.AddEdge(i, j, 1);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 4);
    EXPECT_EQ(maxFlow, 4);
}

TEST(KargerMaxFlowTest, TwoClustersWeakBridge)
{
    FlowGraph graph(6);

    // Left cluster (strong)
    graph.AddEdge(0, 1, 5);
    graph.AddEdge(1, 2, 5);

    // Right cluster (strong)
    graph.AddEdge(3, 4, 5);
    graph.AddEdge(4, 5, 5);

    // Weak connection
    graph.AddEdge(2, 3, 1);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 5);
    EXPECT_EQ(maxFlow, 1);
}


