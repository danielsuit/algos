# Proofs of Greedy Algorithm Correctness

## Exchange Argument

### Definition
Show that any optimal solution can be transformed into the greedy solution through a series of exchanges, without decreasing the solution quality.

### Template
1. Assume optimal solution O differs from greedy solution G
2. Find first difference between O and G
3. Show we can exchange elements to make O more like G
4. Prove exchange doesn't worsen O
5. Repeat until O = G, concluding greedy is optimal

---

## Proof 1: Activity Selection

**Problem**: Select maximum number of non-overlapping activities

**Greedy**: Choose activity with earliest finish time

**Proof by Exchange**:
- Let A = {a₁, ..., aₙ} be greedy solution (sorted by finish time)
- Let O = {o₁, ..., oₘ} be any optimal solution
- Assume O ≠ A

**Exchange**:
- If o₁ ≠ a₁, replace o₁ with a₁
- a₁ finishes earliest, so compatible with remaining activities
- |O'| = |O|, still optimal
- Repeat until O = A
- Therefore |A| = |O|, greedy optimal ✓

---

## Proof 2: Fractional Knapsack

**Problem**: Maximize value with fractional items allowed

**Greedy**: Take items in decreasing order of value/weight ratio

**Proof by Exchange**:
- Let G be greedy solution, O be optimal
- Items sorted by ratio: r₁ ≥ r₂ ≥ ... ≥ rₙ

**Suppose** O takes less of item i than G, and more of item j where j > i
- Therefore rᵢ > rⱼ (by sorting)
- Exchange: Take δ more of i, δ less of j (same weight)
- Value change: Δv = δ(rᵢwᵢ - rⱼwⱼ)/wᵢwⱼ > 0
- Contradiction: O not optimal!
- Therefore O must equal G ✓

---

## Proof 3: Huffman Coding

**Problem**: Optimal prefix-free binary encoding

**Greedy**: Repeatedly merge two least frequent symbols

**Lemma 1**: In any optimal tree, two least frequent symbols x, y are sibling leaves at maximum depth

**Proof**:
- Suppose x at depth dₓ, y at deeper depth dᵧ
- Let z be sibling of x
- Cost difference if we swap y and z:
  - Δcost = fᵧ(dₓ - dᵧ) + f_z(dᵧ - dₓ)
  - = (fᵧ - f_z)(dₓ - dᵧ)
  - < 0 since fᵧ ≤ f_z and dₓ < dᵧ
- Swapping reduces cost, contradiction!
- Therefore x, y must be siblings at max depth ✓

**Lemma 2**: If x, y merged into z, optimal tree for n symbols uses optimal tree for n-1

**Proof**:
- By Lemma 1, can treat z as single symbol with frequency fₓ + fᵧ
- Any improvement to (n-1) tree improves n-symbol tree
- Therefore must be optimal ✓

**Conclusion**: Greedy algorithm builds optimal tree by induction ✓

---

## Proof 4: Minimizing Average Completion Time

**Problem**: Schedule jobs to minimize average completion time

**Greedy**: Process jobs in increasing order of processing time (Shortest Job First)

**Proof by Exchange**:
- Let S be any schedule
- Suppose jobs i, j are adjacent with tᵢ > tⱼ (wrong order)
- Completion times before swap: Cᵢ = ..., Cⱼ = ... + tᵢ
- Completion times after swap: Cᵢ' = ... + tⱼ, Cⱼ' = ...
- Change in total: Δ = (Cᵢ' + Cⱼ') - (Cᵢ + Cⱼ) = tⱼ - tᵢ < 0
- Swapping reduces total completion time
- Keep swapping until fully sorted (greedy)
- Therefore greedy is optimal ✓

---

## Proof 5: Dijkstra's Algorithm

**Problem**: Shortest paths from source in weighted graph

**Greedy**: Always extend shortest known path

**Proof by Exchange (Contradiction)**:
- Suppose Dijkstra wrong: vertex v has dist[v] > shortest path length
- Let P be true shortest path to v: s → ... → u → v
- Since dist[v] wrong, some vertex on P has wrong distance
- Let x be first such vertex on P
- All predecessors of x on P have correct distances (by choice of x)
- When Dijkstra visited x's predecessor, it would have updated dist[x] correctly
- Contradiction!
- Therefore Dijkstra always finds shortest paths ✓

---

## Proof 6: Minimum Spanning Tree (Kruskal's)

**Problem**: Find minimum weight spanning tree

**Greedy**: Add cheapest edge that doesn't create cycle

**Proof by Cut Property**:
- Let S ⊆ V be any subset of vertices
- Let e = (u,v) be minimum weight edge crossing cut (S, V\S)
- **Claim**: Some MST contains e

**Proof**:
- Suppose MST T doesn't contain e
- Adding e to T creates cycle C
- C must have another edge e' crossing (S, V\S)
- Since e is minimum crossing edge: w(e) ≤ w(e')
- T' = T - e' + e is spanning tree with w(T') ≤ w(T)
- Therefore T' is also MST containing e ✓

**Kruskal's Correctness**:
- Each edge e added by Kruskal crosses some cut
- e is minimum weight edge in that cut (by greedy choice)
- By cut property, e is in some MST
- By induction, Kruskal builds an MST ✓

---

## Proof 7: Prim's Algorithm

**Problem**: Find minimum spanning tree

**Greedy**: Grow tree by adding cheapest edge from tree to non-tree vertex

**Proof**:
- Similar to Kruskal's using cut property
- At each step, consider cut (S, V\S) where S = vertices in current tree
- Prim's adds minimum weight edge crossing this cut
- By cut property, this edge is in some MST
- Therefore Prim's builds an MST ✓

---

## Proof 8: Earliest Deadline First (EDF)

**Problem**: Schedule jobs with deadlines to minimize lateness

**Greedy**: Process jobs in order of earliest deadline

**Proof by Exchange**:
- Let S be any schedule with inversion: i scheduled before j but dᵢ > dⱼ
- Swap i and j
- Lateness of i: max(0, Cᵢ - dᵢ)
  - Before: max(0, Cᵢ - dᵢ)
  - After: max(0, Cᵢ + tⱼ - tᵢ - dᵢ) ≥ max(0, Cᵢ - dᵢ)
- Lateness of j:
  - Before: max(0, Cᵢ + tⱼ - dⱼ)
  - After: max(0, Cᵢ - dⱼ) ≤ max(0, Cᵢ + tⱼ - dⱼ) [since dⱼ < dᵢ]
- Maximum lateness doesn't increase!
- Keep swapping until EDF order achieved ✓

---

## General Proof Strategies

### 1. Direct Exchange
Show swapping greedy choice with any other choice maintains/improves solution

### 2. Contradiction
Assume optimal differs from greedy, derive contradiction

### 3. Induction
Prove greedy stays ahead at each step

### 4. Cut Property
For graph problems, show greedy respects optimal cuts

### 5. Structural
Show greedy builds optimal substructure

## Summary Table

| Algorithm | Problem | Proof Technique |
|-----------|---------|-----------------|
| Activity Selection | Scheduling | Exchange |
| Fractional Knapsack | Optimization | Exchange |
| Huffman Coding | Encoding | Structural + Induction |
| Shortest Job First | Scheduling | Exchange |
| Dijkstra | Shortest Path | Contradiction |
| Kruskal | MST | Cut Property |
| Prim | MST | Cut Property |
| EDF | Deadline Scheduling | Exchange |

**Key Insight**: Most greedy proofs show you can safely transform any solution into the greedy solution without losing optimality.
