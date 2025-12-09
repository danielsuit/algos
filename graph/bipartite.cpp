#include <iostream>
#include <vector>
#include <queue>

// Bipartite Graph Check
// A graph is bipartite if it can be colored with 2 colors
// Time Complexity: O(V + E)
// Space Complexity: O(V)

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // BFS-based bipartite check
    bool isBipartiteBFS(int start, std::vector<int>& color) {
        std::queue<int> q;
        q.push(start);
        color[start] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;  // Same color -> not bipartite
                }
            }
        }
        return true;
    }
    
    // DFS-based bipartite check
    bool isBipartiteDFS(int u, int c, std::vector<int>& color) {
        color[u] = c;
        
        for (int v : adj[u]) {
            if (color[v] == -1) {
                if (!isBipartiteDFS(v, 1 - c, color))
                    return false;
            } else if (color[v] == color[u]) {
                return false;
            }
        }
        return true;
    }
    
    bool isBipartite() {
        std::vector<int> color(V, -1);
        
        // Check all components
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!isBipartiteBFS(i, color))
                    return false;
            }
        }
        return true;
    }
    
    bool isBipartiteDFSWrapper() {
        std::vector<int> color(V, -1);
        
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!isBipartiteDFS(i, 0, color))
                    return false;
            }
        }
        return true;
    }
};

int main() {
    std::cout << "=== Bipartite Graph Detection ===" << std::endl;
    std::cout << "Time: O(V+E), Space: O(V)" << std::endl << std::endl;
    
    // Example 1: Bipartite graph
    std::cout << "Graph 1 (Bipartite):" << std::endl;
    Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 3);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    std::cout << "  Is bipartite (BFS): " << (g1.isBipartite() ? "Yes" : "No") << std::endl;
    std::cout << "  Is bipartite (DFS): " << (g1.isBipartiteDFSWrapper() ? "Yes" : "No") << std::endl;
    
    // Example 2: Not bipartite (contains odd cycle)
    std::cout << "\nGraph 2 (Not Bipartite - Triangle):" << std::endl;
    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    std::cout << "  Is bipartite: " << (g2.isBipartite() ? "Yes" : "No") << std::endl;
    
    // Example 3: Bipartite (Tree)
    std::cout << "\nGraph 3 (Bipartite - Tree):" << std::endl;
    Graph g3(5);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    std::cout << "  Is bipartite: " << (g3.isBipartite() ? "Yes" : "No") << std::endl;
    
    std::cout << "\nKey Insight: A graph is bipartite iff it has no odd-length cycles" << std::endl;
    
    return 0;
}
