#include <iostream>
#include <vector>
#include <queue>
#include <list>

// Breadth-First Search (BFS)
// Time Complexity: O(V + E)
// Space Complexity: O(V)

class Graph {
private:
    int V;  // Number of vertices
    std::vector<std::list<int>> adj;  // Adjacency list
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // BFS from source vertex
    void BFS(int start) {
        std::vector<bool> visited(V, false);
        std::queue<int> queue;
        
        visited[start] = true;
        queue.push(start);
        
        std::cout << \"BFS traversal starting from \" << start << \": \";
        
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            std::cout << vertex << \" \";
            
            // Visit all adjacent vertices
            for (int neighbor : adj[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }
    
    // BFS with distance calculation
    std::vector<int> BFSDistance(int start) {
        std::vector<int> distance(V, -1);
        std::queue<int> queue;
        
        distance[start] = 0;
        queue.push(start);
        
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            
            for (int neighbor : adj[vertex]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[vertex] + 1;
                    queue.push(neighbor);
                }
            }
        }
        
        return distance;
    }
    
    // Check if path exists between two vertices
    bool hasPath(int start, int end) {
        if (start == end) return true;
        
        std::vector<bool> visited(V, false);
        std::queue<int> queue;
        
        visited[start] = true;
        queue.push(start);
        
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            
            for (int neighbor : adj[vertex]) {
                if (neighbor == end) return true;
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        
        return false;
    }
    
    // Find shortest path
    std::vector<int> shortestPath(int start, int end) {
        std::vector<int> parent(V, -1);
        std::vector<bool> visited(V, false);
        std::queue<int> queue;
        
        visited[start] = true;
        queue.push(start);
        
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            
            if (vertex == end) break;
            
            for (int neighbor : adj[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = vertex;
                    queue.push(neighbor);
                }
            }
        }
        
        // Reconstruct path
        std::vector<int> path;
        if (parent[end] == -1 && start != end) return path;  // No path
        
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());
        
        return path;
    }
};

int main() {
    std::cout << \"=== Breadth-First Search (BFS) ===\" << std::endl;
    std::cout << \"Time: O(V + E), Space: O(V)\" << std::endl << std::endl;
    
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    
    g.BFS(0);
    
    std::cout << \"\\nDistances from vertex 0:\" << std::endl;
    std::vector<int> distances = g.BFSDistance(0);
    for (int i = 0; i < distances.size(); i++) {
        std::cout << \"  To \" << i << \": \" << distances[i] << std::endl;
    }
    
    std::cout << \"\\nShortest path from 0 to 5: \";
    std::vector<int> path = g.shortestPath(0, 5);
    for (int v : path) std::cout << v << \" \";
    std::cout << std::endl;
    
    return 0;
}
