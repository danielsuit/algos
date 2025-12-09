#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

/*
 * MAXIMUM FLOW ALGORITHMS
 * 
 * Problem: Given a directed graph with capacities on edges, find maximum flow
 * from source to sink such that:
 * 1. Flow on edge doesn't exceed capacity
 * 2. Flow conservation at all nodes except source/sink
 * 
 * Applications:
 * - Network routing
 * - Bipartite matching
 * - Project selection
 * - Image segmentation
 */

// ============================================================================
// FORD-FULKERSON METHOD (using DFS)
// ============================================================================
/*
 * Time Complexity: O(E * max_flow) - pseudopolynomial
 * Space Complexity: O(V^2) for adjacency matrix
 * 
 * Method:
 * 1. Start with zero flow
 * 2. While there exists augmenting path from s to t:
 *    - Find path using DFS
 *    - Augment flow along path
 * 3. Return total flow
 * 
 * Note: May not terminate with irrational capacities!
 */

class FordFulkerson {
private:
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    int n;
    
    // DFS to find augmenting path
    bool dfs(int u, int sink, vector<int>& parent, vector<bool>& visited) {
        if (u == sink) return true;
        
        visited[u] = true;
        
        for (int v : adj[u]) {
            // Check if there's remaining capacity and not visited
            if (!visited[v] && capacity[u][v] > 0) {
                parent[v] = u;
                if (dfs(v, sink, parent, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    
public:
    FordFulkerson(int vertices) : n(vertices) {
        capacity.assign(n, vector<int>(n, 0));
        adj.resize(n);
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // For residual graph
    }
    
    int maxFlow(int source, int sink) {
        int totalFlow = 0;
        vector<int> parent(n);
        
        // While there exists augmenting path
        while (true) {
            vector<bool> visited(n, false);
            parent.assign(n, -1);
            
            if (!dfs(source, sink, parent, visited)) {
                break; // No more augmenting paths
            }
            
            // Find minimum residual capacity along path
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
            }
            
            // Update residual capacities
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= pathFlow;
                capacity[v][u] += pathFlow; // Reverse edge
            }
            
            totalFlow += pathFlow;
        }
        
        return totalFlow;
    }
};

// ============================================================================
// EDMONDS-KARP ALGORITHM (BFS-based)
// ============================================================================
/*
 * Time Complexity: O(V * E^2)
 * Space Complexity: O(V^2)
 * 
 * Improvement over Ford-Fulkerson:
 * - Uses BFS to find shortest augmenting path
 * - Guarantees polynomial time
 * - More efficient in practice
 * 
 * Key Insight: Number of augmentations is O(VE)
 */

class EdmondsKarp {
private:
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    int n;
    
    // BFS to find shortest augmenting path
    bool bfs(int source, int sink, vector<int>& parent) {
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!visited[v] && capacity[u][v] > 0) {
                    visited[v] = true;
                    parent[v] = u;
                    
                    if (v == sink) {
                        return true; // Found path
                    }
                    q.push(v);
                }
            }
        }
        
        return false; // No path found
    }
    
public:
    EdmondsKarp(int vertices) : n(vertices) {
        capacity.assign(n, vector<int>(n, 0));
        adj.resize(n);
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int maxFlow(int source, int sink) {
        int totalFlow = 0;
        vector<int> parent(n);
        
        // While BFS finds augmenting path
        while (bfs(source, sink, parent)) {
            // Find minimum capacity along path
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
            }
            
            // Update residual graph
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= pathFlow;
                capacity[v][u] += pathFlow;
            }
            
            totalFlow += pathFlow;
        }
        
        return totalFlow;
    }
    
    // Get minimum cut
    vector<pair<int, int>> getMinCut(int source) {
        vector<pair<int, int>> minCut;
        vector<bool> visited(n, false);
        
        // BFS from source in residual graph
        queue<int> q;
        q.push(source);
        visited[source] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!visited[v] && capacity[u][v] > 0) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        // Edges from visited to unvisited form min cut
        for (int u = 0; u < n; u++) {
            if (visited[u]) {
                for (int v : adj[u]) {
                    if (!visited[v] && capacity[u][v] == 0) {
                        // This edge is in min cut (capacity exhausted)
                        minCut.push_back({u, v});
                    }
                }
            }
        }
        
        return minCut;
    }
};

// ============================================================================
// DINIC'S ALGORITHM
// ============================================================================
/*
 * Time Complexity: O(V^2 * E)
 * Space Complexity: O(V + E)
 * 
 * Improvements:
 * - Uses level graph (BFS)
 * - Multiple blocking flows per iteration
 * - Very efficient for unit capacity graphs: O(E * sqrt(V))
 * 
 * Best general-purpose max flow algorithm
 */

class Dinic {
private:
    struct Edge {
        int to, rev;
        int cap;
    };
    
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    int n;
    
    // Build level graph using BFS
    bool bfs(int source, int sink) {
        level.assign(n, -1);
        level[source] = 0;
        
        queue<int> q;
        q.push(source);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto& e : graph[u]) {
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        
        return level[sink] >= 0;
    }
    
    // Send flow using DFS
    int dfs(int u, int sink, int pushed) {
        if (u == sink) return pushed;
        
        for (int& i = iter[u]; i < graph[u].size(); i++) {
            Edge& e = graph[u][i];
            
            if (level[u] + 1 == level[e.to] && e.cap > 0) {
                int flow = dfs(e.to, sink, min(pushed, e.cap));
                
                if (flow > 0) {
                    e.cap -= flow;
                    graph[e.to][e.rev].cap += flow;
                    return flow;
                }
            }
        }
        
        return 0;
    }
    
public:
    Dinic(int vertices) : n(vertices) {
        graph.resize(n);
        level.resize(n);
        iter.resize(n);
    }
    
    void addEdge(int u, int v, int cap) {
        graph[u].push_back({v, (int)graph[v].size(), cap});
        graph[v].push_back({u, (int)graph[u].size() - 1, 0}); // Reverse edge
    }
    
    int maxFlow(int source, int sink) {
        int totalFlow = 0;
        
        // While level graph exists
        while (bfs(source, sink)) {
            iter.assign(n, 0);
            
            // Send multiple blocking flows
            while (int pushed = dfs(source, sink, INT_MAX)) {
                totalFlow += pushed;
            }
        }
        
        return totalFlow;
    }
};

// ============================================================================
// EXAMPLE USAGE & TEST CASES
// ============================================================================

void testFordFulkerson() {
    cout << "=== Ford-Fulkerson Algorithm ===" << endl;
    
    /*
     * Graph:
     *        10
     *   0 ------> 1
     *   |    5  / |  6
     *   |15   /   |
     *   v  v/     v
     *   2 ------> 3
     *       10
     * 
     * Max flow from 0 to 3 = 15
     */
    
    FordFulkerson ff(4);
    ff.addEdge(0, 1, 10);
    ff.addEdge(0, 2, 15);
    ff.addEdge(1, 2, 5);
    ff.addEdge(1, 3, 6);
    ff.addEdge(2, 3, 10);
    
    int maxFlow = ff.maxFlow(0, 3);
    cout << "Maximum Flow: " << maxFlow << endl;
    cout << "Expected: 15" << endl << endl;
}

void testEdmondsKarp() {
    cout << "=== Edmonds-Karp Algorithm ===" << endl;
    
    EdmondsKarp ek(6);
    ek.addEdge(0, 1, 16);
    ek.addEdge(0, 2, 13);
    ek.addEdge(1, 2, 10);
    ek.addEdge(1, 3, 12);
    ek.addEdge(2, 1, 4);
    ek.addEdge(2, 4, 14);
    ek.addEdge(3, 2, 9);
    ek.addEdge(3, 5, 20);
    ek.addEdge(4, 3, 7);
    ek.addEdge(4, 5, 4);
    
    int maxFlow = ek.maxFlow(0, 5);
    cout << "Maximum Flow: " << maxFlow << endl;
    cout << "Expected: 23" << endl;
    
    auto minCut = ek.getMinCut(0);
    cout << "Minimum Cut Edges: ";
    for (auto [u, v] : minCut) {
        cout << "(" << u << "->" << v << ") ";
    }
    cout << endl << endl;
}

void testDinic() {
    cout << "=== Dinic's Algorithm ===" << endl;
    
    Dinic dinic(4);
    dinic.addEdge(0, 1, 10);
    dinic.addEdge(0, 2, 10);
    dinic.addEdge(1, 2, 2);
    dinic.addEdge(1, 3, 4);
    dinic.addEdge(2, 3, 9);
    
    int maxFlow = dinic.maxFlow(0, 3);
    cout << "Maximum Flow: " << maxFlow << endl;
    cout << "Expected: 13" << endl << endl;
}

void testBipartiteMatching() {
    cout << "=== Bipartite Matching via Max Flow ===" << endl;
    
    /*
     * Bipartite graph matching:
     * Left: {0, 1, 2}
     * Right: {3, 4, 5}
     * Edges: 0-3, 0-4, 1-4, 1-5, 2-5
     * 
     * Convert to max flow:
     * - Add source connected to all left nodes (capacity 1)
     * - Add sink connected from all right nodes (capacity 1)
     * - Original edges have capacity 1
     */
    
    Dinic dinic(8); // source=6, sink=7
    
    // Source to left nodes
    dinic.addEdge(6, 0, 1);
    dinic.addEdge(6, 1, 1);
    dinic.addEdge(6, 2, 1);
    
    // Bipartite edges
    dinic.addEdge(0, 3, 1);
    dinic.addEdge(0, 4, 1);
    dinic.addEdge(1, 4, 1);
    dinic.addEdge(1, 5, 1);
    dinic.addEdge(2, 5, 1);
    
    // Right nodes to sink
    dinic.addEdge(3, 7, 1);
    dinic.addEdge(4, 7, 1);
    dinic.addEdge(5, 7, 1);
    
    int maxMatching = dinic.maxFlow(6, 7);
    cout << "Maximum Matching Size: " << maxMatching << endl;
    cout << "Expected: 3" << endl << endl;
}

int main() {
    testFordFulkerson();
    testEdmondsKarp();
    testDinic();
    testBipartiteMatching();
    
    cout << "=== Algorithm Comparison ===" << endl;
    cout << "Ford-Fulkerson: O(E * f) - f is max flow" << endl;
    cout << "Edmonds-Karp: O(V * E^2)" << endl;
    cout << "Dinic: O(V^2 * E)" << endl;
    cout << "\nDinic is generally fastest for dense graphs." << endl;
    cout << "Edmonds-Karp is simpler to implement and understand." << endl;
    
    return 0;
}
