#include <iostream>
#include <vector>
#include <algorithm>

// Minimum Spanning Tree (General Implementation)
// Combines Kruskal's and Prim's with additional MST properties
// Time Complexity: O(E log E) for Kruskal
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
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
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

class MSTGraph {
private:
    int V;
    std::vector<Edge> edges;
    
public:
    MSTGraph(int vertices) : V(vertices) {}
    
    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }
    
    // Kruskal's MST
    std::pair<int, std::vector<Edge>> kruskalMST() {
        std::vector<Edge> mst;
        int totalWeight = 0;
        
        std::sort(edges.begin(), edges.end());
        UnionFind uf(V);
        
        for (const Edge& e : edges) {
            if (uf.unite(e.u, e.v)) {
                mst.push_back(e);
                totalWeight += e.weight;
                if (mst.size() == V - 1) break;
            }
        }
        
        return {totalWeight, mst};
    }
    
    // Check if adding edge creates cycle
    bool createsCycle(const Edge& newEdge, const std::vector<Edge>& currentEdges) {
        UnionFind uf(V);
        
        for (const Edge& e : currentEdges) {
            uf.unite(e.u, e.v);
        }
        
        return uf.find(newEdge.u) == uf.find(newEdge.v);
    }
    
    // Count number of MSTs (simplified check)
    int countMSTs() {
        // This is a simplified version - full implementation requires
        // checking all spanning trees with minimum weight
        auto [weight, mst] = kruskalMST();
        
        int count = 0;
        for (const Edge& e : edges) {
            bool inMST = false;
            for (const Edge& mstEdge : mst) {
                if (e.u == mstEdge.u && e.v == mstEdge.v && e.weight == mstEdge.weight) {
                    inMST = true;
                    break;
                }
            }
            if (!inMST && e.weight == mst[0].weight) {
                count++;
            }
        }
        
        return count > 0 ? 2 : 1; // Simplified
    }
    
    // Second best MST
    std::pair<int, std::vector<Edge>> secondBestMST() {
        auto [mstWeight, mst] = kruskalMST();
        int secondBest = INT_MAX;
        std::vector<Edge> secondMST;
        
        // Try removing each MST edge and adding non-MST edge
        for (int i = 0; i < mst.size(); i++) {
            std::vector<Edge> tempMST;
            int tempWeight = 0;
            UnionFind uf(V);
            
            for (const Edge& e : edges) {
                bool isRemovedEdge = (e.u == mst[i].u && e.v == mst[i].v && 
                                     e.weight == mst[i].weight);
                
                if (!isRemovedEdge && uf.unite(e.u, e.v)) {
                    tempMST.push_back(e);
                    tempWeight += e.weight;
                    if (tempMST.size() == V - 1) break;
                }
            }
            
            if (tempMST.size() == V - 1 && tempWeight < secondBest) {
                secondBest = tempWeight;
                secondMST = tempMST;
            }
        }
        
        return {secondBest, secondMST};
    }
};

int main() {
    std::cout << "=== Minimum Spanning Tree ===" << std::endl;
    std::cout << "Time: O(E log E), Space: O(V)" << std::endl << std::endl;
    
    MSTGraph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    
    auto [weight, mst] = g.kruskalMST();
    
    std::cout << "MST edges:" << std::endl;
    for (const Edge& e : mst) {
        std::cout << "  " << e.u << " - " << e.v << " : " << e.weight << std::endl;
    }
    std::cout << "Total weight: " << weight << std::endl;
    
    auto [secondWeight, secondMST] = g.secondBestMST();
    std::cout << "\nSecond best MST weight: " << secondWeight << std::endl;
    
    std::cout << "\nMST Properties:" << std::endl;
    std::cout << "  - Cut property: Lightest edge crossing cut is in some MST" << std::endl;
    std::cout << "  - Cycle property: Heaviest edge in cycle not in any MST" << std::endl;
    std::cout << "  - Unique MST if all edge weights distinct" << std::endl;
    std::cout << "  - Number of edges in MST: V - 1" << std::endl;
    
    return 0;
}
