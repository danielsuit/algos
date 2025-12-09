#include <iostream>
#include <vector>

// Subset Sum Problem
// Determine if there's a subset with given sum
// Time Complexity: O(n * sum)
// Space Complexity: O(sum)

bool subsetSum(const std::vector<int>& arr, int targetSum) {
    int n = arr.size();
    
    // dp[i] = true if sum i is possible
    std::vector<bool> dp(targetSum + 1, false);
    dp[0] = true;  // Sum 0 always possible (empty subset)
    
    for (int num : arr) {
        // Traverse right to left to avoid using same element twice
        for (int sum = targetSum; sum >= num; sum--) {
            if (dp[sum - num]) {
                dp[sum] = true;
            }
        }
    }
    
    return dp[targetSum];
}

// Count number of subsets with given sum
int countSubsetSum(const std::vector<int>& arr, int targetSum) {
    std::vector<int> dp(targetSum + 1, 0);
    dp[0] = 1;
    
    for (int num : arr) {
        for (int sum = targetSum; sum >= num; sum--) {
            dp[sum] += dp[sum - num];
        }
    }
    
    return dp[targetSum];
}

int main() {
    std::cout << \"=== Subset Sum Problem ===\" << std::endl;
    std::cout << \"Time: O(n*sum), Space: O(sum)\" << std::endl << std::endl;
    
    std::vector<int> arr = {3, 34, 4, 12, 5, 2};
    int target = 9;
    
    std::cout << \"Array: \";
    for (int x : arr) std::cout << x << \" \";
    std::cout << std::endl;
    std::cout << \"Target sum: \" << target << std::endl;
    std::cout << \"Exists: \" << (subsetSum(arr, target) ? \"Yes\" : \"No\") << std::endl;
    std::cout << \"Count: \" << countSubsetSum(arr, target) << std::endl;
    
    return 0;
}
