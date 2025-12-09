#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

// Pseudo-Omnipotence: Problems that appear hard but have efficient solutions
// Demonstrates surprising polynomial-time algorithms
// Various time complexities

// Example 1: 2-SAT (Linear time!) despite SAT being NP-complete
class TwoSAT {
private:
    int n;
    std::vector<std::vector<int>> graph, graphT;
    std::vector<bool> visited;
    std::vector<int> order, comp;
    
    void dfs1(int v) {
        visited[v] = true;
        for (int u : graph[v]) {
            if (!visited[u])
                dfs1(u);
        }
        order.push_back(v);
    }
    
    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : graphT[v]) {
            if (comp[u] == -1)
                dfs2(u, c);
        }
    }
    
public:
    TwoSAT(int variables) : n(variables) {
        graph.resize(2 * n);
        graphT.resize(2 * n);
        visited.resize(2 * n, false);
        comp.resize(2 * n, -1);
    }
    
    // Add clause (a v b) where a, b are literals
    // Positive literal: x, Negative literal: ~x represented as x + n
    void addClause(int a, bool notA, int b, bool notB) {
        a = notA ? a + n : a;
        b = notB ? b + n : b;
        
        // (a v b) ≡ (~a → b) ∧ (~b → a)
        int notAVertex = a < n ? a + n : a - n;
        int notBVertex = b < n ? b + n : b - n;
        
        graph[notAVertex].push_back(b);
        graphT[b].push_back(notAVertex);
        
        graph[notBVertex].push_back(a);
        graphT[a].push_back(notBVertex);
    }
    
    bool isSatisfiable() {
        // Kosaraju's SCC algorithm
        for (int i = 0; i < 2 * n; i++) {
            if (!visited[i])
                dfs1(i);
        }
        
        int c = 0;
        std::reverse(order.begin(), order.end());
        for (int v : order) {
            if (comp[v] == -1)
                dfs2(v, c++);
        }
        
        // Check if x and ~x are in same SCC
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n])
                return false;
        }
        
        return true;
    }
    
    std::vector<bool> getAssignment() {
        std::vector<bool> assignment(n);
        for (int i = 0; i < n; i++) {
            // If comp[~x] > comp[x], assign x = true
            assignment[i] = comp[i + n] > comp[i];
        }
        return assignment;
    }
};

// Example 2: Linear Programming (Simplex in practice is fast)
// Simplified 2D linear programming
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double evaluateLinear(double a, double b, double c, const Point& p) {
    return a * p.x + b * p.y + c;
}

// Example 3: Matching in Bipartite Graphs (Polynomial time)
class BipartiteMatching {
private:
    int n, m;
    std::vector<std::vector<int>> graph;
    std::vector<int> match;
    std::vector<bool> used;
    
    bool dfs(int v) {
        if (used[v]) return false;
        used[v] = true;
        
        for (int to : graph[v]) {
            if (match[to] == -1 || dfs(match[to])) {
                match[to] = v;
                return true;
            }
        }
        return false;
    }
    
public:
    BipartiteMatching(int left, int right) : n(left), m(right), graph(left), match(right, -1) {}
    
    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }
    
    int maxMatching() {
        int result = 0;
        for (int v = 0; v < n; v++) {
            used.assign(n, false);
            if (dfs(v))
                result++;
        }
        return result;
    }
};

// Example 4: Convex Hull (O(n log n))
std::vector<Point> convexHull(std::vector<Point> points) {
    int n = points.size();
    if (n < 3) return points;
    
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    
    auto cross = [](const Point& O, const Point& A, const Point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    };
    
    std::vector<Point> hull;
    
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    // Build upper hull
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && cross(hull[hull.size()-2], hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    hull.pop_back();
    return hull;
}

int main() {
    std::cout << "=== Pseudo-Omnipotence: Surprisingly Efficient Algorithms ===" << std::endl << std::endl;
    
    // Example 1: 2-SAT in O(n + m)
    std::cout << "1. 2-SAT (Linear Time!):" << std::endl;
    TwoSAT sat(3);
    // (x0 v x1) ∧ (~x1 v x2) ∧ (~x0 v ~x2)
    sat.addClause(0, false, 1, false);
    sat.addClause(1, true, 2, false);
    sat.addClause(0, true, 2, true);
    
    if (sat.isSatisfiable()) {
        std::cout << "   Satisfiable!" << std::endl;
        auto assignment = sat.getAssignment();
        for (int i = 0; i < assignment.size(); i++) {
            std::cout << "   x" << i << " = " << (assignment[i] ? "true" : "false") << std::endl;
        }
    } else {
        std::cout << "   Not satisfiable" << std::endl;
    }
    
    // Example 2: Bipartite Matching
    std::cout << "\n2. Bipartite Matching (Polynomial):" << std::endl;
    BipartiteMatching bm(3, 3);
    bm.addEdge(0, 0);
    bm.addEdge(0, 1);
    bm.addEdge(1, 1);
    bm.addEdge(1, 2);
    bm.addEdge(2, 2);
    
    std::cout << "   Maximum matching: " << bm.maxMatching() << std::endl;
    
    // Example 3: Convex Hull
    std::cout << "\n3. Convex Hull (O(n log n)):" << std::endl;
    std::vector<Point> points = {
        {0, 0}, {1, 1}, {2, 2}, {0, 2}, {2, 0}, {1, 0.5}
    };
    
    auto hull = convexHull(points);
    std::cout << "   Convex hull points: " << hull.size() << std::endl;
    for (const auto& p : hull) {
        std::cout << "   (" << p.x << ", " << p.y << ")" << std::endl;
    }
    
    std::cout << "\nSurprising Polynomial Algorithms:" << std::endl;
    std::cout << "  - 2-SAT: O(n+m) despite 3-SAT being NP-complete" << std::endl;
    std::cout << "  - Linear Programming: Simplex fast in practice" << std::endl;
    std::cout << "  - Primality Testing: O(log^6 n) (AKS)" << std::endl;
    std::cout << "  - Bipartite Matching: O(VE) via augmenting paths" << std::endl;
    std::cout << "  - Min Cost Flow: Polynomial with cycle canceling" << std::endl;
    
    std::cout << "\nKey Insight:" << std::endl;
    std::cout << "  Many seemingly hard problems have polynomial solutions" << std::endl;
    std::cout << "  due to special structure (planarity, bipartiteness, etc.)" << std::endl;
    
    return 0;
}
