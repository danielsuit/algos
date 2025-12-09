#include <iostream>
#include <vector>
#include <algorithm>

// TriPaSu: Triangle, Pascal's Triangle, and Sum variants
// Time Complexity: O(n^2)
// Space Complexity: O(n)

// Minimum path sum in triangle
int minimumTotal(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();
    std::vector<int> dp = triangle[n-1];
    
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + std::min(dp[j], dp[j+1]);
        }
    }
    
    return dp[0];
}

// Generate Pascal's Triangle
std::vector<std::vector<int>> generatePascal(int numRows) {
    std::vector<std::vector<int>> triangle;
    
    for (int i = 0; i < numRows; i++) {
        std::vector<int> row(i + 1, 1);
        for (int j = 1; j < i; j++) {
            row[j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
        triangle.push_back(row);
    }
    
    return triangle;
}

// Get kth row of Pascal's Triangle (space optimized)
std::vector<int> getRow(int rowIndex) {
    std::vector<int> row(rowIndex + 1, 1);
    
    for (int i = 1; i <= rowIndex; i++) {
        for (int j = i - 1; j > 0; j--) {
            row[j] += row[j-1];
        }
    }
    
    return row;
}

// Maximum sum path in triangle (top to bottom)
int maxPathSum(const std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();
    std::vector<int> dp = triangle[n-1];
    
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + std::max(dp[j], dp[j+1]);
        }
    }
    
    return dp[0];
}

// Count paths with given sum in triangle
int countPathsWithSum(const std::vector<std::vector<int>>& triangle, int targetSum) {
    int n = triangle.size();
    std::vector<std::vector<std::vector<int>>> dp(
        n, std::vector<std::vector<int>>(n, std::vector<int>(targetSum + 1, 0))
    );
    
    if (triangle[0][0] <= targetSum)
        dp[0][0][triangle[0][0]] = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int sum = triangle[i][j]; sum <= targetSum; sum++) {
                if (j > 0 && dp[i-1][j-1][sum - triangle[i][j]] > 0) {
                    dp[i][j][sum] += dp[i-1][j-1][sum - triangle[i][j]];
                }
                if (j < i && dp[i-1][j][sum - triangle[i][j]] > 0) {
                    dp[i][j][sum] += dp[i-1][j][sum - triangle[i][j]];
                }
            }
        }
    }
    
    int count = 0;
    for (int j = 0; j < n; j++) {
        count += dp[n-1][j][targetSum];
    }
    
    return count;
}

void printTriangle(const std::vector<std::vector<int>>& triangle) {
    for (const auto& row : triangle) {
        for (int val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== Triangle Problems ===" << std::endl;
    std::cout << "Time: O(n^2), Space: O(n)" << std::endl << std::endl;
    
    std::vector<std::vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    
    std::cout << "Triangle:" << std::endl;
    printTriangle(triangle);
    
    std::cout << "\nMinimum path sum: " << minimumTotal(triangle) << std::endl;
    std::cout << "Maximum path sum: " << maxPathSum(triangle) << std::endl;
    
    std::cout << "\n=== Pascal's Triangle ===" << std::endl;
    int numRows = 5;
    auto pascal = generatePascal(numRows);
    std::cout << "First " << numRows << " rows:" << std::endl;
    printTriangle(pascal);
    
    std::cout << "\n5th row (0-indexed): ";
    auto row = getRow(5);
    for (int val : row)
        std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "\nPascal's Triangle Properties:" << std::endl;
    std::cout << "  - Each number = sum of two above it" << std::endl;
    std::cout << "  - Row n contains binomial coefficients C(n,k)" << std::endl;
    std::cout << "  - Symmetric around center" << std::endl;
    std::cout << "  - Sum of row n = 2^n" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "  - Combinatorics (binomial coefficients)" << std::endl;
    std::cout << "  - Probability theory" << std::endl;
    std::cout << "  - Path counting problems" << std::endl;
    std::cout << "  - Dynamic programming optimization" << std::endl;
    
    return 0;
}
