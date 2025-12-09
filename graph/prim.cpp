#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// Prim's Minimum Spanning Tree Algorithm
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
        adj[v].push_back({u, weight});  // Undirected
    }
    
    int primMST() {
        std::vector<bool> inMST(V, false);
        std::vector<int> key(V, INT_MAX);
        std::vector<int> parent(V, -1);
        
        // Min heap: {weight, vertex}
        std::priority_queue<std::pair<int, int>,
                          std::vector<std::pair<int, int>>,
                          std::greater<std::pair<int, int>>> pq;
        
        key[0] = 0;
        pq.push({0, 0});
        int mstWeight = 0;
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int weight = pq.top().first;
            pq.pop();
            
            if (inMST[u]) continue;
            
            inMST[u] = true;
            mstWeight += weight;
            
            for (auto& [v, w] : adj[u]) {
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push({w, v});
                }
            }
        }
        
        std::cout << "MST edges:" << std::endl;
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1) {
                std::cout << "  " << parent[i] << " - " << i 
                         << " : " << key[i] << std::endl;
            }
        }
        
        return mstWeight;
    }
};

int main() {
    std::cout << "=== Prim's MST Algorithm ===" << std::endl;
    std::cout << "Time: O((V+E) log V), Space: O(V)" << std::endl << std::endl;
    
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);
    
    int weight = g.primMST();
    std::cout << "\nTotal MST weight: " << weight << std::endl;
    
    return 0;
}
