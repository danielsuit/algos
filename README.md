# Algorithms & Data Structures Course

A comprehensive collection of algorithm implementations and explanations covering a complete algorithms course curriculum.

## 📚 Course Structure

### 1. Introduction & Foundations
**Location**: `intro/`

#### Algorithms Implemented
- **Binary Search** (`binarysearch.cpp`) - O(log n)
  - Iterative and recursive implementations
  - First/last occurrence variants
  
- **Merge Sort** (`mergesort.cpp`) - O(n log n)
  - Divide and conquer sorting
  - Stable sorting algorithm
  
- **Quick Sort** (`quicksort.cpp`) - O(n log n) average, O(n²) worst
  - Multiple partition schemes
  - Hoare and Lomuto partitions
  
- **Randomized Pivot** (`randomizedpivot.cpp`) - O(n log n) expected
  - Randomized quicksort
  - 3-way partitioning for duplicates
  - Quick select for k-th element
  
- **Median of Medians** (`medianofmedians.cpp`) - O(n) worst case
  - Deterministic linear-time selection
  - Finding k-th smallest element
  
- **Integer Multiplication** (`integermultiplication.cpp`) - O(n^1.585)
  - Karatsuba algorithm
  - Fast multiplication for large integers
  
- **Fast Fourier Transform** (`fft.cpp`) - O(n log n)
  - Cooley-Tukey FFT
  - Polynomial multiplication
  - Signal processing

#### Theory Documents
- **Asymptotic Analysis** (`asymptotics.md`)
  - Big O, Omega, Theta notation
  - Common complexity classes
  - Analysis techniques
  
- **Recursion** (`recursion.md`)
  - Types of recursion
  - Recursion trees
  - Tail recursion optimization
  
- **Recurrence Relations** (`recurrences.md`)
  - Solving methods
  - Substitution, recursion tree, master theorem
  
- **Master Theorem** (`master-theorem.md`)
  - Three cases explained
  - Quick reference table
  
- **Mathematical Induction** (`induction.md`)
  - Simple and strong induction
  - Loop invariants
  - Algorithm correctness proofs

---

### 2. Dynamic Programming
**Location**: `dp/`

#### Time Complexity: O(n²) to O(n³) typically

- **Fibonacci** (`fibonacci.cpp`)
  - Recursive, memoization, tabulation, optimized
  - Matrix exponentiation - O(log n)
  
- **0/1 Knapsack** (`knapsack.cpp`) - O(n × W)
  - Memoization and tabulation
  - Space optimized to O(W)
  - Unbounded knapsack variant
  
- **Longest Common Subsequence** (`lcs.cpp`) - O(m × n)
  - String comparison
  - Diff utilities
  - 3-string LCS variant
  
- **Longest Increasing Subsequence** (`lis.cpp`)
  - O(n²) DP approach
  - O(n log n) binary search optimization
  - Bitonic subsequence
  
- **Edit Distance** (`editdistance.cpp`) - O(m × n)
  - Levenshtein distance
  - Insert, delete, replace operations
  
- **Longest Palindromic Subsequence** (`lps.cpp`) - O(n²)
  - Palindrome detection
  - Longest palindromic substring
  
- **Matrix Chain Multiplication** (`matrixchains.cpp`) - O(n³)
  - Optimal parenthesization
  - Minimizing matrix operations
  
- **Subset Sum** (`subsetsum.cpp`) - O(n × sum)
  - Existence and counting
  - Space optimized to O(sum)

---

### 3. Graph Algorithms
**Location**: `graph/`

#### Traversal
- **Breadth-First Search** (`bfs.cpp`) - O(V + E)
  - Level-order traversal
  - Shortest path in unweighted graphs
  - Distance calculation
  
- **Depth-First Search** (`dfs.cpp`) - O(V + E)
  - Recursive and iterative
  - Cycle detection
  - Connected components

#### Shortest Paths
- **Dijkstra's Algorithm** (`dijkstra.cpp`) - O((V + E) log V)
  - Single-source shortest paths
  - Non-negative weights
  - Priority queue implementation

#### Minimum Spanning Tree
- **Kruskal's Algorithm** (`kruskal.cpp`) - O(E log E)
  - Union-Find data structure
  - Edge-based approach
  
- **Prim's Algorithm** (`prim.cpp`) - O((V + E) log V)
  - Vertex-based approach
  - Priority queue implementation

#### Other Graph Problems
- **Topological Sort** (`topoorder.cpp`) - O(V + E)
  - DFS-based approach
  - Kahn's algorithm (BFS-based)
  - Valid for DAGs only

---

### 4. Greedy Algorithms
**Location**: `greedy/`

#### Time Complexity: O(n log n) typically (due to sorting)

- **Fractional Knapsack** (`fractionalknapsack.cpp`) - O(n log n)
  - Value-to-weight ratio
  - Optimal greedy solution
  
- **Huffman Coding** (`huffman.cpp`) - O(n log n)
  - Optimal prefix-free encoding
  - Priority queue construction
  
- **Interval Scheduling** (`intervalscheduling.cpp`) - O(n log n)
  - Maximum non-overlapping intervals
  - Interval partitioning (minimum classrooms)

#### Theory Documents
- **Greedy Stays Ahead** (`greedystaysahead.md`)
  - Proof techniques
  - When greedy works
  - Matroid theory
  
- **Proofs of Correctness** (`proofsofcorrectness.md`)
  - Exchange arguments
  - Cut property
  - Specific algorithm proofs

---

### 5. Network Flow & Linear Programming
**Location**: `networks/` and `lp/`

#### Planned Implementations
- Max Flow (Ford-Fulkerson, Edmonds-Karp)
- Min Cut
- Bipartite Matching
- Min Cost Flow

---

## 🚀 How to Use

### Compiling Individual Files
```bash
# Using g++
g++ -std=c++17 -o program intro/binarysearch.cpp
./program

# Using the Makefile in each directory
cd intro
make
```

### Running Examples
Each `.cpp` file contains a `main()` function with example usage and test cases.

```bash
# Example: Run Dijkstra's algorithm
cd graph
g++ -std=c++17 -o dijkstra dijkstra.cpp
./dijkstra
```

---

## 📊 Complexity Quick Reference

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| **Sorting** |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| **DP** |
| Knapsack | - | O(nW) | O(nW) | O(W) |
| LCS | - | O(mn) | O(mn) | O(min(m,n)) |
| LIS (DP) | - | O(n²) | O(n²) | O(n) |
| LIS (Binary) | - | O(n log n) | O(n log n) | O(n) |
| **Graph** |
| BFS/DFS | O(V+E) | O(V+E) | O(V+E) | O(V) |
| Dijkstra | - | O((V+E) log V) | O((V+E) log V) | O(V) |
| Kruskal MST | - | O(E log E) | O(E log E) | O(V) |
| Prim MST | - | O((V+E) log V) | O((V+E) log V) | O(V) |
| **Greedy** |
| Interval Scheduling | - | O(n log n) | O(n log n) | O(n) |
| Huffman Coding | - | O(n log n) | O(n log n) | O(n) |

---

## 📖 Learning Path

### Week 1-2: Foundations
1. Start with `intro/asymptotics.md` - understand Big O
2. Study `intro/recursion.md` and `intro/induction.md`
3. Implement sorting algorithms (merge sort, quick sort)
4. Read `intro/master-theorem.md` for analyzing divide-and-conquer

### Week 3-4: Dynamic Programming
1. Understand memoization vs tabulation with `dp/fibonacci.cpp`
2. Master classic problems: knapsack, LCS, LIS
3. Practice identifying optimal substructure
4. Learn space optimization techniques

### Week 5-6: Graphs
1. Master traversals: BFS and DFS
2. Shortest paths: Dijkstra
3. Minimum spanning trees: Kruskal and Prim
4. Topological sorting for DAGs

### Week 7-8: Greedy Algorithms
1. Read `greedy/greedystaysahead.md`
2. Understand when greedy works
3. Study proofs in `greedy/proofsofcorrectness.md`
4. Practice: interval scheduling, Huffman coding

---

## 🎯 Key Concepts

### Algorithm Design Paradigms

1. **Divide and Conquer**
   - Break problem into subproblems
   - Solve recursively
   - Combine solutions
   - Examples: Merge sort, FFT, Karatsuba

2. **Dynamic Programming**
   - Optimal substructure
   - Overlapping subproblems
   - Memoization (top-down) or tabulation (bottom-up)
   - Examples: Knapsack, LCS, edit distance

3. **Greedy Algorithms**
   - Make locally optimal choice
   - Hope for global optimum
   - Requires proof of correctness
   - Examples: Dijkstra, MST, Huffman

4. **Graph Algorithms**
   - Model relationships
   - Traversal strategies
   - Optimization problems
   - Examples: BFS, DFS, shortest paths

---

## 🔧 Requirements

- C++ compiler with C++17 support (g++ 7.0+, clang 5.0+)
- Make (optional, for using Makefiles)
- Basic understanding of C++ STL

---

## 📝 Code Style

- Clear variable names
- Comprehensive comments
- Time and space complexity documented
- Test cases in main()
- Example usage provided

---

## 🤝 Contributing

This is a learning repository. Feel free to:
- Add more algorithm implementations
- Improve explanations
- Fix bugs
- Add more test cases
- Enhance documentation

---

## 📚 Resources

### Books
- *Introduction to Algorithms* (CLRS)
- *Algorithm Design* by Kleinberg & Tardos
- *The Algorithm Design Manual* by Skiena

### Online
- [LeetCode](https://leetcode.com) - Practice problems
- [Codeforces](https://codeforces.com) - Competitive programming
- [CP-Algorithms](https://cp-algorithms.com) - Algorithm references

---

## 📄 License

Educational use. Feel free to learn from and build upon this code.

---

## 🎓 Course Topics Summary

✅ **Completed**:
- Asymptotic analysis
- Sorting & searching
- Divide and conquer
- Dynamic programming
- Graph algorithms
- Greedy algorithms
- Proofs of correctness

🚧 **In Progress**:
- Network flows
- Linear programming
- NP-completeness
- Approximation algorithms

---

**Happy Learning! 🚀**

For questions or improvements, feel free to open an issue or submit a pull request.
