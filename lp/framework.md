# Linear Programming Framework

## Table of Contents
1. [Introduction](#introduction)
2. [Standard Form](#standard-form)
3. [Geometric Interpretation](#geometric-interpretation)
4. [Simplex Algorithm](#simplex-algorithm)
5. [Duality Theory](#duality-theory)
6. [Applications](#applications)

---

## Introduction

**Linear Programming (LP)** is a mathematical optimization technique for finding the best outcome in a mathematical model whose requirements are represented by linear relationships.

### General Form
```
Maximize (or Minimize):  c₁x₁ + c₂x₂ + ... + cₙxₙ

Subject to:
  a₁₁x₁ + a₁₂x₂ + ... + a₁ₙxₙ  ≤  b₁
  a₂₁x₁ + a₂₂x₂ + ... + a₂ₙxₙ  ≤  b₂
  ...
  aₘ₁x₁ + aₘ₂x₂ + ... + aₘₙxₙ  ≤  bₘ
  
  x₁, x₂, ..., xₙ ≥ 0
```

### Components
- **Decision Variables**: x₁, x₂, ..., xₙ (what we control)
- **Objective Function**: What we want to optimize
- **Constraints**: Limitations on the variables
- **Non-negativity**: Variables cannot be negative

---

## Standard Form

Every LP can be converted to **standard form**:

```
Maximize:  c^T x

Subject to:
  Ax = b
  x ≥ 0
```

Where:
- **c** ∈ ℝⁿ: coefficient vector for objective function
- **A** ∈ ℝᵐˣⁿ: constraint matrix
- **b** ∈ ℝᵐ: right-hand side vector
- **x** ∈ ℝⁿ: decision variable vector

### Converting to Standard Form

#### 1. Minimization → Maximization
```
Minimize c^T x  ≡  Maximize (-c)^T x
```

#### 2. Inequality → Equality (add slack variables)
```
∑ aᵢⱼxⱼ ≤ bᵢ  →  ∑ aᵢⱼxⱼ + sᵢ = bᵢ,  sᵢ ≥ 0

∑ aᵢⱼxⱼ ≥ bᵢ  →  ∑ aᵢⱼxⱼ - sᵢ = bᵢ,  sᵢ ≥ 0
```

#### 3. Unrestricted Variable
```
If xⱼ is unrestricted:
  xⱼ = xⱼ⁺ - xⱼ⁻  where xⱼ⁺, xⱼ⁻ ≥ 0
```

### Example Conversion

**Original**:
```
Minimize:  2x₁ - 3x₂

Subject to:
  x₁ + x₂ ≥ 4
  2x₁ - x₂ ≤ 6
  x₁ ≥ 0, x₂ unrestricted
```

**Standard Form**:
```
Maximize:  -2x₁ + 3x₂⁺ - 3x₂⁻

Subject to:
  x₁ + x₂⁺ - x₂⁻ - s₁ = 4
  2x₁ - x₂⁺ + x₂⁻ + s₂ = 6
  x₁, x₂⁺, x₂⁻, s₁, s₂ ≥ 0
```

---

## Geometric Interpretation

### Feasible Region
The set of all points satisfying all constraints forms a **convex polyhedron**.

```
     x₂
      |
    6 |     /
      |    /  Feasible
    4 |   /   Region
      |  /
    2 | /________
      |/    2  4  6  x₁
```

### Key Properties

1. **Convexity**: If x and y are feasible, then any point λx + (1-λ)y is feasible for 0 ≤ λ ≤ 1

2. **Corner Points**: Optimal solution occurs at a vertex (corner) of the feasible region

3. **Fundamental Theorem**: 
   - If optimal solution exists, it occurs at a vertex
   - If multiple optima exist, at least one is at a vertex

### Basic Feasible Solutions (BFS)

A **basic feasible solution** is a corner point of the feasible region.

- Set of n-m variables to 0 (non-basic)
- Solve for remaining m variables (basic)
- If all variables ≥ 0, it's a BFS

**Example**: System with 5 variables, 3 constraints
- Choose 3 basic variables, set 2 to zero
- Number of BFS ≤ C(5,3) = 10

---

## Simplex Algorithm

### Overview
The **Simplex Algorithm** (Dantzig, 1947) iteratively moves from one BFS to an adjacent BFS, improving the objective value each time.

**Time Complexity**: 
- Worst case: **Exponential** O(2ⁿ)
- Average case: **Polynomial** (works well in practice)

### Algorithm Steps

```
1. Convert LP to standard form
2. Find initial basic feasible solution
3. While not optimal:
   a. Check optimality conditions
   b. Select entering variable (pivot column)
   c. Select leaving variable (pivot row)
   d. Perform pivot operation
   e. Update basis
4. Return optimal solution
```

### Simplex Tableau

Represents the LP in tabular form:

```
     x₁   x₂   x₃   s₁   s₂   RHS
────────────────────────────────────
s₁ │ a₁₁  a₁₂  a₁₃   1    0  │ b₁
s₂ │ a₂₁  a₂₂  a₂₃   0    1  │ b₂
────────────────────────────────────
 z │ -c₁  -c₂  -c₃   0    0  │  0
```

### Pivot Operation

**Goal**: Make one entering variable basic, one leaving variable non-basic

```
1. Select pivot column: most negative coefficient in z-row
2. Select pivot row: minimum ratio test (RHS / pivot column)
3. Divide pivot row by pivot element
4. Eliminate pivot column in other rows
```

### Optimality Conditions

**Stop when**: All coefficients in z-row are non-negative

```
If z-row: [-2, 3, 1, 0, 0 | 10]
         Not optimal (−2 < 0)

If z-row: [1, 3, 2, 0, 0 | 15]
         Optimal!
```

### Degeneracy

**Degeneracy** occurs when a BFS has more than n-m zero variables.

Problems:
- Simplex may cycle (visit same BFS repeatedly)
- Solutions: Bland's rule, lexicographic ordering

---

## Duality Theory

### Primal-Dual Pairs

Every LP (primal) has an associated **dual** LP.

**Primal** (Maximization):
```
Maximize:  c^T x
Subject to: Ax ≤ b, x ≥ 0
```

**Dual** (Minimization):
```
Minimize:  b^T y
Subject to: A^T y ≥ c, y ≥ 0
```

### Duality Rules

| Primal | Dual |
|--------|------|
| Maximize | Minimize |
| m constraints | m variables |
| n variables | n constraints |
| ≤ constraint → y ≥ 0 | |
| ≥ constraint → y ≤ 0 | |
| = constraint → y unrestricted | |
| x ≥ 0 → constraint ≥ | |
| x ≤ 0 → constraint ≤ | |
| x unrestricted → constraint = | |

### Weak Duality Theorem

For any feasible primal solution x and dual solution y:
```
c^T x  ≤  b^T y
```

**Implication**: Primal optimum ≤ Dual optimum

### Strong Duality Theorem

If primal has optimal solution x*, dual has optimal solution y*, and:
```
c^T x* = b^T y*
```

**Implication**: Primal optimum = Dual optimum (no gap!)

### Complementary Slackness

At optimality, for each i and j:
```
xⱼ > 0  ⟹  (A^T y)ⱼ = cⱼ  (dual constraint tight)
yᵢ > 0  ⟹  (Ax)ᵢ = bᵢ  (primal constraint tight)
```

Either a variable is zero OR its corresponding constraint is tight.

### Example: Diet Problem

**Primal** (minimize cost):
```
Minimize:  ∑ cⱼxⱼ  (cost of foods)

Subject to:
  ∑ aᵢⱼxⱼ ≥ bᵢ  (nutrient requirements)
  xⱼ ≥ 0
```

**Dual** (maximize nutrition value):
```
Maximize:  ∑ bᵢyᵢ  (value of nutrients)

Subject to:
  ∑ aᵢⱼyᵢ ≤ cⱼ  (value ≤ cost)
  yᵢ ≥ 0
```

**Interpretation**: yᵢ = shadow price of nutrient i

---

## Applications

### 1. Resource Allocation
```
Maximize profit from products given limited resources
Variables: quantity of each product
Constraints: resource availability
```

### 2. Diet Problem
```
Minimize cost while meeting nutritional requirements
Variables: amount of each food
Constraints: minimum nutrients needed
```

### 3. Transportation Problem
```
Minimize shipping cost from suppliers to customers
Variables: units shipped on each route
Constraints: supply/demand balance
```

### 4. Network Flow
```
Maximize flow through network
Variables: flow on each edge
Constraints: capacity, conservation
```

### 5. Cutting Stock Problem
```
Minimize waste when cutting materials
Variables: cutting patterns used
Constraints: demand for each size
```

### 6. Portfolio Optimization
```
Maximize return with risk constraints
Variables: investment amounts
Constraints: budget, diversification
```

---

## Interior Point Methods

Modern alternative to Simplex.

### Karmarkar's Algorithm (1984)

**Time Complexity**: O(n³·⁵ L) polynomial time!

**Idea**: 
- Move through interior of feasible region
- Approach optimal vertex from inside
- No visiting vertices until the end

**Advantages**:
- Polynomial worst-case
- Better for very large problems

**Disadvantages**:
- More complex implementation
- Simplex still faster for many problems

---

## Complexity

### Decision Problem
"Is there a feasible solution?"

**Complexity**: In **P** (polynomial time solvable)

### Optimization Problem
"Find optimal solution"

**Complexity**: 
- Simplex: Exponential worst case, polynomial average
- Interior Point: Polynomial worst case

### Integer Linear Programming
Same as LP but variables must be integers.

**Complexity**: **NP-hard**

---

## Key Takeaways

1. **LP is powerful**: Many optimization problems can be modeled as LP

2. **Geometric intuition**: Optimal solution at vertices

3. **Simplex works**: Despite exponential worst case, very efficient in practice

4. **Duality is fundamental**: Provides bounds, sensitivity analysis

5. **Polynomial algorithms exist**: Interior point methods guarantee polynomial time

6. **Integer constraints = hard**: Adding integrality makes problem NP-hard

---

## Further Reading

- **Textbooks**:
  - "Introduction to Linear Optimization" by Bertsimas & Tsitsiklis
  - "Linear Programming" by Vanderbei
  
- **Advanced Topics**:
  - Column generation
  - Branch and bound (for integer LP)
  - Benders decomposition
  - Stochastic programming

---

**Time Complexity Summary**:
- Simplex: O(2ⁿ) worst, polynomial average
- Interior Point: O(n³·⁵ L) worst case
- Finding BFS: O(m³)
- Pivot operation: O(mn)
