#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * MINIMUM CUT ALGORITHMS
 * 
 * Problem: Partition graph vertices into two sets S and T such that
 * the sum of edge capacities crossing the cut is minimized.
 * 
 * Max-Flow Min-Cut Theorem:
 * - Value of max flow = Capacity of min cut
 * - Min cut can be found after computing max flow
 * 
 * Applications:
 * - Network reliability
 * - Image segmentation
 * - Community detection
 * - Clustering
 */

// ============================================================================
// MIN CUT FROM MAX FLOW
// ============================================================================
/*
 * Time Complexity: O(V * E^2) - using Edmonds-Karp
 * Space Complexity: O(V^2)
 * 
 * Method:
 * 1. Compute max flow from s to t
 * 2. Find reachable vertices from s in residual graph
 * 3. Cut edges: from reachable to non-reachable
 */

class MinCutMaxFlow {
private:
    vector<vector<int>> capacity, originalCapacity;
    vector<vector<int>> adj;
    int n;
    
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
                    if (v == sink) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    
    int edmondsKarp(int source, int sink) {
        int totalFlow = 0;
        vector<int> parent(n);
        
        while (bfs(source, sink, parent)) {
            int pathFlow = INT_MAX;
            
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
            }
            
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= pathFlow;
                capacity[v][u] += pathFlow;
            }
            
            totalFlow += pathFlow;
        }
        
        return totalFlow;
    }
    
public:
    MinCutMaxFlow(int vertices) : n(vertices) {
        capacity.assign(n, vector<int>(n, 0));
        originalCapacity.assign(n, vector<int>(n, 0));
        adj.resize(n);
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        originalCapacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    pair<int, vector<pair<int, int>>> findMinCut(int source, int sink) {
        // Compute max flow
        int maxFlow = edmondsKarp(source, sink);
        
        // Find reachable vertices from source in residual graph
        vector<bool> reachable(n, false);
        queue<int> q;
        q.push(source);
        reachable[source] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!reachable[v] && capacity[u][v] > 0) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }
        
        // Collect edges in the cut
        vector<pair<int, int>> cutEdges;
        int cutCapacity = 0;
        
        for (int u = 0; u < n; u++) {
            if (reachable[u]) {
                for (int v : adj[u]) {
                    // Edge from reachable to non-reachable
                    if (!reachable[v] && originalCapacity[u][v] > 0) {
                        cutEdges.push_back({u, v});
                        cutCapacity += originalCapacity[u][v];
                    }
                }
            }
        }
        
        return {cutCapacity, cutEdges};
    }
    
    vector<int> getPartition(int source, int sink) {
        edmondsKarp(source, sink);
        
        vector<bool> reachable(n, false);
        queue<int> q;
        q.push(source);
        reachable[source] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!reachable[v] && capacity[u][v] > 0) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }
        
        vector<int> partition;
        for (int i = 0; i < n; i++) {
            if (reachable[i]) {
                partition.push_back(i);
            }
        }
        
        return partition;
    }
};

// ============================================================================
// STOER-WAGNER ALGORITHM (Global Min Cut)
// ============================================================================
/*
 * Time Complexity: O(V^3)
 * Space Complexity: O(V^2)
 * 
 * Finds minimum cut in undirected graph without specifying source/sink.
 * Uses minimum cut phase to iteratively merge vertices.
 * 
 * Key Idea: The last two vertices added in a phase define a cut
 */

class StoerWagner {
private:
    vector<vector<int>> graph;
    int n;
    
    // Find minimum cut phase
    pair<int, pair<int, int>> minimumCutPhase(vector<bool>& merged) {
        vector<int> weight(n, 0);
        vector<bool> added(n, false);
        
        int prev = -1, current = -1;
        
        // Add vertices in order of maximum connectivity
        for (int i = 0; i < n; i++) {
            if (merged[i]) continue;
            
            current = -1;
            int maxWeight = -1;
            
            // Find vertex with maximum weight to added set
            for (int j = 0; j < n; j++) {
                if (!merged[j] && !added[j] && weight[j] > maxWeight) {
                    maxWeight = weight[j];
                    current = j;
                }
            }
            
            if (current == -1) break;
            
            added[current] = true;
            
            // Update weights
            for (int j = 0; j < n; j++) {
                if (!merged[j] && !added[j]) {
                    weight[j] += graph[current][j];
                }
            }
            
            prev = current;
        }
        
        // Cut between last two vertices has weight = weight[current]
        return {weight[current], {prev, current}};
    }
    
    void merge(int s, int t) {
        // Merge t into s
        for (int i = 0; i < n; i++) {
            graph[s][i] += graph[t][i];
            graph[i][s] += graph[i][t];
        }
        graph[s][t] = graph[t][s] = 0;
    }
    
public:
    StoerWagner(int vertices) : n(vertices) {
        graph.assign(n, vector<int>(n, 0));
    }
    
    void addEdge(int u, int v, int weight) {
        graph[u][v] += weight;
        graph[v][u] += weight;
    }
    
    int globalMinCut() {
        vector<bool> merged(n, false);
        int minCut = INT_MAX;
        
        for (int phase = 0; phase < n - 1; phase++) {
            auto [cutWeight, vertices] = minimumCutPhase(merged);
            auto [s, t] = vertices;
            
            minCut = min(minCut, cutWeight);
            
            // Merge s and t
            merge(s, t);
            merged[t] = true;
        }
        
        return minCut;
    }
};

// ============================================================================
// KARGER'S RANDOMIZED MIN CUT
// ============================================================================
/*
 * Time Complexity: O(V^2) per iteration, O(V^4 log V) for high probability
 * Space Complexity: O(V + E)
 * 
 * Randomized algorithm that contracts random edges.
 * Run multiple times and take minimum.
 * 
 * Probability of success: >= 1/C(n,2) per iteration
 */

class KargerMinCut {
private:
    struct Edge {
        int u, v;
        int weight;
    };
    
    vector<Edge> edges;
    int n;
    
    // Union-Find for contraction
    vector<int> parent, rank;
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
    
    int contractGraph() {
        parent.resize(n);
        rank.assign(n, 0);
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        int vertices = n;
        
        // Contract until 2 vertices remain
        while (vertices > 2) {
            // Pick random edge
            int idx = rand() % edges.size();
            Edge& e = edges[idx];
            
            int set1 = find(e.u);
            int set2 = find(e.v);
            
            if (set1 != set2) {
                unite(set1, set2);
                vertices--;
            }
        }
        
        // Count edges between two remaining components
        int cutWeight = 0;
        for (const Edge& e : edges) {
            if (find(e.u) != find(e.v)) {
                cutWeight += e.weight;
            }
        }
        
        return cutWeight;
    }
    
public:
    KargerMinCut(int vertices) : n(vertices) {}
    
    void addEdge(int u, int v, int weight = 1) {
        edges.push_back({u, v, weight});
    }
    
    int findMinCut(int iterations = -1) {
        if (iterations == -1) {
            // Run O(n^2 log n) times for high probability
            iterations = n * n * log(n);
        }
        
        int minCut = INT_MAX;
        
        for (int i = 0; i < iterations; i++) {
            int cut = contractGraph();
            minCut = min(minCut, cut);
        }
        
        return minCut;
    }
};

// ============================================================================
// EXAMPLE USAGE & TEST CASES
// ============================================================================

void testMinCutMaxFlow() {
    cout << "=== Min Cut from Max Flow ===" << endl;
    
    MinCutMaxFlow mcmf(6);
    mcmf.addEdge(0, 1, 16);
    mcmf.addEdge(0, 2, 13);
    mcmf.addEdge(1, 2, 10);
    mcmf.addEdge(1, 3, 12);
    mcmf.addEdge(2, 1, 4);
    mcmf.addEdge(2, 4, 14);
    mcmf.addEdge(3, 2, 9);
    mcmf.addEdge(3, 5, 20);
    mcmf.addEdge(4, 3, 7);
    mcmf.addEdge(4, 5, 4);
    
    auto [cutCapacity, cutEdges] = mcmf.findMinCut(0, 5);
    
    cout << "Minimum Cut Capacity: " << cutCapacity << endl;
    cout << "Cut Edges: ";
    for (auto [u, v] : cutEdges) {
        cout << "(" << u << "->" << v << ") ";
    }
    cout << endl;
    
    auto partition = mcmf.getPartition(0, 5);
    cout << "Source partition: {";
    for (int v : partition) {
        cout << v << " ";
    }
    cout << "}" << endl << endl;
}

void testStoerWagner() {
    cout << "=== Stoer-Wagner Global Min Cut ===" << endl;
    
    StoerWagner sw(4);
    sw.addEdge(0, 1, 2);
    sw.addEdge(0, 2, 3);
    sw.addEdge(1, 2, 2);
    sw.addEdge(1, 3, 2);
    sw.addEdge(2, 3, 1);
    
    int minCut = sw.globalMinCut();
    cout << "Global Minimum Cut: " << minCut << endl;
    cout << "Expected: 3" << endl << endl;
}

void testKargerMinCut() {
    cout << "=== Karger's Randomized Min Cut ===" << endl;
    
    srand(42); // For reproducibility
    
    KargerMinCut karger(4);
    karger.addEdge(0, 1, 2);
    karger.addEdge(0, 2, 3);
    karger.addEdge(1, 2, 2);
    karger.addEdge(1, 3, 2);
    karger.addEdge(2, 3, 1);
    
    int minCut = karger.findMinCut(100); // Run 100 iterations
    cout << "Minimum Cut (randomized): " << minCut << endl;
    cout << "Expected: ~3 (probabilistic)" << endl << endl;
}

void testImageSegmentation() {
    cout << "=== Application: Image Segmentation ===" << endl;
    
    /*
     * Simple 2x2 grid of pixels
     * Find minimum cut to segment into foreground/background
     * 
     * Grid:  0 - 1
     *        |   |
     *        2 - 3
     * 
     * Add source (4) and sink (5)
     * High capacity to likely foreground/background
     */
    
    MinCutMaxFlow seg(6);
    
    // Source to potential foreground (0, 1)
    seg.addEdge(4, 0, 100); // Strong foreground evidence
    seg.addEdge(4, 1, 50);
    
    // Potential background to sink (2, 3)
    seg.addEdge(2, 5, 80);
    seg.addEdge(3, 5, 100); // Strong background evidence
    
    // Pixel similarity (low = similar, high = boundary)
    seg.addEdge(0, 1, 5);  // Similar
    seg.addEdge(0, 2, 20); // Boundary
    seg.addEdge(1, 3, 15); // Boundary
    seg.addEdge(2, 3, 5);  // Similar
    
    auto partition = seg.getPartition(4, 5);
    cout << "Foreground pixels: {";
    for (int v : partition) {
        if (v != 4) cout << v << " ";
    }
    cout << "}" << endl;
    cout << "Background pixels: {remaining}" << endl << endl;
}

int main() {
    testMinCutMaxFlow();
    testStoerWagner();
    testKargerMinCut();
    testImageSegmentation();
    
    cout << "=== Algorithm Summary ===" << endl;
    cout << "Min Cut from Max Flow: O(V * E^2)" << endl;
    cout << "  - Best for directed graphs with source/sink" << endl;
    cout << "  - Uses max-flow min-cut theorem" << endl << endl;
    
    cout << "Stoer-Wagner: O(V^3)" << endl;
    cout << "  - Global min cut in undirected graphs" << endl;
    cout << "  - Deterministic algorithm" << endl << endl;
    
    cout << "Karger's Algorithm: O(V^2) per iteration" << endl;
    cout << "  - Randomized, simple to implement" << endl;
    cout << "  - Run multiple times for confidence" << endl;
    
    return 0;
}
