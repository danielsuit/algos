#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

// Strongly Connected Components (Kosaraju's Algorithm)
// Time Complexity: O(V + E)
// Space Complexity: O(V)

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    
    void DFSUtil(int v, std::vector<bool>& visited, std::stack<int>& Stack) {
        visited[v] = true;
        
        for (int u : adj[v]) {
            if (!visited[u])
                DFSUtil(u, visited, Stack);
        }
        
        Stack.push(v);
    }
    
    void DFSUtilPrint(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << v << " ";
        
        for (int u : adj[v]) {
            if (!visited[u])
                DFSUtilPrint(u, visited);
        }
    }
    
public:
    Graph(int vertices) : V(vertices), adj(vertices) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    Graph getTranspose() {
        Graph g(V);
        for (int v = 0; v < V; v++) {
            for (int u : adj[v]) {
                g.adj[u].push_back(v);
            }
        }
        return g;
    }
    
    void printSCCs() {
        std::stack<int> Stack;
        std::vector<bool> visited(V, false);
        
        // Step 1: Fill vertices in stack by finish time
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                DFSUtil(i, visited, Stack);
        }
        
        // Step 2: Get transpose graph
        Graph gr = getTranspose();
        
        // Step 3: DFS on transpose in order of decreasing finish time
        std::fill(visited.begin(), visited.end(), false);
        
        std::cout << "Strongly Connected Components:" << std::endl;
        int sccCount = 0;
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            
            if (!visited[v]) {
                std::cout << "  SCC " << ++sccCount << ": ";
                gr.DFSUtilPrint(v, visited);
                std::cout << std::endl;
            }
        }
    }
    
    // Tarjan's Algorithm (one-pass)
    void tarjanSCC() {
        std::vector<int> disc(V, -1);
        std::vector<int> low(V, -1);
        std::vector<bool> onStack(V, false);
        std::stack<int> st;
        int time = 0;
        int sccCount = 0;
        
        std::cout << "Strongly Connected Components (Tarjan):" << std::endl;
        
        std::function<void(int)> tarjanDFS = [&](int u) {
            disc[u] = low[u] = time++;
            st.push(u);
            onStack[u] = true;
            
            for (int v : adj[u]) {
                if (disc[v] == -1) {
                    tarjanDFS(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (onStack[v]) {
                    low[u] = std::min(low[u], disc[v]);
                }
            }
            
            // Found SCC root
            if (low[u] == disc[u]) {
                std::cout << "  SCC " << ++sccCount << ": ";
                while (true) {
                    int v = st.top();
                    st.pop();
                    onStack[v] = false;
                    std::cout << v << " ";
                    if (v == u) break;
                }
                std::cout << std::endl;
            }
        };
        
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1)
                tarjanDFS(i);
        }
    }
};

int main() {
    std::cout << "=== Strongly Connected Components ===" << std::endl;
    std::cout << "Time: O(V+E), Space: O(V)" << std::endl << std::endl;
    
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
    
    std::cout << "Kosaraju's Algorithm:" << std::endl;
    g.printSCCs();
    
    std::cout << "\n";
    g.tarjanSCC();
    
    std::cout << "\nKey Points:" << std::endl;
    std::cout << "  - Kosaraju: Two DFS passes (original + transpose)" << std::endl;
    std::cout << "  - Tarjan: Single DFS with low-link values" << std::endl;
    std::cout << "  - SCCs form a DAG (condensation graph)" << std::endl;
    
    return 0;
}
