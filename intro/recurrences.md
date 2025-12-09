# Solving Recurrence Relations

## Overview
Recurrence relations describe the runtime of recursive algorithms. Solving them helps us determine time complexity.

## Common Forms

### 1. Linear Recurrences

**General Form**: T(n) = aT(n-b) + f(n)

**Example**: T(n) = T(n-1) + c
- Solution: T(n) = O(n)
- Examples: Linear search, factorial

### 2. Divide and Conquer Recurrences

**General Form**: T(n) = aT(n/b) + f(n)
- a = number of subproblems
- n/b = size of each subproblem
- f(n) = work to divide and combine

## Methods for Solving Recurrences

## Method 1: Substitution Method

Guess the solution and verify using induction.

### Example: T(n) = 2T(n/2) + n

**Step 1**: Guess T(n) = O(n log n)

**Step 2**: Prove by induction
- Assume: T(k) ≤ ck log k for all k < n
- Prove: T(n) ≤ cn log n

```
T(n) = 2T(n/2) + n
     ≤ 2c(n/2)log(n/2) + n
     = cn(log n - log 2) + n
     = cn log n - cn + n
     ≤ cn log n  (for c ≥ 1)
```

### Steps:
1. Make an educated guess
2. Use induction to verify
3. Find constants that make it work

### Tips for Guessing:
- Look at recursion tree
- Try common forms: O(n), O(n log n), O(n²), etc.
- Use loose bounds first, then tighten

## Method 2: Recursion Tree Method

Visualize the recursion as a tree and sum up the work.

### Example: T(n) = 2T(n/2) + n

```
                    n                 Level 0: n
                  /   \
               n/2     n/2            Level 1: 2(n/2) = n
              /  \    /  \
            n/4  n/4 n/4 n/4          Level 2: 4(n/4) = n
            ...
```

**Analysis**:
- Height: log n levels
- Work per level: n
- Total: n × log n = **O(n log n)**

### Example 2: T(n) = 3T(n/2) + n²

```
                    n²                     Level 0: n²
                 /   |   \
            (n/2)² (n/2)² (n/2)²         Level 1: 3(n/2)² = (3/4)n²
           /|\   /|\   /|\
         ...   ...   ...             Level 2: 9(n/4)² = (9/16)n²
```

**Analysis**:
- Level i: 3ⁱ(n/2ⁱ)² = n²(3/4)ⁱ
- Geometric series: n²[1 + 3/4 + (3/4)² + ...]
- Sum converges: n² × 1/(1-3/4) = 4n²
- Total: **O(n²)**

### Steps:
1. Draw tree showing subproblem sizes
2. Calculate work at each level
3. Sum over all levels
4. Determine dominant term

## Method 3: Master Theorem

Direct formula for divide-and-conquer recurrences.

See [master-theorem.md](master-theorem.md) for details.

## Common Recurrence Patterns

### Pattern 1: Decrease by One

**T(n) = T(n-1) + c**
- Solution: **O(n)**
- Examples: Factorial, linear search, simple loop

**T(n) = T(n-1) + n**
- Solution: **O(n²)**
- Expansion: n + (n-1) + (n-2) + ... + 1 = n(n+1)/2

**T(n) = T(n-1) + log n**
- Solution: **O(n log n)**
- Expansion: log n + log(n-1) + ... + log 1 = log(n!)

### Pattern 2: Divide by Two

**T(n) = T(n/2) + c**
- Solution: **O(log n)**
- Examples: Binary search

**T(n) = T(n/2) + n**
- Solution: **O(n)**
- Examples: Finding median

**T(n) = 2T(n/2) + c**
- Solution: **O(n)**
- Tree has n leaves

**T(n) = 2T(n/2) + n**
- Solution: **O(n log n)**
- Examples: Merge sort, efficient polynomial multiplication

**T(n) = 2T(n/2) + n²**
- Solution: **O(n²)**

### Pattern 3: Multiple Branches

**T(n) = 2T(n-1) + c**
- Solution: **O(2ⁿ)**
- Examples: Naive Fibonacci, subset generation

**T(n) = 3T(n/2) + n**
- Solution: **O(n^log₂ 3)** ≈ O(n^1.585)

**T(n) = 4T(n/2) + n**
- Solution: **O(n²)**
- Examples: Naive matrix multiplication

**T(n) = 7T(n/2) + n²**
- Solution: **O(n^log₂ 7)** ≈ O(n^2.81)
- Examples: Strassen's matrix multiplication

### Pattern 4: Multiple Terms

**T(n) = T(n-1) + T(n-2) + c**
- Solution: **O(φⁿ)** where φ = (1+√5)/2 ≈ 1.618
- Examples: Fibonacci numbers

## Techniques for Specific Cases

### Telescoping

For recurrences like T(n) = T(n-1) + f(n):

```
T(n) = T(n-1) + f(n)
T(n-1) = T(n-2) + f(n-1)
...
T(2) = T(1) + f(2)

Sum all:
T(n) = T(1) + ∑(i=2 to n) f(i)
```

### Change of Variables

For T(n) = 2T(√n) + log n:

Let m = log n, so n = 2ᵐ

S(m) = T(2ᵐ) = 2T(2ᵐᵏ²) + m = 2S(m/2) + m

Solve S(m) = O(m log m)

Therefore T(n) = O(log n × log log n)

## Verification Techniques

### 1. Plug in Small Values

For T(n) = 2T(n/2) + n, T(1) = 1:

```
T(1) = 1
T(2) = 2T(1) + 2 = 2 + 2 = 4 = 2 × 2 × log 2
T(4) = 2T(2) + 4 = 8 + 4 = 12 = 4 × 3 = 4 × log 4 × (3/2)
T(8) = 2T(4) + 8 = 24 + 8 = 32 = 8 × 4 = 8 × log 8 × (4/3)

Pattern suggests O(n log n)
```

### 2. Expansion

For T(n) = 3T(n/4) + n:

```
T(n) = 3T(n/4) + n
     = 3[3T(n/16) + n/4] + n
     = 9T(n/16) + (3/4)n + n
     = 9[3T(n/64) + n/16] + (3/4)n + n
     = 27T(n/64) + (9/16)n + (3/4)n + n
     ...
     = n[1 + 3/4 + (3/4)² + ...]
     = n × 4 = O(n)
```

## Common Mistakes

1. **Forgetting Base Case**: Always specify T(1) or T(0)

2. **Incorrect Recursion Depth**: 
   - For T(n/2): depth is log n
   - For T(n-1): depth is n

3. **Ignoring Floor/Ceiling**: 
   - T(n/2) vs T(⌊n/2⌋) can matter for proof

4. **Wrong Master Theorem Case**: Verify which case applies

## Practice Problems

1. T(n) = 4T(n/2) + n
   - Answer: O(n²)

2. T(n) = T(n/3) + T(2n/3) + n
   - Answer: O(n log n) [Advanced]

3. T(n) = 2T(n-1) + 1
   - Answer: O(2ⁿ)

4. T(n) = T(n-1) + 1/n
   - Answer: O(log n) [Sum is harmonic series]

5. T(n) = √n T(√n) + n
   - Answer: O(n log log n) [Use change of variables]

## Summary

| Method | Best For | Difficulty |
|--------|----------|------------|
| Substitution | Verifying guess | Medium |
| Recursion Tree | Getting intuition | Easy |
| Master Theorem | Standard D&C | Easy |
| Expansion | Simple recurrences | Medium |

**Key Steps**:
1. Identify recurrence pattern
2. Choose appropriate method
3. Calculate/derive solution
4. Verify with small values
5. Express in asymptotic notation
