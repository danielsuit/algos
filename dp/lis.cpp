#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Longest Increasing Subsequence (LIS)
// Find longest subsequence where elements are in increasing order
// Time Complexity: O(n²) DP, O(n log n) optimized
// Space Complexity: O(n)

// 1. DP Approach
// Time: O(n²), Space: O(n)
int lisDP(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    
    // dp[i] = length of LIS ending at index i
    std::vector<int> dp(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *std::max_element(dp.begin(), dp.end());
}

// 2. Binary Search Approach (Patience Sorting)
// Time: O(n log n), Space: O(n)
int lisBinarySearch(const std::vector<int>& arr) {
    std::vector<int> tails;  // tails[i] = smallest tail of LIS of length i+1
    
    for (int num : arr) {
        auto it = std::lower_bound(tails.begin(), tails.end(), num);
        
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return tails.size();
}

// Reconstruct LIS sequence
std::vector<int> lisSequence(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return {};
    
    std::vector<int> dp(n, 1);
    std::vector<int> parent(n, -1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    // Find index with maximum LIS length
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > dp[maxIdx]) {
            maxIdx = i;
        }
    }
    
    // Reconstruct sequence
    std::vector<int> lis;
    int idx = maxIdx;
    while (idx != -1) {
        lis.push_back(arr[idx]);
        idx = parent[idx];
    }
    
    std::reverse(lis.begin(), lis.end());
    return lis;
}

// Longest Decreasing Subsequence
int longestDecreasingSubsequence(const std::vector<int>& arr) {
    std::vector<int> negated(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        negated[i] = -arr[i];
    }
    return lisBinarySearch(negated);
}

// Number of LIS
// Time: O(n²), Space: O(n)
int numberOfLIS(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    
    std::vector<int> dp(n, 1);      // Length of LIS ending at i
    std::vector<int> count(n, 1);   // Count of LIS ending at i
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                } else if (dp[j] + 1 == dp[i]) {
                    count[i] += count[j];
                }
            }
        }
    }
    
    int maxLen = *std::max_element(dp.begin(), dp.end());
    int result = 0;
    
    for (int i = 0; i < n; i++) {
        if (dp[i] == maxLen) {
            result += count[i];
        }
    }
    
    return result;
}

// Longest Bitonic Subsequence
// Sequence that first increases then decreases
// Time: O(n²), Space: O(n)
int longestBitonicSubsequence(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    
    // LIS from left
    std::vector<int> lis(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = std::max(lis[i], lis[j] + 1);
            }
        }
    }
    
    // LDS from right
    std::vector<int> lds(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[i]) {
                lds[i] = std::max(lds[i], lds[j] + 1);
            }
        }
    }
    
    // Maximum bitonic length
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        maxLen = std::max(maxLen, lis[i] + lds[i] - 1);
    }
    
    return maxLen;
}

void printArray(const std::vector<int>& arr, const std::string& name) {
    std::cout << name << ": ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Longest Increasing Subsequence (LIS) ===" << std::endl;
    std::cout << "DP Approach: O(n²)" << std::endl;
    std::cout << "Binary Search: O(n log n)" << std::endl;
    
    // Example 1
    std::vector<int> arr1 = {10, 9, 2, 5, 3, 7, 101, 18};
    std::cout << "\n=== Example 1 ===" << std::endl;
    printArray(arr1, \"Array\");
    std::cout << \"LIS length (DP): \" << lisDP(arr1) << std::endl;
    std::cout << \"LIS length (Binary Search): \" << lisBinarySearch(arr1) << std::endl;
    
    std::vector<int> lis = lisSequence(arr1);
    printArray(lis, \"LIS sequence\");
    
    // Example 2
    std::vector<int> arr2 = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    std::cout << \"\n=== Example 2 ===" << std::endl;
    printArray(arr2, \"Array\");
    std::cout << \"LIS length: \" << lisBinarySearch(arr2) << std::endl;
    
    lis = lisSequence(arr2);
    printArray(lis, \"LIS sequence\");
    
    // Number of LIS
    std::vector<int> arr3 = {1, 3, 5, 4, 7};
    std::cout << \"\n=== Number of LIS ===" << std::endl;
    printArray(arr3, \"Array\");
    std::cout << \"LIS length: \" << lisDP(arr3) << std::endl;
    std::cout << \"Number of LIS: \" << numberOfLIS(arr3) << std::endl;
    
    // Longest Bitonic Subsequence
    std::vector<int> arr4 = {1, 11, 2, 10, 4, 5, 2, 1};
    std::cout << \"\n=== Longest Bitonic Subsequence ===" << std::endl;
    printArray(arr4, \"Array\");
    std::cout << \"Bitonic length: \" << longestBitonicSubsequence(arr4) << std::endl;
    // Expected: 1,11,10,5,2,1 or 1,2,10,5,2,1 (length 6)
    
    // Longest Decreasing Subsequence
    std::vector<int> arr5 = {10, 9, 2, 5, 3, 7, 101, 4};
    std::cout << \"\n=== Longest Decreasing Subsequence ===" << std::endl;
    printArray(arr5, \"Array\");
    std::cout << \"LDS length: \" << longestDecreasingSubsequence(arr5) << std::endl;
    
    std::cout << \"\n=== Key Insights ===" << std::endl;
    std::cout << \"1. DP Recurrence: dp[i] = max(dp[j] + 1) for all j < i where arr[j] < arr[i]\" << std::endl;
    std::cout << \"2. Binary search uses patience sorting concept\" << std::endl;
    std::cout << \"3. tails[i] = smallest ending element of LIS of length i+1\" << std::endl;
    std::cout << \"4. Bitonic = LIS + LDS (increasing then decreasing)\" << std::endl;
    
    std::cout << \"\n=== Applications ===" << std::endl;
    std::cout << \"1. Stock trading (buy low, sell high sequence)\" << std::endl;
    std::cout << \"2. Box stacking problems\" << std::endl;
    std::cout << \"3. Building bridges (matching pairs)\" << std::endl;
    std::cout << \"4. Patience sorting card game\" << std::endl;
    
    return 0;
}
