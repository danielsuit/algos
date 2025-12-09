#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Quasi-Omnipotence: Problems solvable by clever reductions
// Demonstrates how complex problems reduce to known solvable ones
// Various time complexities depending on reduction

// Example 1: Vertex Cover -> Max Matching (König's theorem)
// Minimum vertex cover in bipartite graph = Maximum matching

class BipartiteGraph {
private:
    int U, V;
    std::vector<std::vector<int>> adj;
    
    bool bpm(int u, std::vector<bool>& visited, std::vector<int>& match) {
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                
                if (match[v] == -1 || bpm(match[v], visited, match)) {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    
public:
    BipartiteGraph(int u, int v) : U(u), V(v), adj(u) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    int maxMatching() {
        std::vector<int> match(V, -1);
        int result = 0;
        
        for (int u = 0; u < U; u++) {
            std::vector<bool> visited(V, false);
            if (bpm(u, visited, match))
                result++;
        }
        
        return result;
    }
    
    int minVertexCover() {
        // König's theorem: min vertex cover = max matching (bipartite)
        return maxMatching();
    }
};

// Example 2: SAT -> 3-SAT reduction
// Show how k-SAT reduces to 3-SAT

struct Clause {
    std::vector<int> literals; // positive = var, negative = -var
};

class SAT {
public:
    // Convert k-SAT clause to multiple 3-SAT clauses
    static std::vector<Clause> reduceTo3SAT(const Clause& clause) {
        std::vector<Clause> result;
        int k = clause.literals.size();
        
        if (k <= 3) {
            result.push_back(clause);
            return result;
        }
        
        // For clause (x1 v x2 v ... v xk), introduce variables y1, y2, ...
        // Convert to: (x1 v x2 v y1) ∧ (~y1 v x3 v y2) ∧ ... ∧ (~yk-3 v xk-1 v xk)
        
        int nextVar = 1000; // Assume original vars < 1000
        
        Clause first;
        first.literals = {clause.literals[0], clause.literals[1], nextVar};
        result.push_back(first);
        
        for (int i = 2; i < k - 2; i++) {
            Clause middle;
            middle.literals = {-nextVar, clause.literals[i], nextVar + 1};
            result.push_back(middle);
            nextVar++;
        }
        
        Clause last;
        last.literals = {-nextVar, clause.literals[k-2], clause.literals[k-1]};
        result.push_back(last);
        
        return result;
    }
};

// Example 3: Subset Sum -> Partition
// Partition problem reduces to Subset Sum

bool subsetSum(const std::vector<int>& arr, int target) {
    int n = arr.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
    
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= arr[i-1])
                dp[i][j] = dp[i][j] || dp[i-1][j - arr[i-1]];
        }
    }
    
    return dp[n][target];
}

bool canPartition(const std::vector<int>& arr) {
    int sum = 0;
    for (int x : arr) sum += x;
    
    if (sum % 2 != 0) return false;
    
    // Partition reduces to: subset sum with target = sum/2
    return subsetSum(arr, sum / 2);
}

// Example 4: Hamiltonian Path -> TSP
// TSP can be reduced to finding Hamiltonian path with specific weights

bool hasHamiltonianPath(const std::vector<std::vector<int>>& graph, int n) {
    // Using DP with bitmask
    std::vector<std::vector<bool>> dp(1 << n, std::vector<bool>(n, false));
    
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = true;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!dp[mask][i]) continue;
            
            for (int j = 0; j < n; j++) {
                if (graph[i][j] && !(mask & (1 << j))) {
                    dp[mask | (1 << j)][j] = true;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (dp[(1 << n) - 1][i])
            return true;
    }
    
    return false;
}

int main() {
    std::cout << "=== Quasi-Omnipotence: Problem Reductions ===" << std::endl << std::endl;
    
    // Example 1: Vertex Cover via Max Matching
    std::cout << "1. Min Vertex Cover (via Max Matching):" << std::endl;
    BipartiteGraph bg(3, 3);
    bg.addEdge(0, 0);
    bg.addEdge(0, 1);
    bg.addEdge(1, 1);
    bg.addEdge(1, 2);
    bg.addEdge(2, 2);
    
    std::cout << "   Max matching: " << bg.maxMatching() << std::endl;
    std::cout << "   Min vertex cover: " << bg.minVertexCover() << std::endl;
    
    // Example 2: Partition via Subset Sum
    std::cout << "\n2. Partition (via Subset Sum):" << std::endl;
    std::vector<int> arr = {1, 5, 11, 5};
    std::cout << "   Array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    std::cout << "   Can partition: " << (canPartition(arr) ? "Yes" : "No") << std::endl;
    
    // Example 3: k-SAT to 3-SAT
    std::cout << "\n3. k-SAT to 3-SAT Reduction:" << std::endl;
    Clause c;
    c.literals = {1, 2, 3, 4, 5}; // (x1 v x2 v x3 v x4 v x5)
    auto clauses = SAT::reduceTo3SAT(c);
    std::cout << "   Original clause size: " << c.literals.size() << std::endl;
    std::cout << "   Reduced to " << clauses.size() << " 3-SAT clauses" << std::endl;
    
    std::cout << "\nKey Reductions:" << std::endl;
    std::cout << "  - 3-SAT ≤p Independent Set" << std::endl;
    std::cout << "  - Independent Set ≤p Vertex Cover" << std::endl;
    std::cout << "  - Vertex Cover ≤p Set Cover" << std::endl;
    std::cout << "  - Hamiltonian Cycle ≤p TSP" << std::endl;
    std::cout << "  - 3-SAT ≤p Subset Sum" << std::endl;
    
    std::cout << "\nQuasi-Omnipotence Concept:" << std::endl;
    std::cout << "  - Many NP-complete problems reduce to each other" << std::endl;
    std::cout << "  - Solving one efficiently solves all" << std::endl;
    std::cout << "  - Forms equivalence classes of difficulty" << std::endl;
    
    return 0;
}
