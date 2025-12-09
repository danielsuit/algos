#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Longest Common Subsequence (LCS)
// Find longest subsequence common to two sequences
// Subsequence: sequence derived by deleting some elements without changing order

// Time Complexity: O(m * n) where m, n are lengths of strings
// Space Complexity: O(m * n), can be optimized to O(min(m, n))

// 1. Recursive Approach (Exponential)
// Time: O(2^(m+n)), Space: O(m+n) for recursion
int lcsRecursive(const std::string& s1, const std::string& s2, int i, int j) {
    // Base case: reached end of either string
    if (i == 0 || j == 0) {
        return 0;
    }
    
    // If characters match, add 1 and move both pointers
    if (s1[i - 1] == s2[j - 1]) {
        return 1 + lcsRecursive(s1, s2, i - 1, j - 1);
    }
    
    // If don't match, try both options
    return std::max(lcsRecursive(s1, s2, i - 1, j),
                    lcsRecursive(s1, s2, i, j - 1));
}

// 2. Memoization (Top-Down DP)
// Time: O(m * n), Space: O(m * n)
int lcsMemo(const std::string& s1, const std::string& s2, int i, int j,
            std::vector<std::vector<int>>& memo) {
    if (i == 0 || j == 0) {
        return 0;
    }
    
    if (memo[i][j] != -1) {
        return memo[i][j];
    }
    
    if (s1[i - 1] == s2[j - 1]) {
        memo[i][j] = 1 + lcsMemo(s1, s2, i - 1, j - 1, memo);
    } else {
        memo[i][j] = std::max(lcsMemo(s1, s2, i - 1, j, memo),
                              lcsMemo(s1, s2, i, j - 1, memo));
    }
    
    return memo[i][j];
}

// 3. Tabulation (Bottom-Up DP)
// Time: O(m * n), Space: O(m * n)
int lcsTabulation(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    // dp[i][j] = LCS length of s1[0..i-1] and s2[0..j-1]
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

// 4. Space Optimized (1D array)
// Time: O(m * n), Space: O(min(m, n))
int lcsOptimized(const std::string& s1, const std::string& s2) {
    // Make s1 the shorter string
    if (s1.length() > s2.length()) {
        return lcsOptimized(s2, s1);
    }
    
    int m = s1.length();
    int n = s2.length();
    
    std::vector<int> prev(m + 1, 0);
    std::vector<int> curr(m + 1, 0);
    
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[i] = prev[i - 1] + 1;
            } else {
                curr[i] = std::max(prev[i], curr[i - 1]);
            }
        }
        prev = curr;
    }
    
    return curr[m];
}

// Reconstruct the LCS string
std::string lcsString(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    // Build DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // Backtrack to construct LCS
    std::string lcs;
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return lcs;
}

// Longest Common Substring (continuous)
// Time: O(m * n), Space: O(m * n)
int longestCommonSubstring(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    int maxLen = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLen = std::max(maxLen, dp[i][j]);
            } else {
                dp[i][j] = 0;  // Reset for substring
            }
        }
    }
    
    return maxLen;
}

// Print LCS with highlighting
void printLCS(const std::string& s1, const std::string& s2) {
    std::string lcs = lcsString(s1, s2);
    int lcsLen = lcs.length();
    
    std::cout << "String 1: " << s1 << std::endl;
    std::cout << "String 2: " << s2 << std::endl;
    std::cout << "LCS:      " << lcs << std::endl;
    std::cout << "Length:   " << lcsLen << std::endl;
}

// LCS of 3 strings
// Time: O(m * n * p), Space: O(m * n * p)
int lcs3(const std::string& s1, const std::string& s2, const std::string& s3) {
    int m = s1.length();
    int n = s2.length();
    int p = s3.length();
    
    std::vector<std::vector<std::vector<int>>> dp(
        m + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(p + 1, 0)));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= p; k++) {
                if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = std::max({dp[i - 1][j][k],
                                           dp[i][j - 1][k],
                                           dp[i][j][k - 1]});
                }
            }
        }
    }
    
    return dp[m][n][p];
}

int main() {
    std::cout << "=== Longest Common Subsequence (LCS) ===" << std::endl;
    std::cout << "Time Complexity: O(m * n)" << std::endl;
    std::cout << "Space Complexity: O(m * n), optimizable to O(min(m,n))" << std::endl;
    
    // Example 1
    std::string s1 = "AGGTAB";
    std::string s2 = "GXTXAYB";
    
    std::cout << "\n=== Example 1 ===" << std::endl;
    printLCS(s1, s2);
    // Expected LCS: "GTAB" (length 4)
    
    // Example 2
    s1 = "ABCDGH";
    s2 = "AEDFHR";
    
    std::cout << "\n=== Example 2 ===" << std::endl;
    printLCS(s1, s2);
    // Expected LCS: "ADH" (length 3)
    
    // Example 3
    s1 = "programming";
    s2 = "gaming";
    
    std::cout << "\n=== Example 3 ===" << std::endl;
    printLCS(s1, s2);
    // Expected LCS: "gaming" (length 6)
    
    // Longest Common Substring
    std::cout << "\n=== Longest Common Substring ===" << std::endl;
    s1 = "abcdxyz";
    s2 = "xyzabcd";
    std::cout << "String 1: " << s1 << std::endl;
    std::cout << "String 2: " << s2 << std::endl;
    std::cout << "Longest Common Substring length: " 
              << longestCommonSubstring(s1, s2) << std::endl;
    
    // LCS of 3 strings
    std::cout << "\n=== LCS of 3 Strings ===" << std::endl;
    std::string s3 = "GXTXAYB";
    std::string s4 = "AGGTAB";
    std::string s5 = "GTAB";
    std::cout << "String 1: " << s3 << std::endl;
    std::cout << "String 2: " << s4 << std::endl;
    std::cout << "String 3: " << s5 << std::endl;
    std::cout << "LCS length: " << lcs3(s3, s4, s5) << std::endl;
    
    std::cout << "\n=== Applications ===" << std::endl;
    std::cout << "1. Diff utilities (finding changes between files)" << std::endl;
    std::cout << "2. DNA sequence alignment in bioinformatics" << std::endl;
    std::cout << "3. Version control systems" << std::endl;
    std::cout << "4. Plagiarism detection" << std::endl;
    std::cout << "5. Data comparison and similarity metrics" << std::endl;
    
    std::cout << "\n=== Key Insights ===" << std::endl;
    std::cout << "1. LCS vs Substring: LCS allows gaps, substring must be continuous" << std::endl;
    std::cout << "2. DP Recurrence:" << std::endl;
    std::cout << "   - If s1[i] == s2[j]: dp[i][j] = dp[i-1][j-1] + 1" << std::endl;
    std::cout << "   - Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])" << std::endl;
    std::cout << "3. Can be extended to k sequences with O(n^k) complexity" << std::endl;
    
    return 0;
}
