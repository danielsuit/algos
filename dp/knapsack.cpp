#include <iostream>
#include <vector>
#include <algorithm>

// 0/1 Knapsack Problem
// Given weights, values, and capacity, maximize total value
// Each item can be taken at most once

// Time Complexity: O(n * W) where n = items, W = capacity
// Space Complexity: O(n * W)

// Structure to hold item information
struct Item {
    int weight;
    int value;
    
    Item(int w, int v) : weight(w), value(v) {}
};

// 1. Recursive Approach (Exponential)
// Time: O(2^n), Space: O(n) for recursion stack
int knapsackRecursive(const std::vector<Item>& items, int capacity, int index) {
    // Base case: no items left or no capacity
    if (index >= items.size() || capacity == 0) {
        return 0;
    }
    
    // If current item is too heavy, skip it
    if (items[index].weight > capacity) {
        return knapsackRecursive(items, capacity, index + 1);
    }
    
    // Choose max of:
    // 1. Include current item
    // 2. Exclude current item
    int include = items[index].value + 
                  knapsackRecursive(items, capacity - items[index].weight, index + 1);
    int exclude = knapsackRecursive(items, capacity, index + 1);
    
    return std::max(include, exclude);
}

// 2. Memoization (Top-Down DP)
// Time: O(n * W), Space: O(n * W)
int knapsackMemo(const std::vector<Item>& items, int capacity, int index,
                 std::vector<std::vector<int>>& memo) {
    if (index >= items.size() || capacity == 0) {
        return 0;
    }
    
    if (memo[index][capacity] != -1) {
        return memo[index][capacity];
    }
    
    if (items[index].weight > capacity) {
        memo[index][capacity] = knapsackMemo(items, capacity, index + 1, memo);
    } else {
        int include = items[index].value + 
                      knapsackMemo(items, capacity - items[index].weight, index + 1, memo);
        int exclude = knapsackMemo(items, capacity, index + 1, memo);
        memo[index][capacity] = std::max(include, exclude);
    }
    
    return memo[index][capacity];
}

// 3. Tabulation (Bottom-Up DP)
// Time: O(n * W), Space: O(n * W)
int knapsackTabulation(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    
    // dp[i][w] = max value using first i items with capacity w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    // Build table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // Don't include current item
            dp[i][w] = dp[i - 1][w];
            
            // Include current item if it fits
            if (items[i - 1].weight <= w) {
                int include = items[i - 1].value + dp[i - 1][w - items[i - 1].weight];
                dp[i][w] = std::max(dp[i][w], include);
            }
        }
    }
    
    return dp[n][capacity];
}

// 4. Space Optimized (1D array)
// Time: O(n * W), Space: O(W)
int knapsackOptimized(const std::vector<Item>& items, int capacity) {
    std::vector<int> dp(capacity + 1, 0);
    
    for (const Item& item : items) {
        // Traverse from right to left to avoid using updated values
        for (int w = capacity; w >= item.weight; w--) {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    return dp[capacity];
}

// Reconstruct solution (which items to take)
std::vector<int> knapsackSolution(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];
            if (items[i - 1].weight <= w) {
                int include = items[i - 1].value + dp[i - 1][w - items[i - 1].weight];
                dp[i][w] = std::max(dp[i][w], include);
            }
        }
    }
    
    // Backtrack to find items
    std::vector<int> selected;
    int w = capacity;
    for (int i = n; i > 0 && w > 0; i--) {
        // If value came from including item i
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i - 1);  // Add item index
            w -= items[i - 1].weight;
        }
    }
    
    std::reverse(selected.begin(), selected.end());
    return selected;
}

// Unbounded Knapsack (items can be taken multiple times)
// Time: O(n * W), Space: O(W)
int unboundedKnapsack(const std::vector<Item>& items, int capacity) {
    std::vector<int> dp(capacity + 1, 0);
    
    for (int w = 0; w <= capacity; w++) {
        for (const Item& item : items) {
            if (item.weight <= w) {
                dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
            }
        }
    }
    
    return dp[capacity];
}

void printItems(const std::vector<Item>& items) {
    std::cout << "Items (weight, value):" << std::endl;
    for (int i = 0; i < items.size(); i++) {
        std::cout << "  Item " << i << ": (" << items[i].weight 
                  << ", " << items[i].value << ")" << std::endl;
    }
}

int main() {
    std::cout << "=== 0/1 Knapsack Problem ===" << std::endl;
    std::cout << "Time Complexity: O(n * W)" << std::endl;
    std::cout << "Space Complexity: O(W) optimized" << std::endl;
    
    // Example 1
    std::vector<Item> items1 = {
        Item(2, 12),   // Item 0
        Item(1, 10),   // Item 1
        Item(3, 20),   // Item 2
        Item(2, 15)    // Item 3
    };
    int capacity1 = 5;
    
    std::cout << "\n=== Example 1 ===" << std::endl;
    printItems(items1);
    std::cout << "Capacity: " << capacity1 << std::endl;
    
    int maxValue = knapsackOptimized(items1, capacity1);
    std::cout << "Maximum value: " << maxValue << std::endl;
    
    std::vector<int> solution = knapsackSolution(items1, capacity1);
    std::cout << "Selected items: ";
    int totalWeight = 0, totalValue = 0;
    for (int idx : solution) {
        std::cout << idx << " ";
        totalWeight += items1[idx].weight;
        totalValue += items1[idx].value;
    }
    std::cout << std::endl;
    std::cout << "Total weight: " << totalWeight << std::endl;
    std::cout << "Total value: " << totalValue << std::endl;
    
    // Example 2
    std::vector<Item> items2 = {
        Item(10, 60),
        Item(20, 100),
        Item(30, 120)
    };
    int capacity2 = 50;
    
    std::cout << "\n=== Example 2 ===" << std::endl;
    printItems(items2);
    std::cout << "Capacity: " << capacity2 << std::endl;
    
    maxValue = knapsackOptimized(items2, capacity2);
    std::cout << "Maximum value: " << maxValue << std::endl;
    
    solution = knapsackSolution(items2, capacity2);
    std::cout << "Selected items: ";
    totalWeight = 0;
    totalValue = 0;
    for (int idx : solution) {
        std::cout << idx << " ";
        totalWeight += items2[idx].weight;
        totalValue += items2[idx].value;
    }
    std::cout << std::endl;
    std::cout << "Total weight: " << totalWeight << std::endl;
    std::cout << "Total value: " << totalValue << std::endl;
    
    // Unbounded Knapsack Example
    std::cout << "\n=== Unbounded Knapsack ===" << std::endl;
    std::vector<Item> items3 = {
        Item(1, 10),
        Item(2, 15),
        Item(3, 40)
    };
    int capacity3 = 5;
    
    printItems(items3);
    std::cout << "Capacity: " << capacity3 << std::endl;
    std::cout << "Items can be taken multiple times" << std::endl;
    
    maxValue = unboundedKnapsack(items3, capacity3);
    std::cout << "Maximum value: " << maxValue << std::endl;
    
    std::cout << "\n=== Key Concepts ===" << std::endl;
    std::cout << "1. Optimal Substructure: Solution depends on solutions to subproblems" << std::endl;
    std::cout << "2. Overlapping Subproblems: Same subproblems solved multiple times" << std::endl;
    std::cout << "3. DP State: dp[i][w] = max value using first i items with capacity w" << std::endl;
    std::cout << "4. Transition: dp[i][w] = max(exclude, include)" << std::endl;
    std::cout << "5. Space optimization: Only need previous row, so use 1D array" << std::endl;
    
    return 0;
}
