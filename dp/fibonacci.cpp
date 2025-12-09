#include <iostream>
#include <vector>
#include <chrono>

// Fibonacci: Classic DP example
// F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)

// 1. Naive Recursive Approach
// Time Complexity: O(2^n) - exponential!
// Space Complexity: O(n) - recursion stack
int fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// 2. Memoization (Top-Down DP)
// Time Complexity: O(n)
// Space Complexity: O(n) for memo array + O(n) for recursion stack
int fibonacciMemo(int n, std::vector<int>& memo) {
    if (n <= 1) return n;
    
    if (memo[n] != -1) {
        return memo[n];  // Return cached result
    }
    
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}

int fibonacciMemoWrapper(int n) {
    std::vector<int> memo(n + 1, -1);
    return fibonacciMemo(n, memo);
}

// 3. Tabulation (Bottom-Up DP)
// Time Complexity: O(n)
// Space Complexity: O(n)
int fibonacciTabulation(int n) {
    if (n <= 1) return n;
    
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// 4. Space Optimized
// Time Complexity: O(n)
// Space Complexity: O(1)
int fibonacciOptimized(int n) {
    if (n <= 1) return n;
    
    int prev2 = 0;  // F(0)
    int prev1 = 1;  // F(1)
    
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

// 5. Matrix Exponentiation (for large n)
// Time Complexity: O(log n)
// Space Complexity: O(1)
void multiplyMatrix(long long F[2][2], long long M[2][2]) {
    long long x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void powerMatrix(long long F[2][2], int n) {
    if (n == 0 || n == 1) return;
    
    long long M[2][2] = {{1, 1}, {1, 0}};
    
    powerMatrix(F, n / 2);
    multiplyMatrix(F, F);
    
    if (n % 2 != 0) {
        multiplyMatrix(F, M);
    }
}

long long fibonacciMatrix(int n) {
    if (n <= 1) return n;
    
    long long F[2][2] = {{1, 1}, {1, 0}};
    powerMatrix(F, n - 1);
    
    return F[0][0];
}

// Print first n Fibonacci numbers
void printFibonacciSequence(int n) {
    std::cout << "First " << n << " Fibonacci numbers: ";
    for (int i = 0; i < n; i++) {
        std::cout << fibonacciOptimized(i);
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

// Benchmark different approaches
void benchmark(int n) {
    using namespace std::chrono;
    
    std::cout << "\n=== Performance Comparison (n=" << n << ") ===" << std::endl;
    
    if (n <= 40) {  // Only test recursive for small n
        auto start = high_resolution_clock::now();
        int result = fibonacciRecursive(n);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        std::cout << "Recursive:   " << result << " (Time: " << duration.count() << " μs)" << std::endl;
    } else {
        std::cout << "Recursive:   Skipped (too slow for n > 40)" << std::endl;
    }
    
    auto start = high_resolution_clock::now();
    int result = fibonacciMemoWrapper(n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    std::cout << "Memoization: " << result << " (Time: " << duration.count() << " μs)" << std::endl;
    
    start = high_resolution_clock::now();
    result = fibonacciTabulation(n);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    std::cout << "Tabulation:  " << result << " (Time: " << duration.count() << " μs)" << std::endl;
    
    start = high_resolution_clock::now();
    result = fibonacciOptimized(n);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    std::cout << "Optimized:   " << result << " (Time: " << duration.count() << " μs)" << std::endl;
    
    start = high_resolution_clock::now();
    long long resultMatrix = fibonacciMatrix(n);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    std::cout << "Matrix Exp:  " << resultMatrix << " (Time: " << duration.count() << " μs)" << std::endl;
}

int main() {
    std::cout << "=== Fibonacci Number Calculations ===" << std::endl;
    std::cout << "Time Complexities:" << std::endl;
    std::cout << "- Recursive:     O(2^n) - Exponential" << std::endl;
    std::cout << "- Memoization:   O(n) - Linear" << std::endl;
    std::cout << "- Tabulation:    O(n) - Linear" << std::endl;
    std::cout << "- Optimized:     O(n) - Linear, O(1) space" << std::endl;
    std::cout << "- Matrix Power:  O(log n) - Logarithmic" << std::endl;
    
    // Print sequence
    printFibonacciSequence(15);
    
    // Calculate specific values
    std::cout << "\n=== Specific Values ===" << std::endl;
    std::cout << "F(10) = " << fibonacciOptimized(10) << std::endl;
    std::cout << "F(20) = " << fibonacciOptimized(20) << std::endl;
    std::cout << "F(30) = " << fibonacciOptimized(30) << std::endl;
    std::cout << "F(40) = " << fibonacciOptimized(40) << std::endl;
    std::cout << "F(50) = " << fibonacciMatrix(50) << std::endl;
    
    // Performance comparison
    benchmark(20);
    benchmark(35);
    
    std::cout << "\n=== Key Insights ===" << std::endl;
    std::cout << "1. Naive recursion has overlapping subproblems (exponential)" << std::endl;
    std::cout << "2. Memoization caches results to avoid recomputation" << std::endl;
    std::cout << "3. Tabulation builds solution bottom-up" << std::endl;
    std::cout << "4. Space can be optimized to O(1) by keeping only last 2 values" << std::endl;
    std::cout << "5. Matrix exponentiation achieves O(log n) for very large n" << std::endl;
    
    return 0;
}
