#include <iostream>
#include <vector>
#include <algorithm>

// Kruskal's Minimum Spanning Tree Algorithm
// Time Complexity: O(E log E) or O(E log V)
// Space Complexity: O(V)

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
private:
    std::vector<int> parent, rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false;
        
        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        
        return true;
    }
};

class Graph {
private:
    int V;
    std::vector<Edge> edges;
    
public:
    Graph(int vertices) : V(vertices) {}
    
    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }
    
    std::pair<int, std::vector<Edge>> kruskalMST() {
        std::vector<Edge> mst;
        int mstWeight = 0;
        
        // Sort edges by weight
        std::sort(edges.begin(), edges.end());
        
        UnionFind uf(V);
        
        for (const Edge& e : edges) {
            if (uf.unite(e.u, e.v)) {
                mst.push_back(e);
                mstWeight += e.weight;
                
                if (mst.size() == V - 1) break;
            }
        }
        
        return {mstWeight, mst};
    }
};

int main() {
    std::cout << \"=== Kruskal's MST Algorithm ===\" << std::endl;
    std::cout << \"Time: O(E log E), Space: O(V)\" << std::endl << std::endl;
    
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    
    auto [weight, mst] = g.kruskalMST();
    
    std::cout << \"MST edges:\" << std::endl;
    for (const Edge& e : mst) {
        std::cout << \"  \" << e.u << \" - \" << e.v << \" : \" << e.weight << std::endl;
    }
    std::cout << \"\\nTotal weight: \" << weight << std::endl;
    
    return 0;
}
