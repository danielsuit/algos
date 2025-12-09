#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Tree Algorithms
// Time Complexity: varies by algorithm
// Space Complexity: O(V)

struct TreeNode {
    int val;
    std::vector<TreeNode*> children;
    TreeNode(int v) : val(v) {}
};

class Tree {
private:
    int V;
    std::vector<std::vector<int>> adj;
    
    int diameterUtil(int u, int parent, int& diameter) {
        int max1 = 0, max2 = 0;
        
        for (int v : adj[u]) {
            if (v != parent) {
                int h = diameterUtil(v, u, diameter);
                if (h > max1) {
                    max2 = max1;
                    max1 = h;
                } else if (h > max2) {
                    max2 = h;
                }
            }
        }
        
        diameter = std::max(diameter, max1 + max2);
        return max1 + 1;
    }
    
    void findCentersUtil(int u, int parent, std::vector<int>& subtreeSize) {
        subtreeSize[u] = 1;
        for (int v : adj[u]) {
            if (v != parent) {
                findCentersUtil(v, u, subtreeSize);
                subtreeSize[u] += subtreeSize[v];
            }
        }
    }
    
public:
    Tree(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Find diameter (longest path)
    int diameter() {
        int diam = 0;
        diameterUtil(0, -1, diam);
        return diam;
    }
    
    // Find height of tree
    int height(int root = 0) {
        std::vector<bool> visited(V, false);
        std::queue<std::pair<int, int>> q;
        q.push({root, 0});
        visited[root] = true;
        int maxHeight = 0;
        
        while (!q.empty()) {
            auto [u, h] = q.front();
            q.pop();
            maxHeight = std::max(maxHeight, h);
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push({v, h + 1});
                }
            }
        }
        return maxHeight;
    }
    
    // Level order traversal
    std::vector<std::vector<int>> levelOrder(int root = 0) {
        std::vector<std::vector<int>> result;
        std::vector<bool> visited(V, false);
        std::queue<int> q;
        q.push(root);
        visited[root] = true;
        
        while (!q.empty()) {
            int size = q.size();
            std::vector<int> level;
            
            for (int i = 0; i < size; i++) {
                int u = q.front();
                q.pop();
                level.push_back(u);
                
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            result.push_back(level);
        }
        return result;
    }
    
    // Find centers of tree (1 or 2 nodes)
    std::vector<int> findCenters() {
        std::vector<int> degree(V, 0);
        for (int u = 0; u < V; u++) {
            degree[u] = adj[u].size();
        }
        
        std::queue<int> leaves;
        for (int i = 0; i < V; i++) {
            if (degree[i] <= 1)
                leaves.push(i);
        }
        
        int remaining = V;
        while (remaining > 2) {
            int leafCount = leaves.size();
            remaining -= leafCount;
            
            for (int i = 0; i < leafCount; i++) {
                int leaf = leaves.front();
                leaves.pop();
                
                for (int neighbor : adj[leaf]) {
                    if (--degree[neighbor] == 1)
                        leaves.push(neighbor);
                }
            }
        }
        
        std::vector<int> centers;
        while (!leaves.empty()) {
            centers.push_back(leaves.front());
            leaves.pop();
        }
        return centers;
    }
    
    // Lowest Common Ancestor (Binary Lifting)
    std::vector<std::vector<int>> parent;
    std::vector<int> depth;
    
    void preprocessLCA(int root = 0) {
        int logV = 20;
        parent.assign(V, std::vector<int>(logV, -1));
        depth.assign(V, 0);
        
        std::function<void(int, int)> dfs = [&](int u, int p) {
            parent[u][0] = p;
            for (int i = 1; i < logV && parent[u][i-1] != -1; i++) {
                parent[u][i] = parent[parent[u][i-1]][i-1];
            }
            
            for (int v : adj[u]) {
                if (v != p) {
                    depth[v] = depth[u] + 1;
                    dfs(v, u);
                }
            }
        };
        
        dfs(root, -1);
    }
    
    int LCA(int u, int v) {
        if (depth[u] < depth[v]) std::swap(u, v);
        
        int diff = depth[u] - depth[v];
        for (int i = 0; i < 20; i++) {
            if ((diff >> i) & 1)
                u = parent[u][i];
        }
        
        if (u == v) return u;
        
        for (int i = 19; i >= 0; i--) {
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        
        return parent[u][0];
    }
};

int main() {
    std::cout << "=== Tree Algorithms ===" << std::endl << std::endl;
    
    Tree t(7);
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(1, 3);
    t.addEdge(1, 4);
    t.addEdge(2, 5);
    t.addEdge(2, 6);
    
    std::cout << "Tree diameter: " << t.diameter() << std::endl;
    std::cout << "Tree height: " << t.height(0) << std::endl;
    
    std::cout << "\nLevel order traversal:" << std::endl;
    auto levels = t.levelOrder(0);
    for (int i = 0; i < levels.size(); i++) {
        std::cout << "  Level " << i << ": ";
        for (int node : levels[i])
            std::cout << node << " ";
        std::cout << std::endl;
    }
    
    std::cout << "\nTree centers: ";
    auto centers = t.findCenters();
    for (int c : centers)
        std::cout << c << " ";
    std::cout << std::endl;
    
    t.preprocessLCA(0);
    std::cout << "\nLCA(3, 4): " << t.LCA(3, 4) << std::endl;
    std::cout << "LCA(3, 5): " << t.LCA(3, 5) << std::endl;
    
    return 0;
}
