# Linear Programming Applications

## Table of Contents
1. [Resource Allocation](#resource-allocation)
2. [Production Planning](#production-planning)
3. [Diet Problem](#diet-problem)
4. [Transportation Problem](#transportation-problem)
5. [Network Flow](#network-flow)
6. [Assignment Problem](#assignment-problem)
7. [Portfolio Optimization](#portfolio-optimization)
8. [Cutting Stock Problem](#cutting-stock-problem)
9. [Blending Problem](#blending-problem)
10. [Scheduling](#scheduling)

---

## Resource Allocation

### Problem Statement
A company manufactures products using limited resources. Maximize profit while respecting resource constraints.

### Formulation

**Decision Variables**:
- xⱼ = quantity of product j to produce

**Objective**:
```
Maximize: ∑ pⱼxⱼ  (total profit)
```

**Constraints**:
```
∑ aᵢⱼxⱼ ≤ bᵢ  (resource i availability)
xⱼ ≥ 0
```

### Example: Furniture Manufacturing

**Products**: Tables (x₁), Chairs (x₂)
- Profit: $60/table, $30/chair
- Resources: Wood, Labor, Machine time

**LP Formulation**:
```
Maximize: 60x₁ + 30x₂

Subject to:
  4x₁ + 2x₂ ≤ 100  (wood, board-feet)
  2x₁ + 3x₂ ≤ 90   (labor, hours)
  3x₁ + 1x₂ ≤ 60   (machine time, hours)
  x₁, x₂ ≥ 0
```

**Solution**: x₁ = 15 tables, x₂ = 20 chairs, Profit = $1500

**Sensitivity Analysis**:
- Shadow price of wood: $10/board-foot
- If wood increases by 1 unit → profit increases by $10

---

## Production Planning

### Multi-Period Planning

**Problem**: Plan production over multiple time periods with inventory.

**Decision Variables**:
- xₜ = production in period t
- Iₜ = inventory at end of period t

**Objective**:
```
Minimize: ∑ (production_cost_t · xₜ + holding_cost_t · Iₜ)
```

**Constraints**:
```
Iₜ = Iₜ₋₁ + xₜ - dₜ    (inventory balance)
xₜ ≤ capacity_t        (production capacity)
Iₜ ≥ safety_stock_t    (safety stock)
xₜ, Iₜ ≥ 0
```

### Example: 4-Month Production

**Data**:
- Demand: [100, 150, 200, 180]
- Production cost: $50/unit
- Holding cost: $2/unit/month
- Capacity: 200 units/month

**Formulation**:
```
Minimize: ∑₄ₜ₌₁ (50xₜ + 2Iₜ)

Subject to:
  I₁ = x₁ - 100
  I₂ = I₁ + x₂ - 150
  I₃ = I₂ + x₃ - 200
  I₄ = I₃ + x₄ - 180
  
  xₜ ≤ 200  for t = 1,2,3,4
  Iₜ, xₜ ≥ 0
```

---

## Diet Problem

### Classic Application
Minimize cost of diet while meeting nutritional requirements.

**Decision Variables**:
- xⱼ = servings of food j

**Objective**:
```
Minimize: ∑ cⱼxⱼ  (total cost)
```

**Constraints**:
```
∑ aᵢⱼxⱼ ≥ bᵢ  (nutrient i requirement)
xⱼ ≥ 0
```

### Example: Simplified Diet

**Foods**: Bread, Milk, Eggs
**Nutrients**: Calories, Protein, Calcium

```
Nutrient Content (per serving):
         Calories  Protein  Calcium  Cost
Bread       80       4        2      $0.50
Milk       120       8       30      $1.00
Eggs        90      12       10      $0.75

Requirements: ≥ 2000 cal, ≥ 60g protein, ≥ 300mg calcium
```

**LP Formulation**:
```
Minimize: 0.50x₁ + 1.00x₂ + 0.75x₃

Subject to:
  80x₁ + 120x₂ + 90x₃ ≥ 2000  (calories)
  4x₁ + 8x₂ + 12x₃ ≥ 60        (protein)
  2x₁ + 30x₂ + 10x₃ ≥ 300      (calcium)
  x₁, x₂, x₃ ≥ 0
```

### Dual Interpretation

**Dual variables** yᵢ = shadow price (value) of nutrient i

**Dual LP**:
```
Maximize: 2000y₁ + 60y₂ + 300y₃

Subject to:
  80y₁ + 4y₂ + 2y₃ ≤ 0.50   (bread)
  120y₁ + 8y₂ + 30y₃ ≤ 1.00 (milk)
  90y₁ + 12y₂ + 10y₃ ≤ 0.75 (eggs)
  y₁, y₂, y₃ ≥ 0
```

**Interpretation**: yᵢ = how much we'd pay for additional unit of nutrient i

---

## Transportation Problem

### Problem Statement
Ship goods from suppliers to customers at minimum cost.

**Indices**:
- i = supplier (i = 1, ..., m)
- j = customer (j = 1, ..., n)

**Parameters**:
- sᵢ = supply at supplier i
- dⱼ = demand at customer j
- cᵢⱼ = cost to ship from i to j

**Decision Variables**:
- xᵢⱼ = units shipped from i to j

**Formulation**:
```
Minimize: ∑ᵢ ∑ⱼ cᵢⱼxᵢⱼ

Subject to:
  ∑ⱼ xᵢⱼ = sᵢ  for all i  (supply constraint)
  ∑ᵢ xᵢⱼ = dⱼ  for all j  (demand constraint)
  xᵢⱼ ≥ 0
```

### Example: 2 Factories, 3 Warehouses

**Supply**: F1 = 100, F2 = 150
**Demand**: W1 = 80, W2 = 70, W3 = 100

**Shipping Costs**:
```
       W1   W2   W3
F1     5    8    6
F2     7    4    5
```

**LP**:
```
Minimize: 5x₁₁ + 8x₁₂ + 6x₁₃ + 7x₂₁ + 4x₂₂ + 5x₂₃

Subject to:
  x₁₁ + x₁₂ + x₁₃ = 100       (F1 supply)
  x₂₁ + x₂₂ + x₂₃ = 150       (F2 supply)
  x₁₁ + x₂₁ = 80              (W1 demand)
  x₁₂ + x₂₂ = 70              (W2 demand)
  x₁₃ + x₂₃ = 100             (W3 demand)
  xᵢⱼ ≥ 0
```

**Solution Methods**:
- Simplex method
- Transportation simplex (specialized, faster)
- Northwest corner rule (initial solution)
- Vogel's approximation method

---

## Network Flow

### Maximum Flow as LP

**Given**: Directed graph with capacities

**Variables**: xᵢⱼ = flow on edge (i,j)

**Formulation**:
```
Maximize: ∑ xsⱼ - ∑ xⱼs  (net flow from source)

Subject to:
  ∑ xᵢⱼ = ∑ xⱼᵢ  for all j ≠ s,t  (flow conservation)
  xᵢⱼ ≤ cᵢⱼ                       (capacity)
  xᵢⱼ ≥ 0
```

### Minimum Cost Flow

**Additional parameter**: cost per unit flow on each edge

**Objective**:
```
Minimize: ∑ cᵢⱼxᵢⱼ  (total cost)
```

**Applications**:
- Supply chain optimization
- Traffic routing
- Telecommunications

---

## Assignment Problem

### Problem Statement
Assign n workers to n jobs, minimizing total cost.

**Decision Variables**:
- xᵢⱼ = 1 if worker i assigned to job j, else 0

**Formulation**:
```
Minimize: ∑ᵢ ∑ⱼ cᵢⱼxᵢⱼ

Subject to:
  ∑ⱼ xᵢⱼ = 1  for all i  (each worker assigned once)
  ∑ᵢ xᵢⱼ = 1  for all j  (each job assigned once)
  xᵢⱼ ∈ {0, 1}
```

**Note**: Although variables are binary, LP relaxation (xᵢⱼ ≥ 0) gives integer solution!

### Example: 3 Workers, 3 Jobs

**Cost matrix**:
```
      J1   J2   J3
W1    10   15   9
W2    15   12   8
W3    11   13   10
```

**LP Formulation**:
```
Minimize: 10x₁₁ + 15x₁₂ + 9x₁₃ + 15x₂₁ + 12x₂₂ + 8x₂₃ + 11x₃₁ + 13x₃₂ + 10x₃₃

Subject to:
  x₁₁ + x₁₂ + x₁₃ = 1  (W1)
  x₂₁ + x₂₂ + x₂₃ = 1  (W2)
  x₃₁ + x₃₂ + x₃₃ = 1  (W3)
  x₁₁ + x₂₁ + x₃₁ = 1  (J1)
  x₁₂ + x₂₂ + x₃₂ = 1  (J2)
  x₁₃ + x₂₃ + x₃₃ = 1  (J3)
  xᵢⱼ ≥ 0
```

**Solution**: W1→J3, W2→J2, W3→J1, Cost = 32

**Algorithms**:
- Hungarian algorithm: O(n³)
- Auction algorithm
- Simplex method

---

## Portfolio Optimization

### Markowitz Mean-Variance Model

**Problem**: Invest in assets to maximize return while limiting risk.

**Decision Variables**:
- xᵢ = fraction of wealth in asset i

**Parameters**:
- rᵢ = expected return of asset i
- σᵢⱼ = covariance between assets i and j

**Formulation 1** (Maximize return for given risk):
```
Maximize: ∑ rᵢxᵢ  (expected return)

Subject to:
  ∑ᵢ ∑ⱼ σᵢⱼxᵢxⱼ ≤ σ²  (risk constraint)
  ∑ xᵢ = 1              (budget)
  xᵢ ≥ 0
```

**Formulation 2** (Minimize risk for given return):
```
Minimize: ∑ᵢ ∑ⱼ σᵢⱼxᵢxⱼ  (portfolio variance)

Subject to:
  ∑ rᵢxᵢ ≥ R  (target return)
  ∑ xᵢ = 1
  xᵢ ≥ 0
```

**Note**: This is **Quadratic Programming** (QP), not pure LP

### Linear Approximation

Use Mean Absolute Deviation (MAD) instead of variance:
```
Minimize: ∑ₜ |rₜ - ∑ rᵢₜxᵢ|  (deviation from expected)

Subject to:
  ∑ rᵢxᵢ ≥ R
  ∑ xᵢ = 1
  xᵢ ≥ 0
```

Can linearize absolute values with auxiliary variables.

---

## Cutting Stock Problem

### Problem Statement
Cut raw materials into smaller pieces to meet demand, minimizing waste.

**Given**:
- Raw material length L
- m types of items with lengths lᵢ and demands dᵢ

**Decision Variables**:
- xⱼ = number of times cutting pattern j is used

**Cutting Patterns**: Ways to cut raw material
- Pattern j: cuts aᵢⱼ items of type i

**Formulation**:
```
Minimize: ∑ⱼ xⱼ  (number of raw materials used)

Subject to:
  ∑ⱼ aᵢⱼxⱼ ≥ dᵢ  for all i  (demand)
  xⱼ ≥ 0
```

### Example: Paper Roll Cutting

**Raw roll**: 100 inches wide
**Orders**: 40" (50 rolls), 30" (60 rolls), 20" (80 rolls)

**Possible patterns**:
```
Pattern 1: 2×40" + 1×20" = 100"
Pattern 2: 1×40" + 2×30" = 100"
Pattern 3: 1×40" + 3×20" = 100"
Pattern 4: 3×30" + 1×10" waste
Pattern 5: 5×20" = 100"
```

**Challenge**: Exponentially many patterns!

**Solution**: Column Generation
- Start with subset of patterns
- Solve LP
- Generate new profitable patterns
- Repeat until optimal

---

## Blending Problem

### Problem Statement
Mix ingredients to meet specifications at minimum cost.

**Application**: Oil refining, animal feed, alloys

**Decision Variables**:
- xᵢ = quantity of ingredient i in blend

**Formulation**:
```
Minimize: ∑ cᵢxᵢ  (cost)

Subject to:
  ∑ pᵢⱼxᵢ ≥ Lⱼ · ∑ xᵢ  (property j lower bound)
  ∑ pᵢⱼxᵢ ≤ Uⱼ · ∑ xᵢ  (property j upper bound)
  xᵢ ≥ 0
```

### Example: Gasoline Blending

**Inputs**: Crude oils with different properties
**Output**: Gasoline meeting octane, vapor pressure specs

**Variables**: xᵢ = barrels of crude i

**Constraints**:
```
∑ octane_i · xᵢ ≥ 87 · ∑ xᵢ  (min octane)
∑ vapor_i · xᵢ ≤ 15 · ∑ xᵢ  (max vapor pressure)
```

**Note**: Can linearize by dividing through by ∑ xᵢ

---

## Scheduling

### Job Shop Scheduling (Linear Approximation)

**Problem**: Schedule jobs on machines to minimize makespan.

**Variables**:
- tⱼ = start time of job j
- Cmax = makespan (completion time of last job)

**Formulation**:
```
Minimize: Cmax

Subject to:
  tⱼ + pⱼ ≤ Cmax              for all j  (makespan)
  tⱼ + pⱼ ≤ tₖ  OR  tₖ + pₖ ≤ tⱼ  if j,k on same machine
  tⱼ ≥ 0
```

**Problem**: Disjunctive constraints (OR)

**Solution**: Use binary variables (becomes mixed-integer LP)

### Shift Scheduling

**Problem**: Assign workers to shifts meeting demand.

**Variables**:
- xᵢ = workers starting shift i

**Formulation**:
```
Minimize: ∑ cᵢxᵢ  (total cost)

Subject to:
  ∑ᵢ∈Sₜ xᵢ ≥ dₜ  for all t  (demand at time t)
  xᵢ ≥ 0
```

Where Sₜ = set of shifts covering time t

### Example: Nurse Scheduling

**Shifts**: Morning, Evening, Night (each 8 hours)
**Demand**: M=5, E=6, N=4 nurses

**Variables**: xM, xE, xN = nurses per shift

**Constraints**:
- Nurses work 8-hour shift
- Cover demand each period
- Minimize total nurses or cost

---

## Advanced Applications

### 1. Network Design
- Facility location
- Capacitated networks
- Hub location

### 2. Revenue Management
- Airline seat allocation
- Hotel pricing
- Dynamic pricing

### 3. Supply Chain
- Multi-echelon inventory
- Distribution network design
- Vendor selection

### 4. Telecommunications
- Network routing
- Bandwidth allocation
- Tower placement

### 5. Energy Systems
- Power generation scheduling
- Grid optimization
- Renewable integration

---

## Modeling Tips

### 1. Linearizing Products

**Non-linear**: x · y
**If y binary**: Replace with z = x · y
```
z ≤ M · y
z ≤ x
z ≥ x - M(1-y)
```

### 2. Absolute Values

**Non-linear**: |x|
**Linear**: Minimize t such that
```
t ≥ x
t ≥ -x
```

### 3. Max/Min Functions

**Non-linear**: max(x₁, x₂, ..., xₙ)
**Linear**: Minimize z such that
```
z ≥ xᵢ  for all i
```

### 4. Piecewise Linear

Use multiple variables and constraints for each segment

### 5. Either-Or Constraints

Use big-M method with binary variables

---

## Software Tools

### Commercial Solvers
- **CPLEX** (IBM)
- **Gurobi**
- **XPRESS**

### Open-Source Solvers
- **GLPK** (GNU Linear Programming Kit)
- **COIN-OR**
- **lp_solve**

### Modeling Languages
- **AMPL**
- **GAMS**
- **Pyomo** (Python)
- **JuMP** (Julia)

---

## Key Takeaways

1. **Versatility**: LP models many real-world problems

2. **Standard Forms**: Convert problem to LP format

3. **Dual Insights**: Shadow prices provide sensitivity

4. **Extensions**: Integer variables for discrete decisions

5. **Algorithms**: Simplex, interior point are practical

6. **Tools**: Modern solvers handle large-scale problems

7. **Modeling**: Art of formulation is crucial

---

**Time Complexity for Applications**:
- Simplex: O(2ⁿ) worst, polynomial average
- Interior Point: O(n³·⁵) worst case
- Network Flow: O(V²E) specialized
- Assignment: O(n³) Hungarian algorithm
- Transportation: O(m²n) specialized simplex
