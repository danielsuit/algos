# Mathematical Induction

## Overview
Mathematical induction is a proof technique used to prove statements about natural numbers or recursive structures. It's fundamental to proving algorithm correctness.

## Principle of Mathematical Induction

To prove a statement P(n) is true for all n ≥ n₀:

1. **Base Case**: Prove P(n₀) is true
2. **Inductive Hypothesis**: Assume P(k) is true for some arbitrary k ≥ n₀
3. **Inductive Step**: Prove P(k+1) is true using the assumption that P(k) is true

**Conclusion**: By induction, P(n) is true for all n ≥ n₀

## Simple Induction Examples

### Example 1: Sum of First n Natural Numbers

**Claim**: $\sum_{i=1}^{n} i = \frac{n(n+1)}{2}$ for all n ≥ 1

**Proof**:

1. **Base Case** (n = 1):
   - Left side: 1
   - Right side: $\frac{1(1+1)}{2} = 1$ ✓

2. **Inductive Hypothesis**: Assume true for n = k:
   - $\sum_{i=1}^{k} i = \frac{k(k+1)}{2}$

3. **Inductive Step**: Prove for n = k+1:
   ```
   ∑(i=1 to k+1) i = (∑(i=1 to k) i) + (k+1)
                   = k(k+1)/2 + (k+1)        [by hypothesis]
                   = [k(k+1) + 2(k+1)] / 2
                   = (k+1)(k+2) / 2
                   = (k+1)((k+1)+1) / 2      ✓
   ```

**Conclusion**: Formula holds for all n ≥ 1

### Example 2: Power of 2

**Claim**: $2^n > n$ for all n ≥ 1

**Proof**:

1. **Base Case** (n = 1):
   - $2^1 = 2 > 1$ ✓

2. **Inductive Hypothesis**: Assume $2^k > k$ for some k ≥ 1

3. **Inductive Step**: Prove $2^{k+1} > k+1$:
   ```
   2^(k+1) = 2 · 2^k
           > 2 · k        [by hypothesis]
           = k + k
           ≥ k + 1        [since k ≥ 1]
   Therefore, 2^(k+1) > k+1  ✓
   ```

## Strong Induction

Sometimes we need to assume the statement is true for **all** values up to k, not just k itself.

**Strong Induction Principle**:
1. **Base Case(s)**: Prove P(n₀), P(n₀+1), ..., P(n₀+m)
2. **Strong Inductive Hypothesis**: Assume P(i) is true for all n₀ ≤ i ≤ k
3. **Inductive Step**: Prove P(k+1) is true

### Example: Fibonacci Numbers

**Claim**: Every Fibonacci number F(n) ≥ φⁿ⁻² where φ = (1+√5)/2 ≈ 1.618 (golden ratio)

Fibonacci: F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)

**Proof using Strong Induction**:

1. **Base Cases**:
   - n=0: F(0) = 0 ≥ φ⁻² ≈ 0.382 ✗ (need to start at n=2)
   - n=2: F(2) = 1 ≥ φ⁰ = 1 ✓
   - n=3: F(3) = 2 ≥ φ¹ ≈ 1.618 ✓

2. **Strong Hypothesis**: Assume F(i) ≥ φⁱ⁻² for all 2 ≤ i ≤ k

3. **Inductive Step**: Prove F(k+1) ≥ φᵏ⁻¹:
   ```
   F(k+1) = F(k) + F(k-1)
          ≥ φ^(k-2) + φ^(k-3)        [by hypothesis]
          = φ^(k-3)(φ + 1)
          = φ^(k-3) · φ²             [golden ratio property: φ² = φ + 1]
          = φ^(k-1)                  ✓
   ```

## Structural Induction

Used for recursively defined structures (trees, lists, etc.)

**Principle**:
1. **Base Case**: Prove for simplest structure
2. **Inductive Step**: Assume true for smaller structures, prove for combined structure

### Example: Binary Tree Height

**Claim**: A binary tree with n nodes has height h ≥ log₂(n+1) - 1

**Proof**:

1. **Base Case**: Empty tree (n=0), height = -1
   - log₂(0+1) - 1 = 0 - 1 = -1 ✓

2. **Inductive Hypothesis**: Assume true for trees with < n nodes

3. **Inductive Step**: For tree with n nodes:
   - Tree has root + left subtree (nₗ nodes) + right subtree (nᵣ nodes)
   - n = 1 + nₗ + nᵣ
   - By hypothesis: h ≥ max(hₗ, hᵣ) + 1
   - Where hₗ ≥ log₂(nₗ+1) - 1 and hᵣ ≥ log₂(nᵣ+1) - 1

## Application to Algorithm Correctness

### Loop Invariants

Use induction to prove loops are correct:

**Loop Invariant**: A property that is true:
- Before the loop (initialization)
- Before each iteration (maintenance)
- After the loop (termination)

### Example: Insertion Sort Correctness

```cpp
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        // Invariant: arr[0..i-1] is sorted
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
        // Invariant: arr[0..i] is sorted
    }
}
```

**Proof of Correctness**:

1. **Initialization**: Before first iteration (i=1), arr[0..0] is trivially sorted ✓

2. **Maintenance**: Assume arr[0..i-1] is sorted
   - Insert arr[i] into correct position in arr[0..i-1]
   - After insertion, arr[0..i] is sorted ✓

3. **Termination**: When loop ends, i = n
   - arr[0..n-1] is sorted ✓

## Common Induction Mistakes

1. **Missing Base Case**: Always verify base case explicitly
2. **Incorrect Assumption**: Don't assume what you're trying to prove
3. **Gap in Logic**: Ensure inductive step clearly uses the hypothesis
4. **Wrong Direction**: For P(k) → P(k+1), start with P(k+1) and work backwards to P(k)

## Practice Problems

1. Prove: $\sum_{i=0}^{n} 2^i = 2^{n+1} - 1$

2. Prove: $\sum_{i=1}^{n} i^2 = \frac{n(n+1)(2n+1)}{6}$

3. Prove: Every amount of postage ≥ 12 cents can be formed using 4-cent and 5-cent stamps

4. Prove: Every binary tree with n internal nodes has n+1 leaves

5. Prove correctness of binary search algorithm

## Key Takeaways

- Induction is essential for proving:
  - Formulas involving n
  - Algorithm correctness
  - Properties of recursive structures

- **Simple induction**: Assume P(k), prove P(k+1)
- **Strong induction**: Assume P(i) for all i ≤ k, prove P(k+1)
- **Structural induction**: For recursive data structures

- Always include:
  1. Clear statement of what you're proving
  2. Base case verification
  3. Explicit inductive hypothesis
  4. Logical inductive step
  5. Conclusion
