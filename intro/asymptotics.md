# Asymptotic Analysis

## Overview
Asymptotic analysis describes the behavior of algorithms as input size grows to infinity. It provides a mathematical framework for comparing algorithm efficiency.

## Big O Notation - O(f(n))
**Upper bound** - Describes worst-case scenario

- **Definition**: f(n) = O(g(n)) if there exist constants c > 0 and n₀ such that f(n) ≤ c·g(n) for all n ≥ n₀
- **Meaning**: Algorithm will never take more than g(n) time (up to constant factors)

### Common Time Complexities (Best to Worst)
1. **O(1)** - Constant time
   - Array access, hash table lookup
   - Example: `return arr[0]`

2. **O(log n)** - Logarithmic time
   - Binary search, balanced tree operations
   - Example: Binary search in sorted array

3. **O(n)** - Linear time
   - Single pass through data
   - Example: Finding max element

4. **O(n log n)** - Linearithmic time
   - Efficient sorting algorithms
   - Example: Merge sort, heap sort

5. **O(n²)** - Quadratic time
   - Nested loops over input
   - Example: Bubble sort, insertion sort

6. **O(n³)** - Cubic time
   - Triple nested loops
   - Example: Naive matrix multiplication

7. **O(2ⁿ)** - Exponential time
   - Recursive algorithms with branching
   - Example: Naive Fibonacci, subset generation

8. **O(n!)** - Factorial time
   - Permutation generation
   - Example: Traveling salesman (brute force)

## Big Omega Notation - Ω(f(n))
**Lower bound** - Describes best-case scenario

- **Definition**: f(n) = Ω(g(n)) if there exist constants c > 0 and n₀ such that f(n) ≥ c·g(n) for all n ≥ n₀
- **Meaning**: Algorithm will take at least g(n) time

## Big Theta Notation - Θ(f(n))
**Tight bound** - Describes average/exact case

- **Definition**: f(n) = Θ(g(n)) if f(n) = O(g(n)) AND f(n) = Ω(g(n))
- **Meaning**: Algorithm grows exactly like g(n)

### Example: Linear Search
```cpp
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```
- **Best case**: Ω(1) - element at first position
- **Worst case**: O(n) - element at last position or not present
- **Average case**: Θ(n) - element expected in middle

## Little o Notation - o(f(n))
**Strict upper bound**

- **Definition**: f(n) = o(g(n)) if for all c > 0, there exists n₀ such that f(n) < c·g(n) for all n ≥ n₀
- **Meaning**: f grows strictly slower than g

## Little omega Notation - ω(f(n))
**Strict lower bound**

- **Definition**: f(n) = ω(g(n)) if for all c > 0, there exists n₀ such that f(n) > c·g(n) for all n ≥ n₀
- **Meaning**: f grows strictly faster than g

## Rules for Analysis

### 1. Drop Constants
- O(2n) → O(n)
- O(n/2) → O(n)
- O(1000) → O(1)

### 2. Drop Lower Order Terms
- O(n² + n) → O(n²)
- O(n log n + n) → O(n log n)
- O(2ⁿ + n³) → O(2ⁿ)

### 3. Analyze Nested Loops
```cpp
// O(n²)
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        // O(1) operation
    }
}

// O(n log n)
for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j *= 2) {
        // O(1) operation
    }
}
```

### 4. Sequential Statements Add
```cpp
// O(n) + O(n) = O(n)
for (int i = 0; i < n; i++) { }  // O(n)
for (int i = 0; i < n; i++) { }  // O(n)

// O(n) + O(n²) = O(n²)
for (int i = 0; i < n; i++) { }  // O(n)
for (int i = 0; i < n; i++) {    // O(n²)
    for (int j = 0; j < n; j++) { }
}
```

### 5. Logarithmic Complexity
```cpp
// O(log n) - dividing problem in half
while (n > 1) {
    n = n / 2;
}

// O(n log n) - divide and conquer
void mergeSort(arr, left, right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);      // T(n/2)
        mergeSort(arr, mid+1, right);   // T(n/2)
        merge(arr, left, mid, right);   // O(n)
    }
}
```

## Space Complexity

Same notation applies to memory usage:

- **O(1)** - Constant space (few variables)
- **O(log n)** - Logarithmic space (recursion stack for binary search)
- **O(n)** - Linear space (array of size n)
- **O(n²)** - Quadratic space (2D matrix)

### Example: Space Analysis
```cpp
// Space: O(1) - only uses constant extra space
int sum(vector<int>& arr) {
    int total = 0;
    for (int x : arr) total += x;
    return total;
}

// Space: O(n) - creates new array
vector<int> double(vector<int>& arr) {
    vector<int> result;
    for (int x : arr) result.push_back(x * 2);
    return result;
}

// Space: O(log n) - recursion stack
int binarySearch(vector<int>& arr, int target, int l, int r) {
    if (l > r) return -1;
    int mid = l + (r - l) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return binarySearch(arr, target, l, mid-1);
    return binarySearch(arr, target, mid+1, r);
}
```

## Amortized Analysis

Analyzes average cost per operation over a sequence of operations.

### Example: Dynamic Array
- Appending to array with resizing:
  - Most appends: O(1)
  - Occasional resize: O(n)
  - **Amortized**: O(1) per operation

## Practical Considerations

1. **Constants Matter in Practice**
   - O(n) algorithm with high constant may be slower than O(n log n) for practical n

2. **Input Size Matters**
   - O(n²) can be faster than O(n log n) for small n

3. **Best, Average, Worst Cases**
   - Quick sort: O(n log n) average, O(n²) worst
   - Always consider which case matters for your application

## Summary

| Growth Rate | Name | Example |
|------------|------|---------|
| O(1) | Constant | Array access |
| O(log n) | Logarithmic | Binary search |
| O(n) | Linear | Linear search |
| O(n log n) | Linearithmic | Merge sort |
| O(n²) | Quadratic | Bubble sort |
| O(2ⁿ) | Exponential | Recursive Fibonacci |
| O(n!) | Factorial | Permutations |

**Key Takeaway**: Focus on the dominant term as n grows large, drop constants and lower-order terms.
