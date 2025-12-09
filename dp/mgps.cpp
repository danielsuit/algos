#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Maximum/Minimum Grid Path Sum (MGPS)
// Find path from top-left to bottom-right with max/min sum
// Time Complexity: O(m * n)
// Space Complexity: O(n) optimized

int maxPathSum(const std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));
    dp[0][0] = grid[0][0];
    
    // Initialize first row
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    // Initialize first column
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    // Fill rest of table
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = grid[i][j] + std::max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    return dp[m-1][n-1];
}

int minPathSum(const std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));
    dp[0][0] = grid[0][0];
    
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = grid[i][j] + std::min(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    return dp[m-1][n-1];
}

// Space optimized O(n)
int minPathSumOptimized(const std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    std::vector<int> dp(n);
    dp[0] = grid[0][0];
    
    for (int j = 1; j < n; j++) {
        dp[j] = dp[j-1] + grid[0][j];
    }
    
    for (int i = 1; i < m; i++) {
        dp[0] += grid[i][0];
        for (int j = 1; j < n; j++) {
            dp[j] = grid[i][j] + std::min(dp[j], dp[j-1]);
        }
    }
    
    return dp[n-1];
}

// Count all paths
int countPaths(int m, int n) {
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    
    return dp[m-1][n-1];
}

// Unique paths with obstacles
int uniquePathsWithObstacles(const std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    if (grid[0][0] == 1 || grid[m-1][n-1] == 1) return 0;
    
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
    dp[0][0] = 1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                dp[i][j] = 0;
            } else {
                if (i > 0) dp[i][j] += dp[i-1][j];
                if (j > 0) dp[i][j] += dp[i][j-1];
            }
        }
    }
    
    return dp[m-1][n-1];
}

int main() {
    std::cout << "=== Grid Path Sum Problems ===" << std::endl;
    std::cout << "Time: O(m*n), Space: O(n) optimized" << std::endl << std::endl;
    
    std::vector<std::vector<int>> grid1 = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    
    std::cout << "Grid 1:" << std::endl;
    for (const auto& row : grid1) {
        for (int val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
    
    std::cout << "Max path sum: " << maxPathSum(grid1) << std::endl;
    std::cout << "Min path sum: " << minPathSum(grid1) << std::endl;
    std::cout << "Min path sum (optimized): " << minPathSumOptimized(grid1) << std::endl;
    
    std::cout << "\nNumber of unique paths (3x3 grid): " << countPaths(3, 3) << std::endl;
    
    std::vector<std::vector<int>> grid2 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    
    std::cout << "\nGrid with obstacles (1 = obstacle):" << std::endl;
    for (const auto& row : grid2) {
        for (int val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
    std::cout << "Unique paths: " << uniquePathsWithObstacles(grid2) << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "  - Robot navigation" << std::endl;
    std::cout << "  - Game pathfinding with costs" << std::endl;
    std::cout << "  - Resource optimization" << std::endl;
    
    return 0;
}
