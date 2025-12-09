# Complexity Classes and Reductions

## Table of Contents
1. [Introduction](#introduction)
2. [Complexity Classes](#complexity-classes)
3. [NP-Completeness](#np-completeness)
4. [Reductions](#reductions)
5. [Classic NP-Complete Problems](#classic-np-complete-problems)
6. [Implications](#implications)

---

## Introduction

**Computational Complexity Theory** classifies problems based on the resources (time, space) required to solve them.

### Decision vs. Optimization

**Decision Problem**: Yes/No answer
```
"Does there exist a solution with value ≥ k?"
```

**Optimization Problem**: Find best solution
```
"Find the maximum value solution"
```

**Relationship**: If optimization is easy, decision is easy. If decision is hard, optimization is hard.

---

## Complexity Classes

### P (Polynomial Time)

**Definition**: Problems solvable in polynomial time O(nᵏ) for some constant k.

**Examples**:
- Sorting: O(n log n)
- Shortest path (Dijkstra): O(V²) or O(E log V)
- Maximum flow: O(V²E) or O(VE²)
- Linear programming: O(n³·⁵)

**Property**: Closed under composition
- If A ∈ P and B ∈ P, then A composed with B ∈ P

### NP (Nondeterministic Polynomial)

**Definition**: Problems where a solution can be **verified** in polynomial time.

**Formal**: A problem is in NP if there exists:
1. A certificate (proof/solution) of polynomial size
2. A polynomial-time algorithm to verify the certificate

**Examples**:
- **Hamiltonian Cycle**: Given cycle, verify in O(n) time
- **3-SAT**: Given assignment, verify in O(n) time
- **Subset Sum**: Given subset, verify sum in O(n) time
- **Graph Coloring**: Given coloring, verify in O(E) time

**Key Point**: NP does NOT mean "non-polynomial" or "not polynomial"!

### Relationship: P ⊆ NP

If we can solve a problem in polynomial time, we can certainly verify it in polynomial time.

**The Million Dollar Question**: **P = NP ?**

Most believe P ≠ NP, but no proof exists!

```
If P = NP:
  - Every efficiently verifiable problem is efficiently solvable
  - Cryptography breaks
  - Many optimization problems become easy
  
If P ≠ NP:
  - Some problems are fundamentally hard
  - Verification easier than solution
  - Current cryptography secure
```

### NP-Hard

**Definition**: A problem H is NP-hard if every problem in NP can be reduced to H in polynomial time.

**Informal**: "At least as hard as the hardest problems in NP"

**Properties**:
- May not be in NP (no polynomial verification)
- May not be decision problems

**Examples**:
- Traveling Salesman (optimization version)
- General game playing
- Halting problem (even harder!)

### NP-Complete

**Definition**: A problem is NP-complete if:
1. It is in NP (polynomial-time verifiable)
2. It is NP-hard (every NP problem reduces to it)

**Significance**: The "hardest" problems in NP

**Property**: If any NP-complete problem can be solved in polynomial time, then P = NP!

```
    NP-Hard
   ┌─────────────┐
   │             │
   │  NP-Complete│
   │  ┌────────┐ │
   │  │   P    │ │
   │  │        │ │
   │  └────────┘ │
   │             │
   └─────────────┘
```

### Other Classes

**co-NP**: Complement of NP
- Problems where "no" answers have polynomial certificates
- Example: "Is this graph NOT 3-colorable?"

**PSPACE**: Problems solvable in polynomial space
- Includes NP (time ≤ space)
- Games with perfect information

**EXP**: Problems solvable in exponential time
- Contains NP and PSPACE

```
P ⊆ NP ⊆ PSPACE ⊆ EXP
```

---

## NP-Completeness

### Cook-Levin Theorem (1971)

**SAT (Boolean Satisfiability) is NP-complete**

This was the **first** NP-complete problem proven!

**Proof sketch**:
1. SAT ∈ NP: Easy to verify assignment
2. Every NP problem reduces to SAT: Encode computation as Boolean formula

### Proving NP-Completeness

To show problem X is NP-complete:

```
1. Show X ∈ NP
   - Provide polynomial-time verification algorithm
   - Describe certificate structure

2. Show X is NP-hard
   - Choose known NP-complete problem Y
   - Construct polynomial-time reduction Y ≤ₚ X
   - Prove reduction correctness
```

### Reduction Strategy

```
Known NP-Complete → New Problem
     (reduce)
     
If we can solve New Problem efficiently,
we can solve Known Problem efficiently.
```

**Chain of Reductions**:
```
SAT → 3-SAT → Vertex Cover → Hamiltonian Cycle → TSP
  ↘                              ↗
    Clique → Independent Set
```

---

## Reductions

### Polynomial-Time Reduction

**Definition**: Problem A reduces to problem B (A ≤ₚ B) if:
- There exists polynomial-time function f
- For any instance x of A: x is a "yes" instance iff f(x) is a "yes" instance of B

**Properties**:
- Transitive: If A ≤ₚ B and B ≤ₚ C, then A ≤ₚ C
- If A ≤ₚ B and B ∈ P, then A ∈ P

### Types of Reductions

#### 1. Many-One Reduction
Transform one problem instance to another
```
A ≤ₚ B means: solver for B ⟹ solver for A
```

#### 2. Turing Reduction  
Use oracle for B to solve A (can call multiple times)

#### 3. Karp Reduction
Polynomial-time many-one reduction (most common)

### Example Reduction: 3-SAT ≤ₚ Clique

**Goal**: Show Clique is NP-complete

**Given**: 3-SAT instance with clauses C₁, C₂, ..., Cₖ

**Construct Graph**:
1. For each clause Cᵢ with 3 literals, create 3 nodes
2. Connect two nodes if:
   - They are from different clauses
   - They are not negations of each other

**Claim**: 3-SAT has satisfying assignment ⟺ Graph has clique of size k

**Example**:
```
3-SAT: (x ∨ y ∨ z) ∧ (¬x ∨ ¬y ∨ w)

Graph:
  Clause 1: nodes {x, y, z}
  Clause 2: nodes {¬x, ¬y, w}
  
Edges: All pairs except (x,¬x), (y,¬y)

Clique of size 2 = satisfying assignment exists
```

---

## Classic NP-Complete Problems

### 1. SAT (Boolean Satisfiability)

**Problem**: Given Boolean formula, is there an assignment making it true?

**Input**: (x₁ ∨ ¬x₂) ∧ (x₂ ∨ x₃) ∧ ...

**First** NP-complete problem (Cook-Levin)

### 2. 3-SAT

**Problem**: SAT where each clause has exactly 3 literals

**Input**: (x ∨ y ∨ z) ∧ (¬x ∨ w ∨ ¬z) ∧ ...

**Note**: 2-SAT is in P! (solvable in O(n))

### 3. Vertex Cover

**Problem**: Select k vertices covering all edges

**Input**: Graph G, integer k

**Question**: Does G have vertex cover of size ≤ k?

### 4. Independent Set

**Problem**: Select k vertices with no edges between them

**Complement** of Vertex Cover

### 5. Clique

**Problem**: Find k vertices all connected to each other

**Equivalent**: Independent Set in complement graph

### 6. Hamiltonian Cycle

**Problem**: Visit each vertex exactly once and return

**Input**: Graph G

**Question**: Does G have Hamiltonian cycle?

**Note**: Eulerian cycle is in P!

### 7. Traveling Salesman Problem (TSP)

**Decision version**: Is there tour with cost ≤ k?

**Optimization version**: Find minimum cost tour

**Relationship**: Hamiltonian Cycle ≤ₚ TSP

### 8. Subset Sum

**Problem**: Select numbers summing to target

**Input**: Set {a₁, ..., aₙ}, target T

**Question**: Does subset sum to T?

**Pseudo-polynomial**: O(nT) dynamic programming

### 9. Knapsack (0/1)

**Problem**: Select items maximizing value within weight limit

**Similar** to Subset Sum

### 10. Graph Coloring

**Problem**: Color vertices with k colors (no adjacent same color)

**Input**: Graph G, integer k

**Note**: 2-coloring is in P (bipartite check)

### 11. Partition

**Problem**: Split numbers into two equal-sum sets

**Special case** of Subset Sum (T = total/2)

### 12. Bin Packing

**Problem**: Pack items into minimum number of bins

**Application**: Resource allocation, scheduling

---

## Implications

### If P = NP

**Consequences**:
- All NP-complete problems solvable efficiently
- Verification = Solution
- Cryptography breaks (factoring easy)
- Optimization revolutionized
- Machine learning, AI breakthroughs

**Likelihood**: Most complexity theorists believe P ≠ NP

### If P ≠ NP

**Consequences**:
- Some problems fundamentally hard
- Need approximation algorithms
- Heuristics for practical solutions
- Cryptography secure

**Practical Impact**: Already assume P ≠ NP in system design

### Approaches When Facing NP-Complete Problems

#### 1. Approximation Algorithms
Get solution within factor of optimal
```
Example: 2-approximation for Vertex Cover
Solution ≤ 2 × OPT
```

#### 2. Parameterized Complexity
Efficient for small parameter k
```
Example: O(2ᵏ n) for Vertex Cover with k vertices
```

#### 3. Heuristics
No guarantees, but work well in practice
```
- Greedy algorithms
- Local search
- Genetic algorithms
```

#### 4. Special Cases
Identify tractable subcases
```
- 2-SAT ∈ P (but 3-SAT NP-complete)
- Planar graphs often easier
- Bounded treewidth
```

#### 5. Exponential Algorithms
Optimize constant in exponential
```
Naive: O(2ⁿ)
Optimized: O(1.5ⁿ)
```

---

## Problem Transformations

### Reduction Examples

#### 3-SAT → Independent Set

**Construction**: 
- For each clause, create triangle of literals
- Connect complementary literals across clauses

**Size**: k clauses → independent set of size k exists

#### Vertex Cover → Hamiltonian Cycle

**Construction**:
- Widget for each edge
- Force path through edge widgets
- Correspond to vertex cover

**Complex** but polynomial-time

#### Subset Sum → Partition

**Construction**:
- Given Subset Sum (S, T)
- Add element (sum(S) - 2T)
- Partition exists ⟺ original subset sum exists

---

## Complexity Class Hierarchy

```
P
  ⊆
NP ∩ co-NP
  ⊆
NP
  ⊆
PSPACE
  ⊆
EXP
  ⊆
NEXP
  ⊆
RE (Recursively Enumerable)
```

**Known Separations**:
- P ≠ EXP (time hierarchy theorem)
- NP ≠ NEXP (time hierarchy theorem)

**Unknown**:
- P =? NP
- NP =? co-NP
- NP =? PSPACE

---

## Key Takeaways

1. **P**: Efficiently solvable problems

2. **NP**: Efficiently verifiable problems

3. **NP-Complete**: Hardest problems in NP
   - If one is easy, all are easy
   - If one is hard, all are hard

4. **Reductions**: Core technique
   - Prove hardness
   - Transfer algorithms

5. **Practical**: Assume P ≠ NP
   - Use approximations
   - Heuristics
   - Special cases

6. **Million Dollar Question**: P =? NP
   - One of the most important open problems
   - Clay Millennium Prize

---

## Further Reading

- **Textbooks**:
  - "Introduction to the Theory of Computation" by Sipser
  - "Computers and Intractability" by Garey & Johnson
  
- **Advanced Topics**:
  - Approximation algorithms
  - Parameterized complexity
  - Circuit complexity
  - Quantum complexity (BQP)

---

**Complexity Class Relationships Summary**:

| Class | Time | Examples |
|-------|------|----------|
| P | Polynomial | Sorting, shortest path, max flow |
| NP | Poly verify | SAT, TSP, Hamiltonian Cycle |
| NP-Complete | Hardest in NP | 3-SAT, Vertex Cover, Clique |
| NP-Hard | ≥ NP-Complete | Halting, optimization TSP |
| PSPACE | Poly space | QBF, game tree evaluation |
| EXP | Exponential | Generalized chess, Go |
