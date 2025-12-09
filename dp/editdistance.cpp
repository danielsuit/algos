#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Edit Distance (Levenshtein Distance)
// Minimum operations to convert one string to another
// Operations: Insert, Delete, Replace
// Time Complexity: O(m * n)
// Space Complexity: O(m * n), optimizable to O(min(m, n))

int editDistanceDP(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    // dp[i][j] = edit distance between s1[0..i-1] and s2[0..j-1]
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    
    // Base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i;  // Delete all
    for (int j = 0; j <= n; j++) dp[0][j] = j;  // Insert all
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];  // No operation needed
            } else {
                dp[i][j] = 1 + std::min({
                    dp[i-1][j],      // Delete from s1
                    dp[i][j-1],      // Insert to s1
                    dp[i-1][j-1]     // Replace
                });
            }
        }
    }
    
    return dp[m][n];
}

// Space Optimized O(n)
int editDistanceOptimized(const std::string& s1, const std::string& s2) {
    int m = s1.length(), n = s2.length();
    
    std::vector<int> prev(n + 1), curr(n + 1);
    for (int j = 0; j <= n; j++) prev[j] = j;
    
    for (int i = 1; i <= m; i++) {
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                curr[j] = prev[j-1];
            } else {
                curr[j] = 1 + std::min({prev[j], curr[j-1], prev[j-1]});
            }
        }
        prev = curr;
    }
    
    return curr[n];
}

int main() {
    std::cout << \"=== Edit Distance (Levenshtein Distance) ===\" << std::endl;
    std::cout << \"Time: O(m*n), Space: O(min(m,n))\" << std::endl << std::endl;
    
    std::string s1 = \"saturday\", s2 = \"sunday\";
    std::cout << \"\\\"\" << s1 << \"\\\" -> \\\"\" << s2 << \"\\\" : \" 
              << editDistanceDP(s1, s2) << \" operations\" << std::endl;
    
    s1 = \"horse\"; s2 = \"ros\";
    std::cout << \"\\\"\" << s1 << \"\\\" -> \\\"\" << s2 << \"\\\" : \" 
              << editDistanceDP(s1, s2) << \" operations\" << std::endl;
    
    return 0;
}
