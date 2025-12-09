# Greedy Algorithm Correctness Proofs

## Overview
The "greedy stays ahead" technique proves that greedy algorithms produce optimal solutions by showing the greedy solution is always at least as good as any other solution at every step.

## Proof Structure

### 1. Greedy Stays Ahead Argument

**Steps**:
1. Define a **measure of progress** for solutions
2. Show greedy solution makes optimal progress at each step
3. Prove greedy solution "stays ahead" of any other solution
4. Conclude greedy gives optimal final solution

### Example: Interval Scheduling

**Problem**: Select maximum number of non-overlapping intervals

**Greedy Algorithm**: Always pick interval that ends earliest

**Proof**:
- Let G = {g₁, g₂, ..., gₖ} be greedy solution
- Let O = {o₁, o₂, ..., oₘ} be any optimal solution
- Both sorted by end time

**Claim**: For all i, gᵢ ends no later than oᵢ

**Proof by Induction**:

*Base case* (i=1): 
- g₁ has earliest end time by greedy choice
- Therefore g₁.end ≤ o₁.end ✓

*Inductive step*: Assume gᵢ.end ≤ oᵢ.end
- Next interval gᵢ₊₁ chosen must start after gᵢ.end
- Since gᵢ.end ≤ oᵢ.end, gᵢ₊₁ also compatible with oᵢ.end
- By greedy choice, gᵢ₊₁.end ≤ oᵢ₊₁.end ✓

**Conclusion**: 
- If m > k, we could add oₘ after gₖ (since gₖ.end ≤ oₘ.start)
- Contradiction with G being greedy solution
- Therefore k = m, greedy is optimal ✓

## 2. Exchange Argument

Show you can transform any optimal solution into greedy solution without making it worse.

### Example: Fractional Knapsack

**Problem**: Maximize value with fractional items

**Greedy**: Take items by value/weight ratio

**Proof**:
- Suppose optimal O differs from greedy G
- Let x be first item where O takes less than G
- Let y be item where O takes more (to maintain weight)
- Exchange: increase x, decrease y by same weight
- Value change: Δv = (vₓ/wₓ - vᵧ/wᵧ) × Δw
- Since vₓ/wₓ > vᵧ/wᵧ (greedy order), Δv > 0
- Contradiction: O not optimal ✓

## 3. Structural Induction

Prove greedy builds optimal substructure.

### Example: Huffman Coding

**Greedy**: Merge two least frequent symbols

**Lemma 1**: In optimal tree, two least frequent symbols are siblings at deepest level

**Proof**: 
- Suppose not; one is higher in tree
- Swapping with leaf increases cost (less frequent higher)
- Contradiction ✓

**Lemma 2**: Optimal encoding for n symbols uses optimal encoding for n-1

**Proof by Induction**: Base on Lemma 1 ✓

## 4. Cut-and-Paste Argument

Show any deviation from greedy can be "cut" and "pasted" to match greedy.

### Example: Minimum Spanning Tree (Kruskal's)

**Greedy**: Add cheapest edge that doesn't create cycle

**Proof**:
- Let T be MST, e be greedy edge not in T
- Adding e to T creates cycle C
- C must have edge e' heavier than e (else greedy would pick e' first)
- Replace e' with e: still spanning, lower weight
- Contradiction: T not minimum ✓

## 5. Matroid Theory

Advanced framework for proving greedy correctness.

**Matroid** (S, I) where:
- S = ground set
- I = independent sets

**Properties**:
1. ∅ ∈ I
2. If B ∈ I and A ⊆ B, then A ∈ I (hereditary)
3. If A, B ∈ I and |A| < |B|, then ∃x ∈ B \ A such that A ∪ {x} ∈ I (exchange)

**Theorem**: Greedy algorithm finds maximum weight independent set in matroid.

**Examples**:
- Graphic matroid (MST)
- Scheduling matroid
- Partition matroid

## Common Greedy Patterns

### 1. Earliest Finish Time
- **Use**: Interval scheduling, task scheduling
- **Proof**: Greedy stays ahead

### 2. Highest Value/Cost Ratio
- **Use**: Fractional knapsack, resource allocation
- **Proof**: Exchange argument

### 3. Smallest Edge Weight
- **Use**: MST (Kruskal, Prim)
- **Proof**: Cut-and-paste

### 4. Shortest Job First
- **Use**: Minimizing average completion time
- **Proof**: Exchange argument

### 5. Merge Smallest Pairs
- **Use**: Huffman coding, optimal BST
- **Proof**: Structural induction

## Proving Greedy is WRONG

To show greedy doesn't work, find a **counterexample**:

### Example: 0/1 Knapsack

**Greedy**: Take highest value/weight ratio
**Counterexample**:
- Items: (w=10, v=60), (w=20, v=100)
- Capacity: 20
- Greedy picks (10,60), gets 60
- Optimal picks (20,100), gets 100
- Greedy fails! ✗

## When Does Greedy Work?

✓ **Greedy Choice Property**: Locally optimal choice leads to globally optimal solution

✓ **Optimal Substructure**: Optimal solution contains optimal solutions to subproblems

✓ **No dependencies**: Choices don't affect future choices

✗ **Fails when**:
- Choices have future consequences
- Need to "look ahead"
- Multiple constraints interact

## Summary

| Technique | Best For | Difficulty |
|-----------|----------|------------|
| Greedy Stays Ahead | Scheduling | Easy |
| Exchange Argument | Optimization | Medium |
| Cut-and-Paste | Graph problems | Medium |
| Structural Induction | Hierarchical | Hard |
| Matroid Theory | General framework | Hard |

**Key Steps**:
1. Clearly state greedy choice
2. Prove it's safe (doesn't eliminate optimal solution)
3. Show optimal substructure remains
4. Conclude by induction/exchange
