#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

// Matrix Chain Multiplication
// Find optimal way to multiply chain of matrices
// Time Complexity: O(n³)
// Space Complexity: O(n²)

int matrixChainMultiplication(const std::vector<int>& dims) {
    int n = dims.size() - 1;  // Number of matrices
    
    // dp[i][j] = min operations to multiply matrices i to j
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    
    // len = chain length
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            // Try all split points
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + 
                          dims[i] * dims[k+1] * dims[j+1];
                dp[i][j] = std::min(dp[i][j], cost);
            }
        }
    }
    
    return dp[0][n-1];
}

int main() {
    std::cout << \"=== Matrix Chain Multiplication ===\" << std::endl;
    std::cout << \"Time: O(n³), Space: O(n²)\" << std::endl << std::endl;
    
    // Matrix dimensions: A1(10x30), A2(30x5), A3(5x60)
    std::vector<int> dims = {10, 30, 5, 60};
    std::cout << \"Matrices: A1(10x30), A2(30x5), A3(5x60)\" << std::endl;
    std::cout << \"Min multiplications: \" << matrixChainMultiplication(dims) << std::endl;
    
    return 0;
}
