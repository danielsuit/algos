#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// Dijkstra's Shortest Path Algorithm
// Time Complexity: O((V + E) log V) with priority queue
// Space Complexity: O(V)

class Graph {
private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj;  // {vertex, weight}
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }
    
    std::vector<int> dijkstra(int start) {
        std::vector<int> dist(V, INT_MAX);
        std::vector<int> parent(V, -1);
        
        // Min heap: {distance, vertex}
        std::priority_queue<std::pair<int, int>, 
                          std::vector<std::pair<int, int>>,
                          std::greater<std::pair<int, int>>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            
            if (d > dist[u]) continue;  // Already processed
            
            for (auto& [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    std::vector<int> getPath(int start, int end) {
        std::vector<int> parent(V, -1);
        std::vector<int> dist(V, INT_MAX);
        
        std::priority_queue<std::pair<int, int>,
                          std::vector<std::pair<int, int>>,
                          std::greater<std::pair<int, int>>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            for (auto& [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // Reconstruct path
        std::vector<int> path;
        if (dist[end] == INT_MAX) return path;
        
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());
        
        return path;
    }
};

int main() {
    std::cout << \"=== Dijkstra's Algorithm ===\" << std::endl;
    std::cout << \"Time: O((V+E) log V), Space: O(V)\" << std::endl << std::endl;
    
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);
    
    std::vector<int> distances = g.dijkstra(0);
    
    std::cout << \"Shortest distances from vertex 0:\" << std::endl;
    for (int i = 0; i < distances.size(); i++) {
        std::cout << \"  To \" << i << \": \" << distances[i] << std::endl;
    }
    
    std::cout << \"\\nShortest path from 0 to 5: \";
    std::vector<int> path = g.getPath(0, 5);
    for (int v : path) std::cout << v << \" \";
    std::cout << std::endl;
    
    return 0;
}
