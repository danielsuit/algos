# Recursion

## Overview
Recursion is a programming technique where a function calls itself to solve a problem by breaking it down into smaller subproblems. It's fundamental to many algorithm design paradigms.

## Anatomy of Recursive Function

Every recursive function needs:

1. **Base Case(s)**: Simple case(s) that can be solved directly without recursion
2. **Recursive Case**: Break problem into smaller subproblems and combine results
3. **Progress towards Base Case**: Each recursive call must get closer to base case

```cpp
int factorial(int n) {
    // Base case
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case: n! = n × (n-1)!
    return n * factorial(n - 1);
}
```

## Types of Recursion

### 1. Linear Recursion
Function makes **one** recursive call

**Example: Factorial**
```cpp
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```
- **Time**: O(n)
- **Space**: O(n) - recursion stack depth

### 2. Binary Recursion
Function makes **two** recursive calls

**Example: Fibonacci**
```cpp
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```
- **Time**: O(2ⁿ) - exponential!
- **Space**: O(n) - maximum recursion depth

**Recurrence**: T(n) = T(n-1) + T(n-2) + O(1)

### 3. Multiple Recursion
Function makes **multiple** recursive calls

**Example: Tower of Hanoi**
```cpp
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    hanoi(n-1, from, aux, to);    // Move n-1 disks to auxiliary
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    hanoi(n-1, aux, to, from);    // Move n-1 disks to destination
}
```
- **Time**: O(2ⁿ)
- **Number of moves**: 2ⁿ - 1

### 4. Tail Recursion
Recursive call is the **last operation**

**Example: Tail Recursive Factorial**
```cpp
int factorialTail(int n, int accumulator = 1) {
    if (n <= 1) return accumulator;
    return factorialTail(n - 1, n * accumulator);
}
```
- Compilers can optimize tail recursion to iteration (Tail Call Optimization)
- **Space**: O(1) after optimization (vs O(n) for regular recursion)

### 5. Mutual Recursion
Two or more functions call each other

**Example: Even/Odd Check**
```cpp
bool isEven(int n);
bool isOdd(int n);

bool isEven(int n) {
    if (n == 0) return true;
    return isOdd(n - 1);
}

bool isOdd(int n) {
    if (n == 0) return false;
    return isEven(n - 1);
}
```

## Recursion vs Iteration

| Aspect | Recursion | Iteration |
|--------|-----------|----------|
| **Readability** | Often clearer for naturally recursive problems | More verbose |
| **Space** | O(depth) stack space | O(1) typically |
| **Performance** | Function call overhead | Direct execution |
| **Risk** | Stack overflow | Infinite loop |
| **Use Case** | Trees, divide-and-conquer | Simple loops |

## Converting Recursion to Iteration

### Example: Fibonacci

**Recursive (inefficient)**:
```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);  // O(2^n)
}
```

**Iterative**:
```cpp
int fib(int n) {
    if (n <= 1) return n;
    int prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;  // O(n), O(1) space
}
```

**Recursive with Memoization**:
```cpp
int fib(int n, vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fib(n-1, memo) + fib(n-2, memo);
    return memo[n];  // O(n) time and space
}
```

## Recursion Trees

Visualize recursive calls to analyze complexity

### Example: fib(5)
```
                    fib(5)
                   /      \
              fib(4)      fib(3)
             /     \       /    \
        fib(3)   fib(2) fib(2) fib(1)
        /    \    /   \   /  \
    fib(2) fib(1) ...  ... ... ...
```

- Height: O(n)
- Nodes: O(2ⁿ)
- Many repeated calculations!

## Common Recursive Patterns

### 1. Divide and Conquer
Break problem into independent subproblems

**Example: Merge Sort**
```cpp
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;  // Base case
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);       // Divide
    mergeSort(arr, mid+1, right);    // Divide
    merge(arr, left, mid, right);    // Conquer
}
```
- T(n) = 2T(n/2) + O(n) = O(n log n)

### 2. Decrease and Conquer
Reduce problem by constant amount

**Example: Binary Search**
```cpp
int binarySearch(vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;  // Base case
    
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) 
        return binarySearch(arr, target, left, mid-1);
    return binarySearch(arr, target, mid+1, right);
}
```
- T(n) = T(n/2) + O(1) = O(log n)

### 3. Backtracking
Explore all possibilities, backtrack on failure

**Example: N-Queens**
```cpp
bool solveNQueens(vector<vector<int>>& board, int col) {
    if (col >= N) return true;  // Base case: all queens placed
    
    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // Place queen
            
            if (solveNQueens(board, col+1))  // Recurse
                return true;
            
            board[row][col] = 0;  // Backtrack
        }
    }
    return false;
}
```

### 4. Dynamic Programming
Recursion + Memoization to avoid redundant calculations

**Example: Longest Common Subsequence**
```cpp
int lcs(string& s1, string& s2, int i, int j, vector<vector<int>>& memo) {
    if (i == 0 || j == 0) return 0;  // Base case
    
    if (memo[i][j] != -1) return memo[i][j];  // Memoized
    
    if (s1[i-1] == s2[j-1])
        memo[i][j] = 1 + lcs(s1, s2, i-1, j-1, memo);
    else
        memo[i][j] = max(lcs(s1, s2, i-1, j, memo), 
                         lcs(s1, s2, i, j-1, memo));
    
    return memo[i][j];
}
```

## Recursion Complexity Analysis

### Counting Operations

**Example: Merge Sort**
- **Recursive calls**: 2 calls to problems of size n/2
- **Work per level**: O(n) for merging
- **Depth**: log n levels
- **Total**: O(n log n)

### Space Complexity

1. **Recursion Stack**: Maximum depth of recursive calls
2. **Auxiliary Space**: Extra space used by function

**Examples**:
- Binary Search: O(log n) stack + O(1) auxiliary = O(log n)
- Merge Sort: O(log n) stack + O(n) auxiliary = O(n)
- Quick Sort: O(log n) average stack, O(n) worst case

## Common Pitfalls

### 1. Missing Base Case
```cpp
// WRONG: No base case!
int factorial(int n) {
    return n * factorial(n - 1);  // Stack overflow!
}
```

### 2. Not Making Progress
```cpp
// WRONG: Never reaches base case!
int wrong(int n) {
    if (n == 0) return 0;
    return wrong(n);  // Infinite recursion!
}
```

### 3. Exponential Complexity
```cpp
// WRONG: Very inefficient!
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);  // O(2^n)!
}
// FIX: Use memoization or iteration
```

### 4. Stack Overflow
```cpp
// WRONG: Too deep recursion
int sum(int n) {
    if (n == 0) return 0;
    return n + sum(n-1);  // Stack overflow for large n
}
// FIX: Use iteration or tail recursion
```

## Best Practices

1. **Always define clear base case(s)**
2. **Ensure progress towards base case**
3. **Consider iterative alternative** for simple recursion
4. **Use memoization** to avoid redundant calculations
5. **Be aware of stack depth** limitations
6. **Document recursive invariants** (what's true at each call)
7. **Test with small inputs** first

## When to Use Recursion

**Good Use Cases**:
- Tree/graph traversal
- Divide and conquer algorithms
- Backtracking problems
- Problems with recursive structure (factorial, Fibonacci, etc.)
- When solution is naturally expressed recursively

**Avoid When**:
- Simple iteration suffices
- Very deep recursion (stack overflow risk)
- No overlapping subproblems (use DP instead)
- Performance is critical and tail recursion not supported

## Summary

- Recursion breaks problems into smaller, similar subproblems
- Requires: base case, recursive case, progress
- Types: linear, binary, multiple, tail, mutual
- Can often be converted to iteration
- Space complexity: O(depth) for recursion stack
- Use memoization to optimize overlapping subproblems
- Essential for divide-and-conquer, backtracking, tree algorithms
