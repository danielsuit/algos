#include <iostream>
#include <vector>
#include <list>
#include <stack>

// Depth-First Search (DFS)
// Time Complexity: O(V + E)
// Space Complexity: O(V)

class Graph {
private:
    int V;
    std::vector<std::list<int>> adj;
    
    void DFSUtil(int vertex, std::vector<bool>& visited) {
        visited[vertex] = true;
        std::cout << vertex << \" \";
        
        for (int neighbor : adj[vertex]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // Recursive DFS
    void DFS(int start) {
        std::vector<bool> visited(V, false);
        std::cout << \"DFS (recursive) from \" << start << \": \";
        DFSUtil(start, visited);
        std::cout << std::endl;
    }
    
    // Iterative DFS using stack
    void DFSIterative(int start) {
        std::vector<bool> visited(V, false);
        std::stack<int> stack;
        
        stack.push(start);
        std::cout << \"DFS (iterative) from \" << start << \": \";
        
        while (!stack.empty()) {
            int vertex = stack.top();
            stack.pop();
            
            if (!visited[vertex]) {
                visited[vertex] = true;
                std::cout << vertex << \" \";
                
                // Push neighbors in reverse to match recursive order
                for (auto it = adj[vertex].rbegin(); it != adj[vertex].rend(); ++it) {
                    if (!visited[*it]) {
                        stack.push(*it);
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    
    // DFS for all vertices (handles disconnected graph)
    void DFSComplete() {
        std::vector<bool> visited(V, false);
        std::cout << \"Complete DFS: \";
        
        for (int v = 0; v < V; v++) {
            if (!visited[v]) {
                DFSUtil(v, visited);
            }
        }
        std::cout << std::endl;
    }
    
    // Detect cycle in directed graph
    bool hasCycleUtil(int v, std::vector<bool>& visited, std::vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;
        
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (hasCycleUtil(neighbor, visited, recStack)) {
                    return true;
                }
            } else if (recStack[neighbor]) {
                return true;  // Back edge found
            }
        }
        
        recStack[v] = false;
        return false;
    }
    
    bool hasCycle() {
        std::vector<bool> visited(V, false);
        std::vector<bool> recStack(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (hasCycleUtil(i, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Count connected components
    int countComponents() {
        std::vector<bool> visited(V, false);
        int count = 0;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v]) {
                DFSUtil(v, visited);
                count++;
            }
        }
        
        return count;
    }
};

int main() {
    std::cout << \"=== Depth-First Search (DFS) ===\" << std::endl;
    std::cout << \"Time: O(V + E), Space: O(V)\" << std::endl << std::endl;
    
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    
    g.DFS(0);
    g.DFSIterative(0);
    
    std::cout << \"\\n=== Cycle Detection ===\" << std::endl;
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 1);  // Creates cycle
    
    std::cout << \"Has cycle: \" << (g2.hasCycle() ? \"Yes\" : \"No\") << std::endl;
    
    return 0;
}
