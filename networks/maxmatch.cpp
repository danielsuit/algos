#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

/*
 * MAXIMUM MATCHING ALGORITHMS
 * 
 * Problem: Find maximum set of edges with no common vertices.
 * 
 * Types:
 * 1. Bipartite Matching - matching in bipartite graphs
 * 2. General Matching - matching in arbitrary graphs (Edmonds' Blossom)
 * 
 * Applications:
 * - Job assignment
 * - Marriage problem
 * - Resource allocation
 * - Network routing
 */

// ============================================================================
// HUNGARIAN ALGORITHM (Kuhn's Algorithm) - Bipartite Matching
// ============================================================================
/*
 * Time Complexity: O(V * E)
 * Space Complexity: O(V + E)
 * 
 * Method:
 * - Use DFS to find augmenting paths
 * - Alternating paths: unmatched -> matched -> unmatched -> ...
 * - Flip matching along augmenting path
 */

class HungarianMatching {
private:
    vector<vector<int>> adj;
    vector<int> match;
    vector<bool> visited;
    int leftSize, rightSize;
    
    // Try to find augmenting path from u
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            
            // If v is unmatched or we can find augmenting path from match[v]
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }
    
public:
    HungarianMatching(int left, int right) 
        : leftSize(left), rightSize(right) {
        adj.resize(leftSize);
        match.assign(rightSize, -1);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    int maxMatching() {
        int matching = 0;
        
        // Try to match each left vertex
        for (int u = 0; u < leftSize; u++) {
            visited.assign(rightSize, false);
            if (dfs(u)) {
                matching++;
            }
        }
        
        return matching;
    }
    
    vector<pair<int, int>> getMatching() {
        maxMatching();
        vector<pair<int, int>> result;
        
        for (int v = 0; v < rightSize; v++) {
            if (match[v] != -1) {
                result.push_back({match[v], v});
            }
        }
        
        return result;
    }
};

// ============================================================================
// HOPCROFT-KARP ALGORITHM - Fast Bipartite Matching
// ============================================================================
/*
 * Time Complexity: O(E * sqrt(V))
 * Space Complexity: O(V + E)
 * 
 * Improvement over Hungarian:
 * - Finds multiple augmenting paths in each phase
 * - Uses BFS to build level graph
 * - Uses DFS to find paths
 */

class HopcroftKarp {
private:
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;
    int leftSize, rightSize;
    const int INF = 1e9;
    
    // Build level graph using BFS
    bool bfs() {
        queue<int> q;
        
        // Add all unmatched left vertices
        for (int u = 0; u < leftSize; u++) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        
        dist[leftSize] = INF; // NIL vertex
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (dist[u] < dist[leftSize]) {
                for (int v : adj[u]) {
                    int next = (pairV[v] == -1) ? leftSize : pairV[v];
                    
                    if (dist[next] == INF) {
                        dist[next] = dist[u] + 1;
                        if (next != leftSize) {
                            q.push(next);
                        }
                    }
                }
            }
        }
        
        return dist[leftSize] != INF;
    }
    
    // DFS to find augmenting path
    bool dfs(int u) {
        if (u != leftSize) {
            for (int v : adj[u]) {
                int next = (pairV[v] == -1) ? leftSize : pairV[v];
                
                if (dist[next] == dist[u] + 1 && dfs(next)) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
            
            dist[u] = INF;
            return false;
        }
        return true;
    }
    
public:
    HopcroftKarp(int left, int right) 
        : leftSize(left), rightSize(right) {
        adj.resize(leftSize);
        pairU.assign(leftSize, -1);
        pairV.assign(rightSize, -1);
        dist.resize(leftSize + 1);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    int maxMatching() {
        int matching = 0;
        
        // While there exists augmenting path
        while (bfs()) {
            // Find all augmenting paths
            for (int u = 0; u < leftSize; u++) {
                if (pairU[u] == -1 && dfs(u)) {
                    matching++;
                }
            }
        }
        
        return matching;
    }
    
    vector<pair<int, int>> getMatching() {
        maxMatching();
        vector<pair<int, int>> result;
        
        for (int u = 0; u < leftSize; u++) {
            if (pairU[u] != -1) {
                result.push_back({u, pairU[u]});
            }
        }
        
        return result;
    }
};

// ============================================================================
// MAXIMUM WEIGHTED BIPARTITE MATCHING (Assignment Problem)
// ============================================================================
/*
 * Time Complexity: O(V^3)
 * Space Complexity: O(V^2)
 * 
 * Hungarian Algorithm for weighted matching.
 * Finds maximum weight matching in complete bipartite graph.
 */

class WeightedMatching {
private:
    vector<vector<int>> cost;
    vector<int> lx, ly;
    vector<int> match;
    vector<bool> visitedX, visitedY;
    int n;
    const int INF = 1e9;
    
    // Try to find augmenting path from x
    bool dfs(int x) {
        visitedX[x] = true;
        
        for (int y = 0; y < n; y++) {
            if (visitedY[y]) continue;
            
            int slack = lx[x] + ly[y] - cost[x][y];
            
            if (slack == 0) {
                visitedY[y] = true;
                
                if (match[y] == -1 || dfs(match[y])) {
                    match[y] = x;
                    return true;
                }
            }
        }
        
        return false;
    }
    
public:
    WeightedMatching(int size) : n(size) {
        cost.assign(n, vector<int>(n, 0));
        lx.resize(n);
        ly.assign(n, 0);
        match.assign(n, -1);
    }
    
    void setCost(int x, int y, int w) {
        cost[x][y] = w;
    }
    
    int maxWeightMatching() {
        // Initialize labels
        for (int x = 0; x < n; x++) {
            lx[x] = *max_element(cost[x].begin(), cost[x].end());
        }
        
        // Find maximum matching
        for (int x = 0; x < n; x++) {
            while (true) {
                visitedX.assign(n, false);
                visitedY.assign(n, false);
                
                if (dfs(x)) break;
                
                // Update labels
                int delta = INF;
                for (int i = 0; i < n; i++) {
                    if (visitedX[i]) {
                        for (int j = 0; j < n; j++) {
                            if (!visitedY[j]) {
                                delta = min(delta, lx[i] + ly[j] - cost[i][j]);
                            }
                        }
                    }
                }
                
                for (int i = 0; i < n; i++) {
                    if (visitedX[i]) lx[i] -= delta;
                    if (visitedY[i]) ly[i] += delta;
                }
            }
        }
        
        // Calculate total weight
        int totalWeight = 0;
        for (int y = 0; y < n; y++) {
            if (match[y] != -1) {
                totalWeight += cost[match[y]][y];
            }
        }
        
        return totalWeight;
    }
    
    vector<pair<int, int>> getMatching() {
        maxWeightMatching();
        vector<pair<int, int>> result;
        
        for (int y = 0; y < n; y++) {
            if (match[y] != -1) {
                result.push_back({match[y], y});
            }
        }
        
        return result;
    }
};

// ============================================================================
// EXAMPLE USAGE & TEST CASES
// ============================================================================

void testHungarianMatching() {
    cout << "=== Hungarian Algorithm (Kuhn's) ===" << endl;
    
    /*
     * Bipartite graph:
     * Left = {0, 1, 2}
     * Right = {0, 1, 2}
     * Edges: 0-0, 0-1, 1-0, 1-2, 2-1, 2-2
     */
    
    HungarianMatching hm(3, 3);
    hm.addEdge(0, 0);
    hm.addEdge(0, 1);
    hm.addEdge(1, 0);
    hm.addEdge(1, 2);
    hm.addEdge(2, 1);
    hm.addEdge(2, 2);
    
    int maxMatch = hm.maxMatching();
    cout << "Maximum Matching Size: " << maxMatch << endl;
    
    auto matching = hm.getMatching();
    cout << "Matching Edges: ";
    for (auto [u, v] : matching) {
        cout << "(" << u << "-" << v << ") ";
    }
    cout << endl << endl;
}

void testHopcroftKarp() {
    cout << "=== Hopcroft-Karp Algorithm ===" << endl;
    
    HopcroftKarp hk(4, 4);
    hk.addEdge(0, 0);
    hk.addEdge(0, 1);
    hk.addEdge(1, 1);
    hk.addEdge(1, 2);
    hk.addEdge(2, 2);
    hk.addEdge(2, 3);
    hk.addEdge(3, 0);
    hk.addEdge(3, 3);
    
    int maxMatch = hk.maxMatching();
    cout << "Maximum Matching Size: " << maxMatch << endl;
    
    auto matching = hk.getMatching();
    cout << "Matching Edges: ";
    for (auto [u, v] : matching) {
        cout << "(" << u << "-" << v << ") ";
    }
    cout << endl << endl;
}

void testWeightedMatching() {
    cout << "=== Weighted Bipartite Matching ===" << endl;
    
    /*
     * Assignment problem:
     * Workers = {0, 1, 2}
     * Tasks = {0, 1, 2}
     * Cost matrix (profit):
     *     T0  T1  T2
     * W0  10  15   9
     * W1  15  12   8
     * W2  11  13  10
     */
    
    WeightedMatching wm(3);
    wm.setCost(0, 0, 10);
    wm.setCost(0, 1, 15);
    wm.setCost(0, 2, 9);
    wm.setCost(1, 0, 15);
    wm.setCost(1, 1, 12);
    wm.setCost(1, 2, 8);
    wm.setCost(2, 0, 11);
    wm.setCost(2, 1, 13);
    wm.setCost(2, 2, 10);
    
    int maxWeight = wm.maxWeightMatching();
    cout << "Maximum Total Weight: " << maxWeight << endl;
    
    auto matching = wm.getMatching();
    cout << "Optimal Assignment: ";
    for (auto [worker, task] : matching) {
        cout << "W" << worker << "->T" << task << " ";
    }
    cout << endl << endl;
}

void testJobAssignment() {
    cout << "=== Application: Job Assignment ===" << endl;
    
    /*
     * 3 employees, 4 tasks
     * Each employee can do certain tasks
     * Find maximum assignment
     */
    
    HungarianMatching jobs(3, 4);
    
    // Employee 0 can do tasks 0, 1
    jobs.addEdge(0, 0);
    jobs.addEdge(0, 1);
    
    // Employee 1 can do tasks 1, 2, 3
    jobs.addEdge(1, 1);
    jobs.addEdge(1, 2);
    jobs.addEdge(1, 3);
    
    // Employee 2 can do tasks 2, 3
    jobs.addEdge(2, 2);
    jobs.addEdge(2, 3);
    
    int assigned = jobs.maxMatching();
    cout << "Employees assigned: " << assigned << " / 3" << endl;
    
    auto assignment = jobs.getMatching();
    for (auto [emp, task] : assignment) {
        cout << "Employee " << emp << " -> Task " << task << endl;
    }
    cout << endl;
}

void testMarriageProblem() {
    cout << "=== Application: Stable Marriage Preview ===" << endl;
    
    /*
     * Men = {0, 1, 2}
     * Women = {0, 1, 2}
     * Find maximum matching (not necessarily stable)
     */
    
    HopcroftKarp marriage(3, 3);
    
    // Each man proposes to compatible women
    marriage.addEdge(0, 0);
    marriage.addEdge(0, 1);
    marriage.addEdge(1, 1);
    marriage.addEdge(1, 2);
    marriage.addEdge(2, 0);
    marriage.addEdge(2, 2);
    
    int couples = marriage.maxMatching();
    cout << "Maximum Matching: " << couples << " couples" << endl;
    
    auto matches = marriage.getMatching();
    for (auto [man, woman] : matches) {
        cout << "Man " << man << " - Woman " << woman << endl;
    }
    cout << "\nNote: This is maximum matching, not stable matching!" << endl;
    cout << "Stable marriage requires preference lists." << endl << endl;
}

int main() {
    testHungarianMatching();
    testHopcroftKarp();
    testWeightedMatching();
    testJobAssignment();
    testMarriageProblem();
    
    cout << "=== Algorithm Comparison ===" << endl;
    cout << "Hungarian (Kuhn): O(V * E)" << endl;
    cout << "  - Simple DFS-based approach" << endl;
    cout << "  - Good for sparse graphs" << endl << endl;
    
    cout << "Hopcroft-Karp: O(E * sqrt(V))" << endl;
    cout << "  - Fastest for unweighted bipartite matching" << endl;
    cout << "  - Uses BFS + DFS" << endl << endl;
    
    cout << "Weighted Matching: O(V^3)" << endl;
    cout << "  - Solves assignment problem" << endl;
    cout << "  - Maximizes total weight" << endl;
    
    return 0;
}