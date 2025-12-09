#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

// Directed Acyclic Graph (DAG) Algorithms
// Time Complexity: O(V + E)
// Space Complexity: O(V)

class DAG {
private:
    int V;
    std::vector<std::vector<int>> adj;
    
    void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& Stack) {
        visited[v] = true;
        
        for (int u : adj[v]) {
            if (!visited[u])
                topologicalSortUtil(u, visited, Stack);
        }
        
        Stack.push(v);
    }
    
public:
    DAG(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // Topological Sort using DFS
    std::vector<int> topologicalSortDFS() {
        std::stack<int> Stack;
        std::vector<bool> visited(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                topologicalSortUtil(i, visited, Stack);
        }
        
        std::vector<int> result;
        while (!Stack.empty()) {
            result.push_back(Stack.top());
            Stack.pop();
        }
        return result;
    }
    
    // Topological Sort using Kahn's Algorithm (BFS)
    std::vector<int> topologicalSortKahn() {
        std::vector<int> indegree(V, 0);
        
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }
        
        std::queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }
        
        std::vector<int> result;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);
            
            for (int v : adj[u]) {
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }
        
        if (result.size() != V) {
            std::cout << "Graph contains a cycle!" << std::endl;
            return {};
        }
        
        return result;
    }
    
    // Longest path in DAG
    std::vector<int> longestPath(int start) {
        std::vector<int> topo = topologicalSortDFS();
        std::vector<int> dist(V, INT_MIN);
        dist[start] = 0;
        
        for (int u : topo) {
            if (dist[u] != INT_MIN) {
                for (int v : adj[u]) {
                    dist[v] = std::max(dist[v], dist[u] + 1);
                }
            }
        }
        
        return dist;
    }
    
    // Check if DAG has a cycle (using Kahn's)
    bool hasCycle() {
        return topologicalSortKahn().size() != V;
    }
    
    // Count paths from source to destination
    int countPaths(int src, int dest) {
        std::vector<int> topo = topologicalSortDFS();
        std::vector<int> pathCount(V, 0);
        pathCount[src] = 1;
        
        for (int u : topo) {
            if (pathCount[u] > 0) {
                for (int v : adj[u]) {
                    pathCount[v] += pathCount[u];
                }
            }
        }
        
        return pathCount[dest];
    }
};

int main() {
    std::cout << "=== DAG Algorithms ===" << std::endl;
    std::cout << "Time: O(V+E), Space: O(V)" << std::endl << std::endl;
    
    DAG g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    
    std::cout << "Topological Sort (DFS): ";
    std::vector<int> topo1 = g.topologicalSortDFS();
    for (int v : topo1) std::cout << v << " ";
    std::cout << std::endl;
    
    std::cout << "Topological Sort (Kahn's BFS): ";
    std::vector<int> topo2 = g.topologicalSortKahn();
    for (int v : topo2) std::cout << v << " ";
    std::cout << std::endl;
    
    std::cout << "\nLongest path from vertex 5:" << std::endl;
    std::vector<int> dist = g.longestPath(5);
    for (int i = 0; i < dist.size(); i++) {
        if (dist[i] != INT_MIN)
            std::cout << "  To " << i << ": " << dist[i] << std::endl;
    }
    
    std::cout << "\nNumber of paths from 5 to 1: " << g.countPaths(5, 1) << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "  - Task scheduling with dependencies" << std::endl;
    std::cout << "  - Build systems (makefiles)" << std::endl;
    std::cout << "  - Course prerequisites" << std::endl;
    std::cout << "  - Program compilation order" << std::endl;
    
    return 0;
}
