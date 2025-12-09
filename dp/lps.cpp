#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Longest Palindromic Subsequence
// Time Complexity: O(n²)
// Space Complexity: O(n²)

int longestPalindromicSubsequence(const std::string& s) {
    int n = s.length();
    // dp[i][j] = LPS length in s[i..j]
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    
    // Every single character is a palindrome of length 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // Fill table for substrings of length 2 to n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            } else {
                dp[i][j] = std::max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[0][n-1];
}

// Longest Palindromic Substring
// Time: O(n²), Space: O(n²)
std::string longestPalindromicSubstring(const std::string& s) {
    int n = s.length();
    if (n == 0) return \"\";
    
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    int maxLen = 1, start = 0;
    
    // Single characters
    for (int i = 0; i < n; i++) dp[i][i] = true;
    
    // Two characters
    for (int i = 0; i < n-1; i++) {
        if (s[i] == s[i+1]) {
            dp[i][i+1] = true;
            start = i;
            maxLen = 2;
        }
    }
    
    // Longer substrings
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i+1][j-1]) {
                dp[i][j] = true;
                if (len > maxLen) {
                    start = i;
                    maxLen = len;
                }
            }
        }
    }
    
    return s.substr(start, maxLen);
}

int main() {
    std::cout << \"=== Longest Palindromic Subsequence ===\" << std::endl;
    std::cout << \"Time: O(n²), Space: O(n²)\" << std::endl << std::endl;
    
    std::string s = \"BBABCBCAB\";
    std::cout << \"String: \" << s << std::endl;
    std::cout << \"LPS Length: \" << longestPalindromicSubsequence(s) << std::endl;
    std::cout << \"Longest Palindromic Substring: \" << longestPalindromicSubstring(s) << std::endl;
    
    return 0;
}
