#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>

// Topological Sort using DFS
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Only valid for Directed Acyclic Graphs (DAGs)

class Graph {
private:
    int V;
    std::vector<std::list<int>> adj;
    
    void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& stack) {
        visited[v] = true;
        
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, stack);
            }
        }
        
        stack.push(v);  // Push after visiting all descendants
    }
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    std::vector<int> topologicalSort() {
        std::stack<int> stack;
        std::vector<bool> visited(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, stack);
            }
        }
        
        std::vector<int> result;
        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
        
        return result;
    }
    
    // Kahn's algorithm (BFS-based)
    std::vector<int> topologicalSortBFS() {
        std::vector<int> inDegree(V, 0);
        
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }
        
        std::queue<int> queue;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                queue.push(i);
            }
        }
        
        std::vector<int> result;
        
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            result.push_back(u);
            
            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue.push(v);
                }
            }
        }
        
        return result;
    }
};

int main() {
    std::cout << "=== Topological Sort ===" << std::endl;
    std::cout << "Time: O(V + E), Space: O(V)" << std::endl << std::endl;
    
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    
    std::cout << "DFS-based topological sort: ";
    std::vector<int> order = g.topologicalSort();
    for (int v : order) std::cout << v << " ";
    std::cout << std::endl;
    
    std::cout << "BFS-based (Kahn's) topological sort: ";
    order = g.topologicalSortBFS();
    for (int v : order) std::cout << v << " ";
    std::cout << std::endl;
    
    return 0;
}