# Master Theorem

## Overview
The Master Theorem provides a cookbook solution for divide-and-conquer recurrences of the form:

**T(n) = aT(n/b) + f(n)**

Where:
- **a ≥ 1**: Number of recursive subproblems
- **b > 1**: Factor by which problem size is reduced
- **f(n)**: Work done outside recursive calls (divide + combine)

## The Three Cases

Compare f(n) with n^(log_b a):

### Case 1: Recursion Dominates
**If f(n) = O(n^(log_b a - ε)) for some ε > 0**

Then: **T(n) = Θ(n^(log_b a))**

**Intuition**: Recursive calls do more work than combining

**Example**: T(n) = 8T(n/2) + n²
- a = 8, b = 2, f(n) = n²
- n^(log_b a) = n^(log₂ 8) = n³
- f(n) = n² = O(n³⁻ᵋ) for ε = 1
- **Answer: T(n) = Θ(n³)**

### Case 2: Balanced Work
**If f(n) = Θ(n^(log_b a) log^k n) for some k ≥ 0**

Then: **T(n) = Θ(n^(log_b a) log^(k+1) n)**

**Intuition**: Work at each level is roughly equal

**Example 1**: T(n) = 2T(n/2) + n (k=0)
- a = 2, b = 2, f(n) = n
- n^(log_b a) = n^(log₂ 2) = n
- f(n) = Θ(n log⁰ n) = Θ(n)
- **Answer: T(n) = Θ(n log n)**

**Example 2**: T(n) = 2T(n/2) + n log n (k=1)
- f(n) = Θ(n log¹ n)
- **Answer: T(n) = Θ(n log² n)**

### Case 3: Combine Dominates
**If f(n) = Ω(n^(log_b a + ε)) for some ε > 0**

**AND regularity condition**: af(n/b) ≤ cf(n) for some c < 1

Then: **T(n) = Θ(f(n))**

**Intuition**: Combining work dominates recursive calls

**Example**: T(n) = 2T(n/2) + n²
- a = 2, b = 2, f(n) = n²
- n^(log_b a) = n
- f(n) = n² = Ω(n¹⁺ᵋ) for ε = 1
- Regularity: 2(n/2)² = n²/2 ≤ (1/2)n² ✓
- **Answer: T(n) = Θ(n²)**

## Quick Reference Table

| Recurrence | a | b | log_b a | f(n) | Case | Solution |
|------------|---|---|---------|------|------|----------|
| T(n) = T(n/2) + 1 | 1 | 2 | 0 | 1 | 2 | O(log n) |
| T(n) = 2T(n/2) + 1 | 2 | 2 | 1 | 1 | 1 | O(n) |
| T(n) = 2T(n/2) + n | 2 | 2 | 1 | n | 2 | O(n log n) |
| T(n) = 2T(n/2) + n² | 2 | 2 | 1 | n² | 3 | O(n²) |
| T(n) = 4T(n/2) + n | 4 | 2 | 2 | n | 1 | O(n²) |
| T(n) = 4T(n/2) + n² | 4 | 2 | 2 | n² | 2 | O(n² log n) |
| T(n) = 4T(n/2) + n³ | 4 | 2 | 2 | n³ | 3 | O(n³) |
| T(n) = 3T(n/2) + n | 3 | 2 | ~1.585 | n | 1 | O(n^1.585) |
| T(n) = 7T(n/2) + n² | 7 | 2 | ~2.807 | n² | 1 | O(n^2.807) |
| T(n) = T(n/3) + 1 | 1 | 3 | 0 | 1 | 2 | O(log n) |

## Algorithm Examples

### Binary Search
```cpp
T(n) = T(n/2) + O(1)
```
- a = 1, b = 2, f(n) = 1
- n^(log₂ 1) = n⁰ = 1
- f(n) = Θ(n⁰ log⁰ n) = Θ(1)
- **Case 2**: T(n) = Θ(log n)

### Merge Sort
```cpp
T(n) = 2T(n/2) + O(n)
```
- a = 2, b = 2, f(n) = n
- n^(log₂ 2) = n
- f(n) = Θ(n log⁰ n) = Θ(n)
- **Case 2**: T(n) = Θ(n log n)

### Karatsuba Multiplication
```cpp
T(n) = 3T(n/2) + O(n)
```
- a = 3, b = 2, f(n) = n
- n^(log₂ 3) ≈ n^1.585
- f(n) = O(n^(1.585 - 0.585)) = O(n^(log₂ 3 - ε))
- **Case 1**: T(n) = Θ(n^1.585)

### Strassen's Matrix Multiplication
```cpp
T(n) = 7T(n/2) + O(n²)
```
- a = 7, b = 2, f(n) = n²
- n^(log₂ 7) ≈ n^2.807
- f(n) = O(n²) = O(n^(2.807 - 0.807))
- **Case 1**: T(n) = Θ(n^2.807)

### Selection (finding k-th element)
```cpp
T(n) = T(n/2) + O(n)
```
- a = 1, b = 2, f(n) = n
- n^(log₂ 1) = 1
- f(n) = n = Ω(n^(0+1))
- Regularity: (n/2) ≤ (1/2)n ✓
- **Case 3**: T(n) = Θ(n)

### Matrix Multiplication (naive)
```cpp
T(n) = 8T(n/2) + O(n²)
```
- a = 8, b = 2, f(n) = n²
- n^(log₂ 8) = n³
- f(n) = O(n²) = O(n^(3-1))
- **Case 1**: T(n) = Θ(n³)

## Step-by-Step Application

### Example: T(n) = 4T(n/2) + n log n

**Step 1**: Identify parameters
- a = 4
- b = 2
- f(n) = n log n

**Step 2**: Calculate n^(log_b a)
- log₂ 4 = 2
- n^(log_b a) = n²

**Step 3**: Compare f(n) with n^(log_b a)
- f(n) = n log n
- n^(log_b a) = n²
- n log n = O(n²⁻ᵋ) for ε = 1? 
  - Need: n log n ≤ c × n²⁻¹ = cn for some c
  - This is FALSE (log n grows unbounded)
- n log n = O(n²⁻ᵋ) for small ε?
  - n log n = O(n^(2-ε)) requires log n = O(n^(-ε))
  - This is TRUE for any ε < 1

**Step 4**: Apply Case 1
- **Answer: T(n) = Θ(n²)**

## When Master Theorem Doesn't Apply

Master Theorem requires specific form. It **doesn't work** for:

### 1. Non-constant a or b
```cpp
T(n) = nT(n/2) + n²  // a depends on n
```

### 2. Subproblem sizes don't divide evenly
```cpp
T(n) = T(n/3) + T(2n/3) + n  // Different subproblem sizes
```

### 3. f(n) doesn't fit any case
```cpp
T(n) = 2T(n/2) + n/log n  // Gap between cases
```

### 4. Negative or fractional parameters
```cpp
T(n) = T(n-1) + 1  // Not divide-and-conquer form
```

For these cases, use:
- Substitution method
- Recursion tree method
- Akra-Bazzi theorem (generalization)

## Extended Master Theorem

For cases where regular Master Theorem doesn't apply:

**If f(n) = Θ(n^(log_b a) log^k n)** for any k (including negative):

- k > -1: **T(n) = Θ(n^(log_b a) log^(k+1) n)**
- k = -1: **T(n) = Θ(n^(log_b a) log log n)**
- k < -1: **T(n) = Θ(n^(log_b a))**

## Common Patterns Recognition

### Pattern: One subproblem
- **T(n) = T(n/b) + f(n)** → Usually O(f(n)) if f(n) ≥ log n
- Binary search: T(n) = T(n/2) + O(1) = O(log n)

### Pattern: Balanced split
- **T(n) = 2T(n/2) + O(n)** → O(n log n)
- Merge sort, quicksort (average)

### Pattern: Unbalanced but still divide-and-conquer
- **T(n) = T(n/3) + T(2n/3) + O(n)** → O(n log n)
- Use recursion tree, depth is log_{3/2} n

## Practice Problems

Determine time complexity:

1. T(n) = 16T(n/4) + n
2. T(n) = 2T(n/2) + n log n
3. T(n) = 3T(n/3) + n
4. T(n) = 3T(n/3) + n²
5. T(n) = T(n/2) + log n
6. T(n) = 2T(n/4) + √n
7. T(n) = 9T(n/3) + n² log n
8. T(n) = T(n/2) + 2ⁿ

### Solutions:
1. O(n²) - Case 2
2. O(n log² n) - Case 2 with k=1
3. O(n log n) - Case 2
4. O(n²) - Case 3
5. O(log n) - Case 2 (a=1)
6. O(√n log n) - Case 2
7. O(n² log² n) - Case 2 with k=1
8. Not applicable - f(n) grows exponentially

## Summary

**Master Theorem Quick Guide**:

1. Calculate n^(log_b a)
2. Compare with f(n):
   - **f(n) polynomially smaller** → Case 1 → T(n) = Θ(n^(log_b a))
   - **f(n) same (times log^k)** → Case 2 → T(n) = Θ(n^(log_b a) log^(k+1) n)
   - **f(n) polynomially larger** → Case 3 → T(n) = Θ(f(n))

3. For Case 3, verify regularity condition

**Key Insight**: Master Theorem tells us which part of the algorithm dominates:
- **Case 1**: Leaves of recursion tree (subproblems)
- **Case 2**: Equal work at all levels
- **Case 3**: Root of recursion tree (combining)
