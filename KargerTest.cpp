#include "KargerTest.h"

// -------------------------------
// Helper test graph
// -------------------------------
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

// -------------------------------
// Run Karger Many Times → Max Flow
// -------------------------------
int RunKargerMultipleTimes(FlowGraph baseGraph, int s, int t)
{
    int n = baseGraph.adjacencyList.size();
    int runs = 5 * n * (n - 1);

    int maxFlow = INT_MIN;

    for (int i = 0; i < runs; ++i)
    {
        FlowGraph gCopy = baseGraph;
        int cut = KargerSTMinCut(gCopy, s, t);

        if (cut > maxFlow)
            maxFlow = cut;
    }

    return maxFlow;
}

// -------------------------------
// ✅ MAX FLOW TESTS
// -------------------------------

// Max flow in this graph = 2
TEST(KargerMaxFlowTest, SimpleGraph)
{
    FlowGraph graph = BuildTestGraph();
    int maxFlow = RunKargerMultipleTimes(graph, 0, 3);
    cout<<"max flow: "<<maxFlow;
    EXPECT_EQ(maxFlow, 2);
}

// Empty graph → max flow = 0
TEST(KargerMaxFlowTest, EmptyGraph)
{
    FlowGraph graph(0);
    int maxFlow = RunKargerMultipleTimes(graph, 0, 0);
    cout<<"max flow: "<<maxFlow;
    EXPECT_EQ(maxFlow, 0);
}

// Single edge graph → max flow = capacity
TEST(KargerMaxFlowTest, SingleEdge)
{
    FlowGraph graph(2);
    graph.AddEdge(0, 1, 5);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 1);
    EXPECT_EQ(maxFlow, 5);
}

// Diamond graph → max flow = 2
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

// Parallel edges → max flow = sum of capacities
TEST(KargerMaxFlowTest, ParallelEdges)
{
    FlowGraph graph(2);

    graph.AddEdge(0, 1, 2);
    graph.AddEdge(0, 1, 3);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 1);
    EXPECT_EQ(maxFlow, 5);
}

// Complete graph K5 with unit capacities → max flow = degree(s) = 4
TEST(KargerMaxFlowTest, CompleteGraph5)
{
    const int n = 5;
    FlowGraph graph(n);

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            graph.AddEdge(i, j, 1);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 4);
    cout<<"max flow: "<<maxFlow;
    EXPECT_EQ(maxFlow, 4);
}

// Two strong clusters but only 1-capacity bridge → max flow = 1
TEST(KargerMaxFlowTest, TwoClustersWeakBridge)
{
    FlowGraph graph(6);

    // Left cluster
    graph.AddEdge(0, 1, 5);
    graph.AddEdge(1, 2, 5);

    // Right cluster
    graph.AddEdge(3, 4, 5);
    graph.AddEdge(4, 5, 5);

    // Weak 1-capacity connection
    graph.AddEdge(2, 3, 1);

    int maxFlow = RunKargerMultipleTimes(graph, 0, 5);
    cout<<"max flow: "<<maxFlow;
    EXPECT_EQ(maxFlow, 1);
}
