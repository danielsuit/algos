#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

// Flow Variants: Max Flow with Additional Constraints
// Multiple sources/sinks, vertex capacities, edge demands
// Time Complexity: varies by variant
// Space Complexity: O(V^2)

class FlowNetwork {
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
                    if (v == t) return true;
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
        return false;
    }
    
public:
    FlowNetwork(int vertices) : V(vertices) {
        capacity.assign(V, std::vector<int>(V, 0));
        flow.assign(V, std::vector<int>(V, 0));
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }
    
    // Standard max flow (Ford-Fulkerson with BFS)
    int maxFlow(int s, int t) {
        int maxflow = 0;
        std::vector<int> parent(V);
        flow.assign(V, std::vector<int>(V, 0));
        
        while (bfs(s, t, parent)) {
            int pathFlow = INT_MAX;
            
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
            }
            
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += pathFlow;
                flow[v][u] -= pathFlow;
            }
            
            maxflow += pathFlow;
        }
        
        return maxflow;
    }
    
    // Multiple sources to multiple sinks
    int multiSourceSinkFlow(const std::vector<int>& sources, const std::vector<int>& sinks) {
        // Add super source and super sink
        int superSource = V;
        int superSink = V + 1;
        
        FlowNetwork extended(V + 2);
        
        // Copy existing edges
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (capacity[i][j] > 0)
                    extended.addEdge(i, j, capacity[i][j]);
            }
        }
        
        // Connect super source to all sources
        for (int s : sources) {
            extended.addEdge(superSource, s, INT_MAX);
        }
        
        // Connect all sinks to super sink
        for (int t : sinks) {
            extended.addEdge(t, superSink, INT_MAX);
        }
        
        return extended.maxFlow(superSource, superSink);
    }
    
    // Flow with edge demands (lower bounds)
    int flowWithDemands(int s, int t, const std::vector<std::vector<int>>& demand) {
        // Transform to standard max flow with demands satisfied
        std::vector<int> balance(V, 0);
        FlowNetwork newNet(V);
        
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (capacity[u][v] > 0) {
                    int d = demand[u][v];
                    newNet.addEdge(u, v, capacity[u][v] - d);
                    balance[u] -= d;
                    balance[v] += d;
                }
            }
        }
        
        // Add artificial source and sink for balancing
        int newS = V;
        int newT = V + 1;
        FlowNetwork balanced(V + 2);
        
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (newNet.capacity[i][j] > 0) {
                    balanced.addEdge(i, j, newNet.capacity[i][j]);
                }
            }
            
            if (balance[i] > 0) {
                balanced.addEdge(newS, i, balance[i]);
            } else if (balance[i] < 0) {
                balanced.addEdge(i, newT, -balance[i]);
            }
        }
        
        balanced.addEdge(t, s, INT_MAX);
        
        return balanced.maxFlow(newS, newT);
    }
};

// Vertex capacity network (split vertices)
class VertexCapacityNetwork {
private:
    int V;
    FlowNetwork net;
    
public:
    VertexCapacityNetwork(int vertices) : V(vertices), net(2 * vertices) {}
    
    void addEdge(int u, int v, int cap) {
        net.addEdge(2*u + 1, 2*v, cap);
    }
    
    void setVertexCapacity(int v, int cap) {
        net.addEdge(2*v, 2*v + 1, cap);
    }
    
    int maxFlow(int s, int t) {
        return net.maxFlow(2*s, 2*t + 1);
    }
};

int main() {
    std::cout << "=== Flow Network Variants ===" << std::endl << std::endl;
    
    // Standard max flow
    std::cout << "1. Standard Max Flow:" << std::endl;
    FlowNetwork g1(6);
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
    
    std::cout << "   Max flow from 0 to 5: " << g1.maxFlow(0, 5) << std::endl;
    
    // Multiple sources/sinks
    std::cout << "\n2. Multiple Sources/Sinks:" << std::endl;
    FlowNetwork g2(4);
    g2.addEdge(0, 2, 10);
    g2.addEdge(1, 2, 10);
    g2.addEdge(2, 3, 15);
    
    std::vector<int> sources = {0, 1};
    std::vector<int> sinks = {3};
    std::cout << "   Max flow: " << g2.multiSourceSinkFlow(sources, sinks) << std::endl;
    
    // Vertex capacities
    std::cout << "\n3. Vertex Capacities:" << std::endl;
    VertexCapacityNetwork g3(4);
    g3.setVertexCapacity(0, 100);
    g3.setVertexCapacity(1, 5);
    g3.setVertexCapacity(2, 5);
    g3.setVertexCapacity(3, 100);
    g3.addEdge(0, 1, 10);
    g3.addEdge(0, 2, 10);
    g3.addEdge(1, 3, 10);
    g3.addEdge(2, 3, 10);
    
    std::cout << "   Max flow with vertex caps: " << g3.maxFlow(0, 3) << std::endl;
    
    std::cout << "\nFlow Variant Applications:" << std::endl;
    std::cout << "  - Multi-commodity flow (multiple types)" << std::endl;
    std::cout << "  - Circulation with demands" << std::endl;
    std::cout << "  - Network reliability" << std::endl;
    std::cout << "  - Traffic assignment" << std::endl;
    
    return 0;
}
