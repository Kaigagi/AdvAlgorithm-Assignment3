#include "FlowGraph.h"
#include "EdmondsKarp.h"
#include <gtest/gtest.h>

static FlowGraph createTestGraph1() {
    FlowGraph graph(4);
    graph.AddEdge(0, 1, 3);
    graph.AddEdge(0, 2, 2);
    graph.AddEdge(1, 2, 5);
    graph.AddEdge(1, 3, 2);
    graph.AddEdge(2, 3, 3);
    return graph;
}

TEST(EdmondsKarpMaxFlow, SimpleGraph) {
    FlowGraph graph = createTestGraph1();
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 3);
    EXPECT_EQ(maxFlow, 5); // Expected max flow is 5
}

TEST(EdmondsKarpMaxFlow, NoPath) {
    FlowGraph graph(3);
    graph.AddEdge(0, 1, 2);
    // No edge from 1 to 2, so no path from source (0) to sink (2)
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 2);
    EXPECT_EQ(maxFlow, 0); // Expected max flow is 0
}

TEST(EdmondsKarpMaxFlow, SingleEdge) {
    FlowGraph graph(2);
    graph.AddEdge(0, 1, 10);
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 1);
    EXPECT_EQ(maxFlow, 10); // Expected max flow is 10
}

TEST(EdmondsKarpMaxFlow, Diamond) {
    FlowGraph graph(4);
    graph.AddEdge(0, 1, 10);
    graph.AddEdge(0, 2, 10);
    graph.AddEdge(1, 3, 10);
    graph.AddEdge(2, 3, 10);
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 3);
    EXPECT_EQ(maxFlow, 20); // Expected max flow is 20
}

TEST(EdmondsKarpMaxFlow, ParallelEdges) {
    FlowGraph graph(3);
    graph.AddEdge(0, 1, 5);
    graph.AddEdge(0, 1, 15); // Parallel edge
    graph.AddEdge(1, 2, 10);
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 2);
    EXPECT_EQ(maxFlow, 10); // Expected max flow is 10
}

TEST(EdmondsKarpMaxFlow, BridgeBetweenClusters) {
    FlowGraph graph(6);
    graph.AddEdge(0, 1, 10);
    graph.AddEdge(1, 2, 5);
    graph.AddEdge(2, 3, 15);
    graph.AddEdge(3, 4, 10);
    graph.AddEdge(4, 5, 10);
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 5);
    EXPECT_EQ(maxFlow, 5); // Expected max flow is limited by the bridge edge (1->2)
}

TEST(EdmondsKarpMaxFlow, InvalidSourceSink) {
    FlowGraph graph = createTestGraph1();
    EXPECT_THROW(EdmondsKarpMaxFlow(graph, -1, 3), std::out_of_range);
    EXPECT_THROW(EdmondsKarpMaxFlow(graph, 0, 4), std::out_of_range);
}

TEST(EdmondsKarpMaxFlow, ZeroCapacityEdges) {
    FlowGraph graph(3);
    graph.AddEdge(0, 1, 0); // Zero capacity edge
    graph.AddEdge(1, 2, 10);
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 2);
    EXPECT_EQ(maxFlow, 0); // Expected max flow is 0 due to zero capacity edge
}

TEST(EdmondsKarpMaxFlow, LargeCapacities) {
    FlowGraph graph(3);
    graph.AddEdge(0, 1, INT_MAX);
    graph.AddEdge(1, 2, INT_MAX);
    int maxFlow = EdmondsKarpMaxFlow(graph, 0, 2);
    EXPECT_EQ(maxFlow, INT_MAX); // Expected max flow is INT_MAX
}