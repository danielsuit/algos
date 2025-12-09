#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

// Network Flow Algorithms
// Comprehensive implementation of flow algorithms
// Time Complexity: O(V^2 * E) for Edmonds-Karp
// Space Complexity: O(V^2)

class FlowGraph {
private:
    int V;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;
    
    bool bfs(int s, int t, std::vector<int>& parent) {
        std::vector<bool> visited(V, false);
        std::queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v = 0; v < V; v++) {
                if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                    parent[v] = u;
                    visited[v] = true;
                    if (v == t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    
    void dfs(int u, std::vector<bool>& visited) {
        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                dfs(v, visited);
            }
        }
    }
    
public:
    FlowGraph(int vertices) : V(vertices) {
        capacity.assign(V, std::vector<int>(V, 0));
        flow.assign(V, std::vector<int>(V, 0));
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] += cap;
    }
    
    // Edmonds-Karp (BFS-based Ford-Fulkerson)
    int edmondsKarp(int s, int t) {
        int maxflow = 0;
        std::vector<int> parent(V);
        flow.assign(V, std::vector<int>(V, 0));
        
        while (bfs(s, t, parent)) {
            int pathFlow = INT_MAX;
            
            // Find minimum residual capacity along path
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
            }
            
            // Update flows along path
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += pathFlow;
                flow[v][u] -= pathFlow;
            }
            
            maxflow += pathFlow;
        }
        
        return maxflow;
    }
    
    // Find minimum cut
    std::pair<int, std::vector<std::pair<int, int>>> minCut(int s, int t) {
        int maxFlowValue = edmondsKarp(s, t);
        
        std::vector<bool> visited(V, false);
        dfs(s, visited);
        
        std::vector<std::pair<int, int>> cutEdges;
        
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (visited[u] && !visited[v] && capacity[u][v] > 0) {
                    cutEdges.push_back({u, v});
                }
            }
        }
        
        return {maxFlowValue, cutEdges};
    }
    
    // Check if there's a bottleneck
    std::vector<std::pair<int, int>> findBottlenecks(int s, int t) {
        edmondsKarp(s, t);
        
        std::vector<std::pair<int, int>> bottlenecks;
        
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (capacity[u][v] > 0 && flow[u][v] == capacity[u][v]) {
                    bottlenecks.push_back({u, v});
                }
            }
        }
        
        return bottlenecks;
    }
    
    // Get current flow value
    int getFlow(int u, int v) const {
        return flow[u][v];
    }
    
    // Print flow network
    void printFlow() {
        std::cout << "Flow network:" << std::endl;
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (capacity[u][v] > 0) {
                    std::cout << "  " << u << " -> " << v 
                             << ": " << flow[u][v] << "/" << capacity[u][v] << std::endl;
                }
            }
        }
    }
};

// Dinic's Algorithm (faster for many cases)
class DinicFlow {
private:
    struct Edge {
        int to, cap, flow;
    };
    
    int V;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> graph;
    std::vector<int> level, iter;
    
    bool bfs(int s, int t) {
        level.assign(V, -1);
        level[s] = 0;
        std::queue<int> q;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int id : graph[u]) {
                if (level[edges[id].to] < 0 && edges[id].flow < edges[id].cap) {
                    level[edges[id].to] = level[u] + 1;
                    q.push(edges[id].to);
                }
            }
        }
        
        return level[t] >= 0;
    }
    
    int dfs(int u, int t, int pushed) {
        if (u == t || pushed == 0) return pushed;
        
        for (int& cid = iter[u]; cid < graph[u].size(); cid++) {
            int id = graph[u][cid];
            int to = edges[id].to;
            
            if (level[u] + 1 != level[to] || edges[id].cap <= edges[id].flow)
                continue;
            
            int tr = dfs(to, t, std::min(pushed, edges[id].cap - edges[id].flow));
            if (tr > 0) {
                edges[id].flow += tr;
                edges[id ^ 1].flow -= tr;
                return tr;
            }
        }
        
        return 0;
    }
    
public:
    DinicFlow(int vertices) : V(vertices), graph(vertices), level(vertices), iter(vertices) {}
    
    void addEdge(int from, int to, int cap) {
        graph[from].push_back(edges.size());
        edges.push_back({to, cap, 0});
        graph[to].push_back(edges.size());
        edges.push_back({from, 0, 0});
    }
    
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            iter.assign(V, 0);
            while (int pushed = dfs(s, t, INT_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    std::cout << "=== Network Flow Algorithms ===" << std::endl << std::endl;
    
    // Example 1: Edmonds-Karp
    std::cout << "1. Edmonds-Karp Algorithm:" << std::endl;
    FlowGraph g1(6);
    g1.addEdge(0, 1, 16);
    g1.addEdge(0, 2, 13);
    g1.addEdge(1, 2, 10);
    g1.addEdge(1, 3, 12);
    g1.addEdge(2, 1, 4);
    g1.addEdge(2, 4, 14);
    g1.addEdge(3, 2, 9);
    g1.addEdge(3, 5, 20);
    g1.addEdge(4, 3, 7);
    g1.addEdge(4, 5, 4);
    
    int maxFlow1 = g1.edmondsKarp(0, 5);
    std::cout << "   Max flow: " << maxFlow1 << std::endl;
    g1.printFlow();
    
    // Min cut
    auto [cutValue, cutEdges] = g1.minCut(0, 5);
    std::cout << "\n   Min cut value: " << cutValue << std::endl;
    std::cout << "   Cut edges: ";
    for (auto [u, v] : cutEdges) {
        std::cout << "(" << u << "," << v << ") ";
    }
    std::cout << std::endl;
    
    // Bottlenecks
    auto bottlenecks = g1.findBottlenecks(0, 5);
    std::cout << "   Bottleneck edges: ";
    for (auto [u, v] : bottlenecks) {
        std::cout << "(" << u << "," << v << ") ";
    }
    std::cout << std::endl;
    
    // Example 2: Dinic's Algorithm
    std::cout << "\n2. Dinic's Algorithm:" << std::endl;
    DinicFlow g2(6);
    g2.addEdge(0, 1, 16);
    g2.addEdge(0, 2, 13);
    g2.addEdge(1, 2, 10);
    g2.addEdge(1, 3, 12);
    g2.addEdge(2, 1, 4);
    g2.addEdge(2, 4, 14);
    g2.addEdge(3, 2, 9);
    g2.addEdge(3, 5, 20);
    g2.addEdge(4, 3, 7);
    g2.addEdge(4, 5, 4);
    
    std::cout << "   Max flow: " << g2.maxFlow(0, 5) << std::endl;
    
    std::cout << "\nAlgorithm Comparison:" << std::endl;
    std::cout << "  - Ford-Fulkerson: O(E * max_flow)" << std::endl;
    std::cout << "  - Edmonds-Karp: O(V * E^2)" << std::endl;
    std::cout << "  - Dinic: O(V^2 * E)" << std::endl;
    std::cout << "  - Push-Relabel: O(V^3)" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "  - Maximum bipartite matching" << std::endl;
    std::cout << "  - Minimum cut in networks" << std::endl;
    std::cout << "  - Circulation problems" << std::endl;
    std::cout << "  - Image segmentation" << std::endl;
    std::cout << "  - Airline scheduling" << std::endl;
    
    return 0;
}
