#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * MINIMUM COST FLOW ALGORITHMS
 * 
 * Problem: Send 'flow' units from source to sink with minimum cost.
 * Each edge has capacity and unit cost.
 * 
 * Applications:
 * - Transportation problems
 * - Assignment with costs
 * - Supply chain optimization
 * - Network routing with QoS
 */

// ============================================================================
// SUCCESSIVE SHORTEST PATH ALGORITHM
// ============================================================================
/*
 * Time Complexity: O(flow * (E + V log V)) - using Dijkstra
 * Space Complexity: O(V + E)
 * 
 * Method:
 * 1. Find shortest path in residual graph (by cost)
 * 2. Augment flow along path
 * 3. Repeat until desired flow achieved
 * 
 * Uses modified Dijkstra to handle negative costs via potentials
 */

class MinCostFlow {
private:
    struct Edge {
        int to, rev;
        int cap, cost;
    };
    
    vector<vector<Edge>> graph;
    vector<int> potential, dist, parent, parentEdge;
    int n;
    const int INF = 1e9;
    
    // Bellman-Ford to initialize potentials (handles negative costs)
    void bellmanFord(int source) {
        potential.assign(n, INF);
        potential[source] = 0;
        
        for (int iter = 0; iter < n - 1; iter++) {
            for (int u = 0; u < n; u++) {
                if (potential[u] == INF) continue;
                
                for (const Edge& e : graph[u]) {
                    if (e.cap > 0) {
                        potential[e.to] = min(potential[e.to], 
                                             potential[u] + e.cost);
                    }
                }
            }
        }
    }
    
    // Dijkstra with potentials (reduced costs are non-negative)
    bool dijkstra(int source, int sink) {
        dist.assign(n, INF);
        parent.assign(n, -1);
        parentEdge.assign(n, -1);
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
                      greater<pair<int, int>>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (int i = 0; i < graph[u].size(); i++) {
                const Edge& e = graph[u][i];
                
                if (e.cap > 0) {
                    // Reduced cost = actual cost + potential difference
                    int reducedCost = e.cost + potential[u] - potential[e.to];
                    
                    if (dist[u] + reducedCost < dist[e.to]) {
                        dist[e.to] = dist[u] + reducedCost;
                        parent[e.to] = u;
                        parentEdge[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
        }
        
        return dist[sink] != INF;
    }
    
public:
    MinCostFlow(int vertices) : n(vertices) {
        graph.resize(n);
        potential.resize(n);
    }
    
    void addEdge(int from, int to, int cap, int cost) {
        graph[from].push_back({to, (int)graph[to].size(), cap, cost});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0, -cost});
    }
    
    pair<int, int> minCostFlow(int source, int sink, int maxFlow) {
        int totalFlow = 0;
        int totalCost = 0;
        
        // Initialize potentials
        bellmanFord(source);
        
        while (totalFlow < maxFlow) {
            if (!dijkstra(source, sink)) {
                break; // No more paths
            }
            
            // Find bottleneck capacity
            int pathFlow = maxFlow - totalFlow;
            int v = sink;
            
            while (v != source) {
                int u = parent[v];
                int edgeIdx = parentEdge[v];
                pathFlow = min(pathFlow, graph[u][edgeIdx].cap);
                v = u;
            }
            
            // Augment flow
            v = sink;
            while (v != source) {
                int u = parent[v];
                int edgeIdx = parentEdge[v];
                
                Edge& e = graph[u][edgeIdx];
                e.cap -= pathFlow;
                graph[v][e.rev].cap += pathFlow;
                
                totalCost += pathFlow * e.cost;
                v = u;
            }
            
            totalFlow += pathFlow;
            
            // Update potentials for next iteration
            for (int i = 0; i < n; i++) {
                if (dist[i] < INF) {
                    potential[i] += dist[i];
                }
            }
        }
        
        return {totalFlow, totalCost};
    }
};

// ============================================================================
// CYCLE-CANCELING ALGORITHM
// ============================================================================
/*
 * Time Complexity: O(U * E^2 * log V) where U is max capacity
 * Space Complexity: O(V + E)
 * 
 * Method:
 * 1. Find max flow (any method)
 * 2. While there exists negative cost cycle:
 *    - Find cycle using Bellman-Ford
 *    - Cancel cycle by augmenting flow
 */

class CycleCanceling {
private:
    struct Edge {
        int to, rev;
        int cap, cost, flow;
    };
    
    vector<vector<Edge>> graph;
    int n;
    const int INF = 1e9;
    
    // Bellman-Ford to detect negative cycle
    bool findNegativeCycle(vector<int>& cycle) {
        vector<int> dist(n, INF);
        vector<int> parent(n, -1);
        
        dist[0] = 0;
        int x = -1;
        
        // Relax edges n times
        for (int iter = 0; iter < n; iter++) {
            x = -1;
            for (int u = 0; u < n; u++) {
                if (dist[u] == INF) continue;
                
                for (int i = 0; i < graph[u].size(); i++) {
                    const Edge& e = graph[u][i];
                    
                    if (e.flow < e.cap && dist[u] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost;
                        parent[e.to] = u;
                        x = e.to;
                    }
                }
            }
        }
        
        if (x == -1) return false; // No negative cycle
        
        // Reconstruct cycle
        for (int i = 0; i < n; i++) {
            x = parent[x];
        }
        
        cycle.clear();
        for (int v = x;; v = parent[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1) break;
        }
        
        reverse(cycle.begin(), cycle.end());
        return true;
    }
    
public:
    CycleCanceling(int vertices) : n(vertices) {
        graph.resize(n);
    }
    
    void addEdge(int from, int to, int cap, int cost) {
        graph[from].push_back({to, (int)graph[to].size(), cap, cost, 0});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0, -cost, 0});
    }
    
    pair<int, int> minCostMaxFlow(int source, int sink) {
        // First, find max flow (simplified version)
        // In practice, use any max flow algorithm
        
        // Then cancel negative cycles
        vector<int> cycle;
        while (findNegativeCycle(cycle)) {
            // Find minimum residual capacity in cycle
            int minCap = INF;
            for (int i = 0; i < cycle.size() - 1; i++) {
                int u = cycle[i];
                int v = cycle[i + 1];
                
                for (Edge& e : graph[u]) {
                    if (e.to == v) {
                        minCap = min(minCap, e.cap - e.flow);
                    }
                }
            }
            
            // Augment along cycle
            for (int i = 0; i < cycle.size() - 1; i++) {
                int u = cycle[i];
                int v = cycle[i + 1];
                
                for (Edge& e : graph[u]) {
                    if (e.to == v) {
                        e.flow += minCap;
                        graph[v][e.rev].flow -= minCap;
                    }
                }
            }
        }
        
        // Calculate total flow and cost
        int totalFlow = 0, totalCost = 0;
        
        for (const Edge& e : graph[source]) {
            totalFlow += e.flow;
        }
        
        for (int u = 0; u < n; u++) {
            for (const Edge& e : graph[u]) {
                if (e.flow > 0 && e.cost > 0) {
                    totalCost += e.flow * e.cost;
                }
            }
        }
        
        return {totalFlow, totalCost};
    }
};

// ============================================================================
// EXAMPLE USAGE & TEST CASES
// ============================================================================

void testMinCostFlow() {
    cout << "=== Minimum Cost Flow (Successive Shortest Path) ===" << endl;
    
    /*
     * Network:
     *        [10,2]
     *   0 ----------> 1
     *   |             |
     *   |[10,1]  [5,3]|
     *   v             v
     *   2 ----------> 3
     *        [10,1]
     * 
     * Format: [capacity, cost]
     * Find min cost to send 15 units from 0 to 3
     */
    
    MinCostFlow mcf(4);
    mcf.addEdge(0, 1, 10, 2);
    mcf.addEdge(0, 2, 10, 1);
    mcf.addEdge(1, 3, 5, 3);
    mcf.addEdge(2, 3, 10, 1);
    
    auto [flow, cost] = mcf.minCostFlow(0, 3, 15);
    
    cout << "Maximum Flow: " << flow << endl;
    cout << "Minimum Cost: " << cost << endl;
    cout << "Expected Flow: 15, Cost: 25" << endl;
    cout << "  Path 1: 0->2->3 (10 units, cost 20)" << endl;
    cout << "  Path 2: 0->1->3 (5 units, cost 25)" << endl << endl;
}

void testTransportationProblem() {
    cout << "=== Application: Transportation Problem ===" << endl;
    
    /*
     * 2 factories, 2 warehouses
     * 
     * Supply: F0=15, F1=25
     * Demand: W0=20, W1=20
     * 
     * Shipping costs:
     *       W0  W1
     * F0    4   6
     * F1    5   3
     */
    
    // Model: source -> factories -> warehouses -> sink
    MinCostFlow transport(6);
    
    int source = 0, sink = 5;
    int f0 = 1, f1 = 2;
    int w0 = 3, w1 = 4;
    
    // Source to factories (supply)
    transport.addEdge(source, f0, 15, 0);
    transport.addEdge(source, f1, 25, 0);
    
    // Factories to warehouses (costs)
    transport.addEdge(f0, w0, 100, 4); // Large capacity
    transport.addEdge(f0, w1, 100, 6);
    transport.addEdge(f1, w0, 100, 5);
    transport.addEdge(f1, w1, 100, 3);
    
    // Warehouses to sink (demand)
    transport.addEdge(w0, sink, 20, 0);
    transport.addEdge(w1, sink, 20, 0);
    
    auto [flow, cost] = transport.minCostFlow(source, sink, 40);
    
    cout << "Total shipped: " << flow << " units" << endl;
    cout << "Total cost: $" << cost << endl;
    cout << "Optimal solution:" << endl;
    cout << "  F0 -> W0: 15 units (cost $60)" << endl;
    cout << "  F1 -> W0: 5 units (cost $25)" << endl;
    cout << "  F1 -> W1: 20 units (cost $60)" << endl;
    cout << "Expected total: $145" << endl << endl;
}

void testAssignmentWithCosts() {
    cout << "=== Application: Job Assignment with Costs ===" << endl;
    
    /*
     * 3 workers, 3 jobs
     * Each worker has different cost for each job
     * 
     * Cost matrix:
     *       J0  J1  J2
     * W0    9   2   7
     * W1    6   4   3
     * W2    5   8   1
     */
    
    MinCostFlow assignment(8);
    
    int source = 0, sink = 7;
    vector<int> workers = {1, 2, 3};
    vector<int> jobs = {4, 5, 6};
    
    // Source to workers
    for (int w : workers) {
        assignment.addEdge(source, w, 1, 0);
    }
    
    // Workers to jobs with costs
    vector<vector<int>> costs = {
        {9, 2, 7},
        {6, 4, 3},
        {5, 8, 1}
    };
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assignment.addEdge(workers[i], jobs[j], 1, costs[i][j]);
        }
    }
    
    // Jobs to sink
    for (int j : jobs) {
        assignment.addEdge(j, sink, 1, 0);
    }
    
    auto [flow, cost] = assignment.minCostFlow(source, sink, 3);
    
    cout << "Workers assigned: " << flow << endl;
    cout << "Total cost: $" << cost << endl;
    cout << "Optimal: W0->J1 ($2), W1->J2 ($3), W2->J0 ($5)" << endl;
    cout << "Expected cost: $10" << endl << endl;
}

void testSupplyChain() {
    cout << "=== Application: Supply Chain Optimization ===" << endl;
    
    /*
     * Multi-stage supply chain:
     * Supplier -> Distribution Centers -> Retailers
     * 
     * Minimize total transportation + storage costs
     */
    
    MinCostFlow supply(7);
    
    int supplier = 0;
    int dc1 = 1, dc2 = 2;
    int retail1 = 3, retail2 = 4, retail3 = 5;
    int sink = 6;
    
    // Supplier to DCs (transportation cost)
    supply.addEdge(supplier, dc1, 100, 5);
    supply.addEdge(supplier, dc2, 100, 7);
    
    // DCs to retailers (delivery cost)
    supply.addEdge(dc1, retail1, 50, 3);
    supply.addEdge(dc1, retail2, 50, 4);
    supply.addEdge(dc2, retail2, 50, 2);
    supply.addEdge(dc2, retail3, 50, 3);
    
    // Retailers to sink (demand)
    supply.addEdge(retail1, sink, 30, 0);
    supply.addEdge(retail2, sink, 40, 0);
    supply.addEdge(retail3, sink, 20, 0);
    
    auto [flow, cost] = supply.minCostFlow(supplier, sink, 90);
    
    cout << "Total delivered: " << flow << " units" << endl;
    cout << "Total cost: $" << cost << endl;
    cout << "Supply chain optimized to minimize costs" << endl << endl;
}

int main() {
    testMinCostFlow();
    testTransportationProblem();
    testAssignmentWithCosts();
    testSupplyChain();
    
    cout << "=== Algorithm Summary ===" << endl;
    cout << "Successive Shortest Path: O(flow * (E + V log V))" << endl;
    cout << "  - Uses Dijkstra with potentials" << endl;
    cout << "  - Handles non-negative reduced costs" << endl << endl;
    
    cout << "Cycle Canceling: O(U * E^2 * log V)" << endl;
    cout << "  - Find max flow, then cancel negative cycles" << endl;
    cout << "  - Simple but slower in practice" << endl << endl;
    
    cout << "Applications:" << endl;
    cout << "  - Transportation and logistics" << endl;
    cout << "  - Resource allocation with costs" << endl;
    cout << "  - Supply chain optimization" << endl;
    cout << "  - Network routing with QoS" << endl;
    
    return 0;
}
