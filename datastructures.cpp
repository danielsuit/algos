#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <forward_list>
#include <bitset>
#include <string>
#include <algorithm>

using namespace std;

// ============================================
// 1. ARRAY (Fixed-size, contiguous memory)
// ============================================
// HOW IT WORKS:
// - Arrays store elements in contiguous memory locations
// - Each element occupies a fixed amount of space based on data type
// - Memory address of element i = base_address + (i * element_size)
// - This allows O(1) random access using pointer arithmetic
// - Size is fixed at compile time (C-style) or initialization (std::array)
//
// MEMORY LAYOUT: [elem0][elem1][elem2][elem3][elem4] (consecutive addresses)
//
// TIME COMPLEXITY:
// - Access: O(1) - direct memory address calculation
// - Search: O(n) - must check each element linearly
// - Insert/Delete: O(n) - requires shifting elements (not supported in fixed arrays)
//
// SPACE COMPLEXITY: O(n) where n is array size
//
// USE CASES:
// - When size is known and fixed
// - Need fast random access by index
// - Memory locality important (cache-friendly)
// - Simple data storage without dynamic resizing
void arrayExample() {
    cout << "\n=== ARRAY EXAMPLE ===" << endl;
    
    // C-style array
    int arr[5] = {1, 2, 3, 4, 5};
    
    // std::array (modern C++)
    array<int, 5> stdArr = {10, 20, 30, 40, 50};
    
    cout << "C-style array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    cout << "std::array: ";
    for (int val : stdArr) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Array size: " << stdArr.size() << endl;
    cout << "Array at index 2: " << stdArr.at(2) << endl;
}

// ============================================
// 2. VECTOR (Dynamic array)
// ============================================
// HOW IT WORKS:
// - Vector is a dynamic array that automatically resizes
// - Internally maintains: pointer to array, size (used elements), capacity (allocated space)
// - When capacity is exceeded, allocates new larger array (typically 2x), copies elements, deletes old
// - Growth strategy amortizes cost: occasional O(n) reallocation but O(1) average push_back
// - Elements stored contiguously like array, so cache-friendly
//
// RESIZING MECHANISM:
// Initial: capacity=4  [a][b][c][d]
// Full, add 'e': Allocate capacity=8 [a][b][c][d][e][ ][ ][ ]
// Copy existing + add new, delete old array
//
// TIME COMPLEXITY:
// - Access (operator[]): O(1) - direct indexing
// - push_back: O(1) amortized, O(n) worst case (reallocation)
// - pop_back: O(1) - just decrements size
// - insert/erase middle: O(n) - must shift elements
// - Search: O(n) unsorted, O(log n) if sorted with binary search
//
// SPACE COMPLEXITY: O(n), but capacity may be > size (1.5x-2x size typical)
//
// USE CASES:
// - Most common container - default choice
// - Dynamic size needed with fast random access
// - Frequent additions at end
// - When memory locality/cache performance matters
void vectorExample() {
    cout << "\n=== VECTOR EXAMPLE ===" << endl;
    
    vector<int> vec;
    
    // Adding elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    
    cout << "Vector elements: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    // Accessing elements
    cout << "Element at index 2: " << vec[2] << endl;
    cout << "First element: " << vec.front() << endl;
    cout << "Last element: " << vec.back() << endl;
    
    // Size and capacity
    cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
    
    // Insert at position
    vec.insert(vec.begin() + 2, 25);
    
    // Remove last element
    vec.pop_back();
    
    cout << "After insert and pop: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    // 2D vector
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "2D vector[1][1]: " << matrix[1][1] << endl;
}

// ============================================
// 3. LIST (Doubly-linked list)
// ============================================
// HOW IT WORKS:
// - Each node contains: data, pointer to next node, pointer to previous node
// - Nodes scattered in memory (not contiguous)
// - List maintains pointers to head and tail
// - Bidirectional traversal possible (forward and backward)
//
// NODE STRUCTURE:
// [prev*|data|next*] <-> [prev*|data|next*] <-> [prev*|data|next*]
//     ^                                                          ^
//    head                                                      tail
//
// INSERTION PROCESS (middle):
// 1. Create new node
// 2. Set new->next = current->next
// 3. Set new->prev = current
// 4. Update current->next->prev = new
// 5. Update current->next = new
// Only pointer updates - no element shifting!
//
// TIME COMPLEXITY:
// - Access: O(n) - must traverse from head/tail
// - Insert/Delete at known position: O(1) - just update pointers
// - Insert/Delete with search: O(n) - need to find position first
// - push_front/push_back: O(1) - have head/tail pointers
//
// SPACE COMPLEXITY: O(n) + overhead for prev/next pointers per node
//
// USE CASES:
// - Frequent insertions/deletions in middle
// - Don't need random access
// - Bidirectional traversal needed
// - Implementing LRU cache, undo/redo functionality
void listExample() {
    cout << "\n=== LIST EXAMPLE ===" << endl;
    
    list<int> lst;
    
    // Adding elements
    lst.push_back(10);
    lst.push_back(20);
    lst.push_front(5);
    lst.push_front(1);
    
    cout << "List elements: ";
    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl;
    
    // Insert in middle
    auto it = lst.begin();
    advance(it, 2);
    lst.insert(it, 15);
    
    // Remove elements
    lst.remove(20);
    
    cout << "After insert and remove: ";
    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl;
    
    // Front and back
    cout << "Front: " << lst.front() << ", Back: " << lst.back() << endl;
}

// ============================================
// 4. FORWARD_LIST (Singly-linked list)
// ============================================
// HOW IT WORKS:
// - Each node contains: data and pointer to next node only
// - More memory efficient than doubly-linked list (one pointer vs two)
// - Can only traverse forward, not backward
// - No tail pointer maintained (would require O(n) to reach end)
//
// NODE STRUCTURE:
// [data|next*] -> [data|next*] -> [data|next*] -> nullptr
//     ^
//    head
//
// INSERTION AFTER NODE:
// Before: [A|*]--->[C|*]
// After:  [A|*]--->[B|*]--->[C|*]
// Steps: 1) new->next = A->next  2) A->next = new
//
// TIME COMPLEXITY:
// - Access: O(n) - traverse from head
// - Insert after known position: O(1) - update pointers
// - push_front: O(1) - update head pointer
// - No push_back (would be O(n) without tail pointer)
//
// SPACE COMPLEXITY: O(n) + one pointer per node (less than list)
//
// USE CASES:
// - Memory constrained environments
// - Only forward traversal needed
// - Implementing stack-like structures
// - Hash table chaining (collision resolution)
void forwardListExample() {
    cout << "\n=== FORWARD_LIST EXAMPLE ===" << endl;
    
    forward_list<int> flist = {10, 20, 30, 40};
    
    // Push front
    flist.push_front(5);
    
    cout << "Forward list elements: ";
    for (int val : flist) {
        cout << val << " ";
    }
    cout << endl;
    
    // Insert after
    auto it = flist.begin();
    flist.insert_after(it, 7);
    
    cout << "After insert_after: ";
    for (int val : flist) {
        cout << val << " ";
    }
    cout << endl;
}

// ============================================
// 5. DEQUE (Double-ended queue)
// ============================================
// HOW IT WORKS:
// - Hybrid structure: array of arrays (chunks/blocks)
// - Maintains array of pointers to fixed-size memory blocks
// - Each block contains multiple elements contiguously
// - Can grow/shrink at both ends efficiently
// - Central "map" tracks which blocks are in use
//
// STRUCTURE:
// Map: [*][*][*][*][*]  <- pointers to blocks
//       |  |  |  |  |
//       v  v  v  v  v
//      [Block0][Block1][Block2][Block3][Block4]
//      elements elements elements elements elements
//
// GROWTH:
// - Adding at front: allocate new block, add to map beginning
// - Adding at back: allocate new block, add to map end
// - No need to copy all existing elements (unlike vector)
//
// TIME COMPLEXITY:
// - Access (operator[]): O(1) - calculate block + offset
// - push_front/push_back: O(1) amortized - add to existing/new block
// - pop_front/pop_back: O(1) - remove from end blocks
// - Insert/Delete middle: O(n) - must shift elements within blocks
//
// SPACE COMPLEXITY: O(n) + overhead for block pointers
//
// USE CASES:
// - Need efficient insertion/removal at both ends
// - Still want random access (unlike list)
// - Implementing sliding window algorithms
// - Queue with priority access to both ends
void dequeExample() {
    cout << "\n=== DEQUE EXAMPLE ===" << endl;
    
    deque<int> dq;
    
    // Add elements at both ends
    dq.push_back(20);
    dq.push_back(30);
    dq.push_front(10);
    dq.push_front(5);
    
    cout << "Deque elements: ";
    for (int val : dq) {
        cout << val << " ";
    }
    cout << endl;
    
    // Access elements
    cout << "Element at index 2: " << dq[2] << endl;
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << endl;
    
    // Remove from both ends
    dq.pop_front();
    dq.pop_back();
    
    cout << "After popping: ";
    for (int val : dq) {
        cout << val << " ";
    }
    cout << endl;
}

// ============================================
// 6. STACK (LIFO - Last In First Out)
// ============================================
// HOW IT WORKS:
// - Adapter container - wraps underlying container (default: deque)
// - Restricts access to LIFO operations only: push, pop, top
// - Think of it as a stack of plates - add/remove from top only
// - Internally just calls push_back, pop_back, back on underlying container
//
// VISUALIZATION:
//    top()  ->  [D]  <- push/pop here
//               [C]
//               [B]
//               [A]  <- bottom (first inserted)
//
// OPERATIONS:
// push(X): adds X to top
// pop(): removes top element
// top(): returns top element without removing
//
// CALL STACK ANALOGY:
// Function calls use stack - each call pushes frame, return pops
// push(main) -> push(foo) -> push(bar) -> pop(bar) -> pop(foo) -> pop(main)
//
// TIME COMPLEXITY:
// - push: O(1) - add to end of underlying container
// - pop: O(1) - remove from end
// - top: O(1) - access last element
//
// SPACE COMPLEXITY: O(n) where n is number of elements
//
// USE CASES:
// - Function call stack, recursion simulation
// - Undo mechanisms, backtracking algorithms
// - Expression evaluation (postfix, infix)
// - DFS traversal, parentheses matching
// - Browser back button history
void stackExample() {
    cout << "\n=== STACK EXAMPLE ===" << endl;
    
    stack<int> stk;
    
    // Push elements
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    
    cout << "Stack size: " << stk.size() << endl;
    cout << "Top element: " << stk.top() << endl;
    
    // Pop elements
    cout << "Popping elements: ";
    while (!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;
}

// ============================================
// 7. QUEUE (FIFO - First In First Out)
// ============================================
// HOW IT WORKS:
// - Adapter container wrapping underlying container (default: deque)
// - Restricts to FIFO operations: push (enqueue), pop (dequeue), front, back
// - Like a line at a store - first person in is first person served
// - Uses push_back for enqueue, pop_front for dequeue on underlying container
//
// VISUALIZATION:
// back -> [D][C][B][A] <- front
//  ^                ^
// enqueue          dequeue
// (push)           (pop)
//
// OPERATIONS:
// push(X): adds X to back of queue
// pop(): removes front element
// front(): returns front element (next to be removed)
// back(): returns back element (most recently added)
//
// REAL-WORLD ANALOGY:
// Print queue - jobs printed in order received
// Customer service - first caller gets served first
//
// TIME COMPLEXITY:
// - push: O(1) - add to back
// - pop: O(1) - remove from front
// - front/back: O(1) - access ends
//
// SPACE COMPLEXITY: O(n)
//
// USE CASES:
// - BFS traversal in graphs/trees
// - Task scheduling, job processing
// - Buffering (keyboard buffer, printer queue)
// - Message queues in systems
// - Level-order tree traversal
void queueExample() {
    cout << "\n=== QUEUE EXAMPLE ===" << endl;
    
    queue<int> q;
    
    // Enqueue elements
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    
    cout << "Queue size: " << q.size() << endl;
    cout << "Front: " << q.front() << ", Back: " << q.back() << endl;
    
    // Dequeue elements
    cout << "Dequeuing elements: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

// ============================================
// 8. PRIORITY_QUEUE (Heap-based)
// ============================================
// HOW IT WORKS:
// - Implemented as binary heap (complete binary tree stored in array)
// - Max heap by default - largest element at top
// - Heap property: parent ≥ children (max heap) or parent ≤ children (min heap)
// - Uses vector internally, indices follow heap rules
//
// ARRAY REPRESENTATION OF HEAP:
// Array: [50, 30, 40, 10, 20, 15, 35]
// Indices: 0   1   2   3   4   5   6
//
// Tree form:        50
//                  /  \
//                30    40
//               / \    / \
//              10 20  15 35
//
// INDEX FORMULAS (0-indexed):
// - Parent of i: (i-1)/2
// - Left child of i: 2*i+1
// - Right child of i: 2*i+2
//
// INSERTION (push):
// 1. Add element at end of array
// 2. "Bubble up" - swap with parent if heap property violated
// 3. Continue until heap property restored
//
// DELETION (pop):
// 1. Remove top element (index 0)
// 2. Move last element to top
// 3. "Bubble down" - swap with larger child (max heap) if needed
// 4. Continue until heap property restored
//
// TIME COMPLEXITY:
// - top: O(1) - just access first element
// - push: O(log n) - bubble up through tree height
// - pop: O(log n) - bubble down through tree height
// - Construction from array: O(n) using heapify
//
// SPACE COMPLEXITY: O(n)
//
// USE CASES:
// - Dijkstra's shortest path algorithm
// - Huffman coding compression
// - Finding k largest/smallest elements
// - Task scheduling with priorities
// - Median maintenance in streaming data
// - A* pathfinding algorithm
void priorityQueueExample() {
    cout << "\n=== PRIORITY_QUEUE EXAMPLE ===" << endl;
    
    // Max heap (default)
    priority_queue<int> maxHeap;
    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(50);
    maxHeap.push(20);
    
    cout << "Max heap (popping): ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;
    
    // Min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(50);
    minHeap.push(20);
    
    cout << "Min heap (popping): ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;
    
    // Custom comparator
    auto cmp = [](pair<int,int> a, pair<int,int> b) { return a.second > b.second; };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
    pq.push({1, 100});
    pq.push({2, 50});
    pq.push({3, 150});
    
    cout << "Custom priority queue: ";
    while (!pq.empty()) {
        cout << "(" << pq.top().first << "," << pq.top().second << ") ";
        pq.pop();
    }
    cout << endl;
}

// ============================================
// 9. SET (Sorted, unique elements)
// ============================================
// HOW IT WORKS:
// - Implemented as self-balancing binary search tree (Red-Black tree in most STL)
// - Elements automatically sorted on insertion
// - No duplicates allowed - attempts to insert duplicate are ignored
// - Tree maintains balance to ensure O(log n) operations
//
// RED-BLACK TREE PROPERTIES:
// 1. Each node is red or black
// 2. Root is black
// 3. Red nodes cannot have red children
// 4. All paths from node to leaves have same number of black nodes
// 5. These properties ensure height ≤ 2*log(n+1)
//
// STRUCTURE EXAMPLE:
//         30(B)
//        /     \
//     20(R)    40(R)
//    /   \       \
//  10(B) 25(B)  50(B)
//
// INSERTION PROCESS:
// 1. Insert like normal BST
// 2. Color new node red
// 3. Fix violations: recolor and/or rotate
// 4. Ensure red-black properties maintained
//
// SEARCH PROCESS:
// Binary search through tree: O(log n)
// If value < current, go left; if >, go right; if ==, found
//
// TIME COMPLEXITY:
// - Insert: O(log n) - tree traversal + rebalancing
// - Find: O(log n) - binary search through tree
// - Erase: O(log n) - find + rebalancing
// - lower_bound/upper_bound: O(log n)
// - Iteration: O(n) but elements in sorted order
//
// SPACE COMPLEXITY: O(n) + tree node overhead (color, pointers)
//
// USE CASES:
// - Maintain sorted unique collection
// - Range queries (elements between x and y)
// - Finding next/previous element efficiently
// - Implementing interval scheduling
// - Database indexing
void setExample() {
    cout << "\n=== SET EXAMPLE ===" << endl;
    
    set<int> s;
    
    // Insert elements
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(10);
    s.insert(30);
    s.insert(20); // Duplicate, won't be inserted
    
    cout << "Set elements (sorted): ";
    for (int val : s) {
        cout << val << " ";
    }
    cout << endl;
    
    // Find element
    if (s.find(30) != s.end()) {
        cout << "30 found in set" << endl;
    }
    
    // Lower bound and upper bound
    cout << "Lower bound of 25: " << *s.lower_bound(25) << endl;
    cout << "Upper bound of 30: " << *s.upper_bound(30) << endl;
    
    // Erase element
    s.erase(40);
    
    cout << "After erasing 40: ";
    for (int val : s) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Set size: " << s.size() << endl;
}

// ============================================
// 10. MULTISET (Sorted, allows duplicates)
// ============================================
// HOW IT WORKS:
// - Same as set (Red-Black tree) but allows duplicate values
// - Multiple nodes can have same value
// - Still maintains sorted order
// - Duplicates stored as separate nodes in tree
//
// DUPLICATE HANDLING:
//       20(B)
//      /    \
//    10(R)  30(B)
//   /  \       \
// 10(B) 10(B) 40(R)
//   ^    ^
// duplicates stored as separate nodes
//
// OPERATIONS WITH DUPLICATES:
// - count(x): returns number of occurrences
// - find(x): returns iterator to one occurrence
// - equal_range(x): returns pair of iterators [first, last) for all x
// - erase(x): removes ALL occurrences
// - erase(iterator): removes single occurrence
//
// TIME COMPLEXITY:
// - Insert: O(log n) - same as set
// - Find: O(log n) - find any occurrence
// - count(x): O(log n + k) where k is count of x
// - erase value: O(log n + k) where k is count
// - erase iterator: O(1) amortized
//
// SPACE COMPLEXITY: O(n) where n includes duplicates
//
// USE CASES:
// - Maintaining sorted collection with duplicates
// - Frequency counting with order preservation
// - Event scheduling with duplicate times
// - Priority tasks with same priority levels
void multisetExample() {
    cout << "\n=== MULTISET EXAMPLE ===" << endl;
    
    multiset<int> ms;
    
    // Insert elements (including duplicates)
    ms.insert(50);
    ms.insert(20);
    ms.insert(20);
    ms.insert(40);
    ms.insert(20);
    
    cout << "Multiset elements: ";
    for (int val : ms) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Count of 20: " << ms.count(20) << endl;
    
    // Erase one occurrence
    ms.erase(ms.find(20));
    
    cout << "After erasing one 20: ";
    for (int val : ms) {
        cout << val << " ";
    }
    cout << endl;
}

// ============================================
// 11. UNORDERED_SET (Hash table, unique elements)
// ============================================
// HOW IT WORKS:
// - Implemented as hash table with chaining for collision resolution
// - Hash function converts element to integer index
// - Buckets array where each bucket is linked list of elements
// - No ordering guarantee - elements stored by hash value
// - Load factor (elements/buckets) monitored - rehashes when exceeded
//
// STRUCTURE:
// Buckets:  [0] -> 30 -> nullptr
//           [1] -> nullptr
//           [2] -> 50 -> 20 -> nullptr  (collision chain)
//           [3] -> 40 -> nullptr
//           [4] -> nullptr
//
// HASH FUNCTION:
// hash(key) = key % bucket_count
// e.g., hash(50) = 50 % 5 = 0, so 50 goes in bucket 0
//
// COLLISION RESOLUTION (chaining):
// When hash(x) == hash(y):
// Store both in same bucket as linked list
// Search requires traversing chain: O(k) where k = chain length
//
// INSERTION PROCESS:
// 1. Compute hash(key)
// 2. Go to bucket[hash(key)]
// 3. Check if key exists (avoid duplicates)
// 4. If not, add to bucket's linked list
// 5. If load factor > threshold, rehash (resize buckets, reinsert all)
//
// REHASHING:
// When too many elements per bucket:
// - Allocate larger bucket array (typically 2x)
// - Recompute hash for all elements with new size
// - Reinsert into new buckets
// - O(n) operation but amortized to O(1) per insert
//
// TIME COMPLEXITY:
// - Insert: O(1) average, O(n) worst case (many collisions or rehash)
// - Find: O(1) average, O(n) worst case (all in one bucket)
// - Erase: O(1) average, O(n) worst case
// Note: No logarithmic factor like tree-based set!
//
// SPACE COMPLEXITY: O(n + b) where b is bucket count (usually n ≤ b ≤ 2n)
//
// USE CASES:
// - Fast lookup without needing sorted order
// - Checking existence (visited nodes, seen elements)
// - Removing duplicates from array
// - Two-sum problem, finding pairs
// - When O(1) lookup is critical and order doesn't matter
void unorderedSetExample() {
    cout << "\n=== UNORDERED_SET EXAMPLE ===" << endl;
    
    unordered_set<int> us;
    
    // Insert elements
    us.insert(50);
    us.insert(20);
    us.insert(40);
    us.insert(10);
    us.insert(30);
    us.insert(20); // Duplicate, won't be inserted
    
    cout << "Unordered set elements (no specific order): ";
    for (int val : us) {
        cout << val << " ";
    }
    cout << endl;
    
    // Find element (O(1) average)
    if (us.find(30) != us.end()) {
        cout << "30 found in unordered set" << endl;
    }
    
    cout << "Size: " << us.size() << endl;
    cout << "Bucket count: " << us.bucket_count() << endl;
}

// ============================================
// 12. MAP (Key-value pairs, sorted by key)
// ============================================
// HOW IT WORKS:
// - Red-Black tree where each node stores pair<key, value>
// - Sorted by key using comparison function
// - Keys are unique - inserting duplicate key updates value
// - Self-balancing ensures O(log n) operations
//
// STRUCTURE:
// Each node: [key|value|color|left*|right*|parent*]
//
// Tree example (key->value):
//         ("banana",3)
//        /            \
//   ("apple",5)    ("orange",7)
//                   /
//              ("grape",2)
//
// LOOKUP PROCESS:
// map["key"]:
// 1. Search tree using binary search on keys
// 2. If found, return reference to value
// 3. If not found, INSERT new node with default value, return reference
//    (This is why map["new_key"] creates entry!)
//
// at("key"):
// 1. Search tree like above
// 2. If found, return reference to value
// 3. If not found, throw exception (doesn't create entry)
//
// INSERTION:
// map[key] = value or map.insert({key, value})
// 1. Search for key
// 2. If exists, update value
// 3. If not, insert new node and rebalance tree
//
// TIME COMPLEXITY:
// - Insert: O(log n) - tree traversal + balance
// - Access/Find: O(log n) - binary search through tree
// - Erase: O(log n) - find + rebalance
// - Iteration: O(n) in sorted order by key
//
// SPACE COMPLEXITY: O(n) + tree overhead
//
// USE CASES:
// - Dictionary/associative array with sorted keys
// - Frequency counting (char/word -> count)
// - Caching with ordered keys
// - Symbol tables in compilers
// - Range queries on keys
// - Maintaining sorted mapping
void mapExample() {
    cout << "\n=== MAP EXAMPLE ===" << endl;
    
    map<string, int> m;
    
    // Insert elements
    m["apple"] = 5;
    m["banana"] = 3;
    m["orange"] = 7;
    m["grape"] = 2;
    
    cout << "Map elements (sorted by key): " << endl;
    for (auto& pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Access element
    cout << "Value of 'banana': " << m["banana"] << endl;
    
    // Find element
    if (m.find("orange") != m.end()) {
        cout << "Orange found with value: " << m["orange"] << endl;
    }
    
    // Update value
    m["apple"] = 10;
    
    // Erase element
    m.erase("grape");
    
    cout << "After modifications: " << endl;
    for (auto& pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    cout << "Map size: " << m.size() << endl;
}

// ============================================
// 13. MULTIMAP (Multiple values per key, sorted)
// ============================================
// HOW IT WORKS:
// - Red-Black tree allowing duplicate keys
// - Multiple key-value pairs with same key stored as separate nodes
// - Sorted by key; duplicate keys are adjacent in iteration order
// - No operator[] because key isn't unique (which value to return?)
//
// STRUCTURE:
//       ("fruit",2)
//      /           \
// ("fruit",1)   ("vegetable",5)
//     \              \
//  ("fruit",3)   ("vegetable",6)
//
// MULTIPLE VALUES FOR SAME KEY:
// All pairs with same key stored as separate nodes in tree
// equal_range(key) returns iterators to [first, last) occurrence
//
// QUERYING:
// multimap.count("fruit") -> 3
// auto range = multimap.equal_range("fruit")
// for(auto it = range.first; it != range.second; ++it)
//     process(it->second)  // gets all values for "fruit"
//
// TIME COMPLEXITY:
// - Insert: O(log n)
// - Find: O(log n) - finds any one occurrence
// - count(k): O(log n + m) where m is count of key k
// - equal_range: O(log n + m)
//
// SPACE COMPLEXITY: O(n) where n includes all pairs (duplicates count)
//
// USE CASES:
// - One-to-many relationships (student->courses)
// - Event scheduling (time->events at that time)
// - Inverted index (word->document IDs)
// - Graph adjacency list with weights
void multimapExample() {
    cout << "\n=== MULTIMAP EXAMPLE ===" << endl;
    
    multimap<string, int> mm;
    
    // Insert multiple values for same key
    mm.insert({"fruit", 1});
    mm.insert({"fruit", 2});
    mm.insert({"vegetable", 5});
    mm.insert({"fruit", 3});
    mm.insert({"vegetable", 6});
    
    cout << "Multimap elements: " << endl;
    for (auto& pair : mm) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    cout << "Count of 'fruit': " << mm.count("fruit") << endl;
    
    // Equal range
    auto range = mm.equal_range("fruit");
    cout << "All values for 'fruit': ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->second << " ";
    }
    cout << endl;
}

// ============================================
// 14. UNORDERED_MAP (Hash table, key-value pairs)
// ============================================
// HOW IT WORKS:
// - Hash table with chaining, each bucket stores key-value pairs
// - Hash function maps key to bucket index
// - No ordering - pairs stored by hash value of key
// - Automatic rehashing when load factor exceeded
//
// STRUCTURE:
// Buckets:  [0] -> ("apple",5) -> nullptr
//           [1] -> nullptr
//           [2] -> ("orange",7) -> ("banana",3) -> nullptr  (collision)
//           [3] -> ("grape",2) -> nullptr
//
// HASHING KEYS:
// For string "apple":
// hash("apple") = (complex hash function) % bucket_count = bucket index
// Different types have different hash functions (int, string, custom)
//
// COLLISION RESOLUTION:
// When hash("banana") == hash("orange"):
// Both stored in same bucket, forming linked list
// Search requires comparing keys in chain: compare keys, not just hash
//
// LOOKUP PROCESS:
// map["apple"]:
// 1. Compute hash("apple") to get bucket
// 2. Traverse bucket's chain comparing keys
// 3. If found, return reference to value
// 4. If not found, insert with default value, return reference
//
// at("apple"):
// Same as lookup but throws exception if not found (no insertion)
//
// REHASHING TRIGGER:
// load_factor = size / bucket_count
// When load_factor > max_load_factor (default 1.0):
// 1. Allocate new bucket array (typically 2x size)
// 2. Rehash all keys with new bucket_count
// 3. Move all pairs to new buckets
// 4. Delete old bucket array
//
// TIME COMPLEXITY:
// - Insert: O(1) average, O(n) worst case (rehash or long chain)
// - Access/Find: O(1) average, O(n) worst case (all in one bucket)
// - Erase: O(1) average, O(n) worst case
// Much faster than map for lookup! No log factor!
//
// SPACE COMPLEXITY: O(n + b) where b ≈ n to 2n buckets
//
// USE CASES:
// - Fast key-value lookup (cache, memoization)
// - Frequency counting without needing order
// - Adjacency list for graphs (node->neighbors)
// - Configuration/settings storage
// - When O(1) lookup critical, order not needed
// - Hash maps for two-sum, anagram grouping
void unorderedMapExample() {
    cout << "\n=== UNORDERED_MAP EXAMPLE ===" << endl;
    
    unordered_map<string, int> um;
    
    // Insert elements
    um["apple"] = 5;
    um["banana"] = 3;
    um["orange"] = 7;
    um["grape"] = 2;
    
    cout << "Unordered map elements (no specific order): " << endl;
    for (auto& pair : um) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Fast lookup (O(1) average)
    if (um.find("banana") != um.end()) {
        cout << "Banana found with value: " << um["banana"] << endl;
    }
    
    // Update using []
    um["apple"] += 5;
    
    cout << "Updated apple value: " << um["apple"] << endl;
    cout << "Size: " << um.size() << endl;
}

// ============================================
// 15. BITSET (Fixed-size sequence of bits)
// ============================================
// HOW IT WORKS:
// - Fixed-size array of bits (0s and 1s)
// - Stored efficiently: 1 bit per boolean (vs 8 bits for bool)
// - Size must be known at compile time (template parameter)
// - Internally stored in chunks (typically 32 or 64 bits per word)
//
// MEMORY EFFICIENCY:
// bool array[8]: 8 bytes (8 bits each)
// bitset<8>: 1 byte (1 bit each) - 8x more efficient!
//
// STORAGE REPRESENTATION:
// bitset<8> bs(42);  // 42 in binary = 00101010
// Memory: Single byte storing bits directly
// Index:  7 6 5 4 3 2 1 0
// Bit:    0 0 1 0 1 0 1 0
//
// BIT OPERATIONS:
// set(i): bits[i] = 1
// reset(i): bits[i] = 0
// flip(i): bits[i] = !bits[i]
// test(i): return bits[i]
//
// BITWISE OPERATIONS (hardware-level fast):
// bs1 & bs2: AND each bit pair
// bs1 | bs2: OR each bit pair
// bs1 ^ bs2: XOR each bit pair
// ~bs1: flip all bits
//
// These operations work on multiple bits simultaneously (SIMD)
//
// COUNT IMPLEMENTATION:
// Uses population count (popcount) - counts 1-bits
// Modern CPUs have hardware instruction for this: O(1) operation
// Without hardware: O(k) where k is number of words
//
// TIME COMPLEXITY:
// - set/reset/flip/test: O(1) - direct bit manipulation
// - Bitwise operations (&,|,^): O(k) where k = size/word_size, but very fast
// - count: O(1) with hardware popcount, O(k) otherwise
// - to_string/to_ulong: O(n)
//
// SPACE COMPLEXITY: O(n/8) bytes where n is bitset size
//
// USE CASES:
// - Space-efficient boolean flags (1M bools = 125KB vs 1MB)
// - Bit manipulation problems
// - Sieve of Eratosthenes (prime finding)
// - Representing sets as bitmasks
// - Subset generation (each bit = include/exclude)
// - Dynamic programming with bitmasks
// - Network packet flags, permissions
void bitsetExample() {
    cout << "\n=== BITSET EXAMPLE ===" << endl;
    
    bitset<8> bs1;
    bitset<8> bs2(42); // Binary: 00101010
    bitset<8> bs3(string("11001100"));
    
    cout << "bs1 (default): " << bs1 << endl;
    cout << "bs2 (42): " << bs2 << endl;
    cout << "bs3 (string): " << bs3 << endl;
    
    // Set and reset bits
    bs1.set(0);
    bs1.set(3);
    bs1.set(7);
    cout << "bs1 after setting bits: " << bs1 << endl;
    
    // Flip bits
    bs1.flip();
    cout << "bs1 after flip: " << bs1 << endl;
    
    // Bitwise operations
    bitset<8> bs4 = bs2 & bs3;
    bitset<8> bs5 = bs2 | bs3;
    
    cout << "bs2 & bs3: " << bs4 << endl;
    cout << "bs2 | bs3: " << bs5 << endl;
    
    // Count set bits
    cout << "Number of set bits in bs2: " << bs2.count() << endl;
    
    // Test specific bit
    cout << "Bit at position 1 in bs2: " << bs2.test(1) << endl;
}

// ============================================
// 16. PAIR and TUPLE
// ============================================
// HOW IT WORKS:
// 
// PAIR:
// - Simple struct with two public members: first and second
// - Template allows any two types: pair<T1, T2>
// - Stored contiguously in memory: [first][second]
// - Comparison operators defined lexicographically
//
// PAIR STRUCTURE:
// template<typename T1, typename T2>
// struct pair {
//     T1 first;
//     T2 second;
// };
//
// LEXICOGRAPHIC COMPARISON:
// pair<int,int> p1{1,2}, p2{1,3};
// p1 < p2 because: first equal, then compare second (2 < 3)
// Used for sorting: vector of pairs sorts by first, then second
//
// TUPLE:
// - Generalization of pair to N elements (N ≥ 0)
// - Access via get<index>(tuple)
// - Stored contiguously: [elem0][elem1][elem2]...
// - More overhead than pair, but more flexible
//
// MEMORY LAYOUT:
// pair<int, double>: [int:4 bytes][padding:4][double:8 bytes] = 16 bytes
// tuple<int,char,double>: [int:4][char:1][padding:3][double:8] = 16 bytes
//
// STRUCTURED BINDING (C++17):
// auto [a, b] = pair{1, 2};
// Compiler generates: auto __temp = pair{1,2}; int a = __temp.first; int b = __temp.second;
//
// TIME COMPLEXITY:
// - Create: O(1) - just assign members
// - Access (first/second or get<>): O(1) - direct member access
// - Comparison: O(k) where k is number of elements
//
// SPACE COMPLEXITY: O(1) - fixed size based on types (plus padding)
//
// USE CASES:
// - Returning multiple values from function
// - Storing coordinates: pair<int,int> for (x,y)
// - Map/set elements: pair<key,value>
// - Graph edges: pair<node1, node2>
// - Sorting by multiple criteria
// - Representing rational numbers: pair<numerator, denominator>
void pairTupleExample() {
    cout << "\n=== PAIR AND TUPLE EXAMPLE ===" << endl;
    
    // Pair
    pair<int, string> p1 = {1, "one"};
    pair<int, string> p2 = make_pair(2, "two");
    
    cout << "Pair p1: (" << p1.first << ", " << p1.second << ")" << endl;
    cout << "Pair p2: (" << p2.first << ", " << p2.second << ")" << endl;
    
    // Tuple
    tuple<int, string, double> t1 = {1, "hello", 3.14};
    
    cout << "Tuple elements: ";
    cout << get<0>(t1) << ", " << get<1>(t1) << ", " << get<2>(t1) << endl;
    
    // Structured binding (C++17)
    auto [num, str, dbl] = t1;
    cout << "Using structured binding: " << num << ", " << str << ", " << dbl << endl;
    
    // Vector of pairs (common usage)
    vector<pair<int, int>> coords = {{1, 2}, {3, 4}, {5, 6}};
    cout << "Vector of pairs: ";
    for (auto& coord : coords) {
        cout << "(" << coord.first << "," << coord.second << ") ";
    }
    cout << endl;
}

// ============================================
// 17. STRING (Character sequence)
// ============================================
// HOW IT WORKS:
// - Dynamic array of characters (similar to vector<char>)
// - Stores: pointer to character array, size, capacity
// - Null-terminated for C compatibility (but size stored separately)
// - Small String Optimization (SSO): short strings stored inline, no heap allocation
//
// SSO OPTIMIZATION:
// Short string (≤15 chars typically): stored directly in string object
// [c][h][a][r][s]...[size] (no heap allocation)
//
// Long string: uses dynamic allocation
// [pointer to heap][size][capacity]
// Heap: [l][o][n][g]...[s][t][r][i][n][g][\0]
//
// MEMORY LAYOUT:
// sizeof(string) typically 24-32 bytes even for short strings
// Union of: {inline buffer (16 bytes)} OR {pointer + size + capacity}
//
// CONCATENATION:
// s1 + s2:
// 1. Allocate new buffer of size (s1.size + s2.size + 1)
// 2. Copy s1 characters
// 3. Copy s2 characters
// 4. Add null terminator
// Expensive for large strings - O(n+m)
//
// SUBSTRING CREATION:
// s.substr(pos, len):
// 1. Allocate new string
// 2. Copy len characters starting at pos
// Creates new string, not view (C++17 has string_view for zero-copy)
//
// FIND OPERATION:
// s.find("pattern"):
// Uses string matching algorithm (typically naive O(n*m) or optimized)
// Returns position of first occurrence or string::npos
//
// TIME COMPLEXITY:
// - Access []: O(1) - direct array indexing
// - Concatenation (+): O(n+m) - must copy both strings
// - substr: O(k) where k is substring length
// - find: O(n*m) worst case, often better in practice
// - Insert/erase middle: O(n) - must shift characters
// - push_back: O(1) amortized (like vector)
//
// SPACE COMPLEXITY: 
// - Small strings: O(1) - stored inline
// - Large strings: O(n) - heap allocation
//
// USE CASES:
// - Text processing, parsing
// - User input handling
// - File paths, URLs
// - Protocol messages
// - DNA sequence analysis
// - Natural language processing
void stringExample() {
    cout << "\n=== STRING EXAMPLE ===" << endl;
    
    string s1 = "Hello";
    string s2 = " World";
    
    // Concatenation
    string s3 = s1 + s2;
    cout << "Concatenated: " << s3 << endl;
    
    // Length
    cout << "Length: " << s3.length() << endl;
    
    // Substring
    cout << "Substring (0, 5): " << s3.substr(0, 5) << endl;
    
    // Find
    size_t pos = s3.find("World");
    if (pos != string::npos) {
        cout << "'World' found at position: " << pos << endl;
    }
    
    // Replace
    string s4 = s3;
    s4.replace(6, 5, "C++");
    cout << "After replace: " << s4 << endl;
    
    // Character access
    cout << "Character at index 0: " << s3[0] << endl;
    
    // Iteration
    cout << "Characters: ";
    for (char c : s3) {
        cout << c << " ";
    }
    cout << endl;
    
    // String to number and vice versa
    string numStr = "12345";
    int num = stoi(numStr);
    cout << "String to int: " << num << endl;
    cout << "Int to string: " << to_string(num + 1) << endl;
}

// ============================================
// 18. GRAPH (Adjacency List and Matrix)
// ============================================
// HOW IT WORKS:
// Graphs represent relationships between objects (vertices/nodes connected by edges)
//
// ADJACENCY LIST:
// - Array/vector of lists, where list[i] contains neighbors of vertex i
// - Each vertex stores only its adjacent vertices
// - Memory efficient for sparse graphs (few edges)
// - Structure: vector<vector<int>> or vector<list<int>>
//
// Example graph:    0---1
//                   |   |
//                   2---3---4
// Adjacency list:
// 0: [1, 2]
// 1: [0, 3]
// 2: [0, 3, 4]
// 3: [1, 2, 4]
// 4: [2, 3]
//
// ADJACENCY MATRIX:
// - 2D array where matrix[i][j] = 1 if edge exists from i to j
// - Fast edge lookup: O(1) to check if edge exists
// - Memory intensive: O(V²) space even for sparse graphs
// - Better for dense graphs (many edges)
//
// Matrix for above:  0 1 2 3 4
//                 0 [0 1 1 0 0]
//                 1 [1 0 0 1 0]
//                 2 [1 0 0 1 1]
//                 3 [0 1 1 0 1]
//                 4 [0 0 1 1 0]
//
// WEIGHTED GRAPHS:
// - Adjacency list: store pairs (neighbor, weight)
// - Adjacency matrix: matrix[i][j] = weight (0 or ∞ for no edge)
//
// BFS (Breadth-First Search):
// - Explores level by level using queue
// - Process: visit node, add to queue, mark visited
// - Then process its neighbors, add unvisited to queue
// - Finds shortest path in unweighted graphs
//
// DFS (Depth-First Search):
// - Explores as far as possible before backtracking
// - Uses recursion (implicit stack) or explicit stack
// - Process: visit node, mark visited, recurse on unvisited neighbors
// - Used for cycle detection, topological sort, connected components
//
// TIME COMPLEXITY (V=vertices, E=edges):
// Adjacency List:
// - Space: O(V + E)
// - Add edge: O(1)
// - Check edge exists: O(degree(v)) - must scan neighbor list
// - Iterate neighbors: O(degree(v))
// - BFS/DFS: O(V + E) - visit each vertex and edge once
//
// Adjacency Matrix:
// - Space: O(V²)
// - Add edge: O(1)
// - Check edge exists: O(1) - direct array access
// - Iterate neighbors: O(V) - must scan entire row
// - BFS/DFS: O(V²) - checking all possible edges
//
// USE CASES:
// - Social networks (people as nodes, friendships as edges)
// - Road networks (cities as nodes, roads as edges)
// - Web page linking (pages as nodes, hyperlinks as edges)
// - Dependency resolution (tasks as nodes, dependencies as edges)
// - Circuit design, molecule structures, recommendation systems
void graphExample() {
    cout << "\n=== GRAPH EXAMPLE ===" << endl;
    
    int n = 5; // Number of vertices
    
    // Adjacency List (most common)
    vector<vector<int>> adjList(n);
    
    // Add edges (undirected graph)
    adjList[0].push_back(1);
    adjList[1].push_back(0);
    
    adjList[0].push_back(2);
    adjList[2].push_back(0);
    
    adjList[1].push_back(3);
    adjList[3].push_back(1);
    
    adjList[2].push_back(4);
    adjList[4].push_back(2);
    
    adjList[3].push_back(4);
    adjList[4].push_back(3);
    
    cout << "Adjacency List Representation:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    
    // Weighted graph using pair
    vector<vector<pair<int, int>>> weightedGraph(n); // {neighbor, weight}
    weightedGraph[0].push_back({1, 5});
    weightedGraph[0].push_back({2, 3});
    weightedGraph[1].push_back({3, 2});
    weightedGraph[2].push_back({4, 7});
    weightedGraph[3].push_back({4, 1});
    
    cout << "\nWeighted Adjacency List:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (auto& edge : weightedGraph[i]) {
            cout << "(" << edge.first << ",w=" << edge.second << ") ";
        }
        cout << endl;
    }
    
    // Adjacency Matrix
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    adjMatrix[0][1] = adjMatrix[1][0] = 1;
    adjMatrix[0][2] = adjMatrix[2][0] = 1;
    adjMatrix[1][3] = adjMatrix[3][1] = 1;
    adjMatrix[2][4] = adjMatrix[4][2] = 1;
    adjMatrix[3][4] = adjMatrix[4][3] = 1;
    
    cout << "\nAdjacency Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // BFS traversal
    cout << "\nBFS from vertex 0: ";
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        
        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
    
    // DFS traversal
    cout << "DFS from vertex 0: ";
    fill(visited.begin(), visited.end(), false);
    
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        cout << u << " ";
        for (int v : adjList[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    };
    
    dfs(0);
    cout << endl;
}

// ============================================
// 18b. ADJACENCY LIST (Detailed Implementation)
// ============================================
// HOW ADJACENCY LIST WORKS IN DETAIL:
// - Most memory-efficient representation for sparse graphs
// - Array/vector where index = vertex, value = list of neighbors
// - Can use vector<vector<int>>, vector<list<int>>, or map<int, vector<int>>
// - For weighted graphs: store pairs (neighbor, weight)
// - For directed graphs: adjList[u] contains v if edge u→v exists
//
// MEMORY COMPARISON:
// Graph with 1000 vertices, 5000 edges:
// - Adjacency Matrix: 1000×1000 = 1,000,000 entries (1MB for ints)
// - Adjacency List: 1000 + 2×5000 = 11,000 entries (11KB for ints)
// List is ~90x more memory efficient!
//
// TYPES OF ADJACENCY LISTS:
// 1. Unweighted: vector<vector<int>>
// 2. Weighted: vector<vector<pair<int,int>>> where pair = (neighbor, weight)
// 3. With edge info: vector<vector<Edge>> where Edge = struct with multiple fields
// 4. Sparse graphs: map<int, vector<int>> when vertex IDs are non-contiguous

class AdjacencyList {
private:
    int numVertices;
    vector<vector<int>> adj;           // Unweighted
    vector<vector<pair<int, int>>> weightedAdj;  // Weighted: (neighbor, weight)
    
public:
    AdjacencyList(int n) : numVertices(n) {
        adj.resize(n);
        weightedAdj.resize(n);
    }
    
    // Add undirected edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // For undirected graph
    }
    
    // Add directed edge
    void addDirectedEdge(int u, int v) {
        adj[u].push_back(v);  // Only u→v, not v→u
    }
    
    // Add weighted undirected edge
    void addWeightedEdge(int u, int v, int weight) {
        weightedAdj[u].push_back({v, weight});
        weightedAdj[v].push_back({u, weight});
    }
    
    // Add weighted directed edge
    void addWeightedDirectedEdge(int u, int v, int weight) {
        weightedAdj[u].push_back({v, weight});
    }
    
    // Get neighbors of vertex
    vector<int> getNeighbors(int u) {
        return adj[u];
    }
    
    // Get degree of vertex (number of edges)
    int getDegree(int u) {
        return adj[u].size();
    }
    
    // Check if edge exists (slower than matrix - O(degree))
    bool hasEdge(int u, int v) {
        for (int neighbor : adj[u]) {
            if (neighbor == v) return true;
        }
        return false;
    }
    
    // Remove edge
    void removeEdge(int u, int v) {
        // Remove v from u's list
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
        // Remove u from v's list (for undirected)
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
    }
    
    // Print adjacency list
    void print() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << ": ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    // Print weighted adjacency list
    void printWeighted() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << ": ";
            for (auto& edge : weightedAdj[i]) {
                cout << "(" << edge.first << ",w=" << edge.second << ") ";
            }
            cout << endl;
        }
    }
    
    // BFS traversal
    void bfs(int start) {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        cout << "BFS from " << start << ": ";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
    
    // DFS traversal (iterative with stack)
    void dfsIterative(int start) {
        vector<bool> visited(numVertices, false);
        stack<int> s;
        
        s.push(start);
        
        cout << "DFS (iterative) from " << start << ": ";
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            
            if (!visited[u]) {
                visited[u] = true;
                cout << u << " ";
                
                // Push neighbors in reverse order for consistent ordering
                for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
    
    // DFS traversal (recursive)
    void dfsRecursive(int start) {
        vector<bool> visited(numVertices, false);
        cout << "DFS (recursive) from " << start << ": ";
        dfsHelper(start, visited);
        cout << endl;
    }
    
    // Find shortest path using BFS (unweighted graph)
    vector<int> shortestPath(int start, int end) {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (u == end) break;
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        
        // Reconstruct path
        vector<int> path;
        if (parent[end] == -1 && start != end) {
            return path;  // No path exists
        }
        
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Detect cycle using DFS (for undirected graph)
    bool hasCycle() {
        vector<bool> visited(numVertices, false);
        
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                if (hasCycleHelper(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Find all connected components
    int countComponents() {
        vector<bool> visited(numVertices, false);
        int count = 0;
        
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                dfsHelper(i, visited);
                count++;
            }
        }
        return count;
    }
    
private:
    void dfsHelper(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsHelper(v, visited);
            }
        }
    }
    
    bool hasCycleHelper(int u, vector<bool>& visited, int parent) {
        visited[u] = true;
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                if (hasCycleHelper(v, visited, u)) {
                    return true;
                }
            } else if (v != parent) {
                // Visited neighbor that's not parent = cycle
                return true;
            }
        }
        return false;
    }
};

void adjacencyListExample() {
    cout << "\n=== ADJACENCY LIST DETAILED EXAMPLE ===" << endl;
    
    // Create graph with 6 vertices
    //     0 --- 1 --- 2
    //     |     |     |
    //     3 --- 4     5
    
    AdjacencyList graph(6);
    
    cout << "Building undirected graph:" << endl;
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    
    cout << "\nAdjacency List representation:" << endl;
    graph.print();
    
    cout << "\nDegree of each vertex:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Vertex " << i << ": degree " << graph.getDegree(i) << endl;
    }
    
    cout << "\nCheck if edges exist:" << endl;
    cout << "Edge 0-1: " << (graph.hasEdge(0, 1) ? "Yes" : "No") << endl;
    cout << "Edge 0-2: " << (graph.hasEdge(0, 2) ? "Yes" : "No") << endl;
    
    // Traversals
    graph.bfs(0);
    graph.dfsIterative(0);
    graph.dfsRecursive(0);
    
    // Shortest path
    cout << "\nShortest path from 0 to 5: ";
    vector<int> path = graph.shortestPath(0, 5);
    for (int v : path) {
        cout << v << " ";
    }
    cout << "(length: " << path.size() - 1 << " edges)" << endl;
    
    // Cycle detection
    cout << "\nHas cycle: " << (graph.hasCycle() ? "Yes" : "No") << endl;
    
    // Connected components
    cout << "Number of connected components: " << graph.countComponents() << endl;
    
    // Weighted graph example
    cout << "\n--- WEIGHTED GRAPH EXAMPLE ---" << endl;
    AdjacencyList weightedGraph(5);
    
    //      5
    //  0 ---- 1
    //  |  \   |
    // 2|   \3 |4
    //  |    \ |
    //  2 ---- 3
    //      6
    
    weightedGraph.addWeightedEdge(0, 1, 5);
    weightedGraph.addWeightedEdge(0, 2, 2);
    weightedGraph.addWeightedEdge(0, 3, 3);
    weightedGraph.addWeightedEdge(1, 3, 4);
    weightedGraph.addWeightedEdge(2, 3, 6);
    
    cout << "\nWeighted Adjacency List:" << endl;
    weightedGraph.printWeighted();
    
    // Directed graph example
    cout << "\n--- DIRECTED GRAPH EXAMPLE ---" << endl;
    AdjacencyList directedGraph(4);
    
    // 0 → 1 → 2
    // ↓       ↓
    // 3 ← ← ← 
    
    directedGraph.addDirectedEdge(0, 1);
    directedGraph.addDirectedEdge(0, 3);
    directedGraph.addDirectedEdge(1, 2);
    directedGraph.addDirectedEdge(2, 3);
    
    cout << "\nDirected Adjacency List:" << endl;
    directedGraph.print();
    
    // Edge removal example
    cout << "\n--- EDGE REMOVAL ---" << endl;
    AdjacencyList graph2(4);
    graph2.addEdge(0, 1);
    graph2.addEdge(0, 2);
    graph2.addEdge(1, 3);
    graph2.addEdge(2, 3);
    
    cout << "Before removing edge 0-1:" << endl;
    graph2.print();
    
    graph2.removeEdge(0, 1);
    cout << "\nAfter removing edge 0-1:" << endl;
    graph2.print();
    
    // Space efficiency demonstration
    cout << "\n--- SPACE EFFICIENCY ---" << endl;
    int vertices = 1000;
    int edges = 5000;
    size_t matrixSize = vertices * vertices * sizeof(int);
    size_t listSize = (vertices + 2 * edges) * sizeof(int);
    
    cout << "For graph with " << vertices << " vertices and " << edges << " edges:" << endl;
    cout << "Adjacency Matrix: " << matrixSize / 1024 << " KB" << endl;
    cout << "Adjacency List: " << listSize / 1024 << " KB" << endl;
    cout << "Space saved: " << (matrixSize - listSize) / 1024 << " KB ("
         << (100 * (matrixSize - listSize) / matrixSize) << "%)" << endl;
}

// ============================================
// 19. TREE (General Tree Structure)
// ============================================
// HOW IT WORKS:
// - Hierarchical data structure with root node and children
// - Each node can have any number of children (unlike binary tree)
// - No cycles - exactly one path between any two nodes
// - Nodes stored as objects with pointers to children
//
// TERMINOLOGY:
// - Root: topmost node (no parent)
// - Parent: node with children
// - Children: nodes directly connected below
// - Leaf: node with no children
// - Height: longest path from root to leaf
// - Depth: distance from root to node
// - Subtree: tree formed by node and all descendants
//
// STRUCTURE:
//        1 (root, height=3, depth=0)
//      / | \
//     2  3  4 (depth=1)
//    /|     |
//   5 6     7 (leaves, depth=2)
//
// NODE REPRESENTATION:
// struct TreeNode {
//     int val;
//     vector<TreeNode*> children;  // dynamic array of child pointers
// };
// Each node stores value + list of pointers to children
//
// TRAVERSAL METHODS:
//
// 1. LEVEL-ORDER (BFS):
//    Visit nodes level by level (use queue)
//    Above tree: 1, 2, 3, 4, 5, 6, 7
//    Algorithm:
//    - Enqueue root
//    - While queue not empty: dequeue, process, enqueue children
//
// 2. DFS PREORDER:
//    Visit node, then recurse on children
//    Above tree: 1, 2, 5, 6, 3, 4, 7
//    Algorithm: process(node), then for each child: preorder(child)
//
// 3. DFS POSTORDER:
//    Recurse on children, then visit node
//    Above tree: 5, 6, 2, 3, 7, 4, 1
//    Algorithm: for each child: postorder(child), then process(node)
//
// HEIGHT CALCULATION:
// height(node) = 1 + max(height of all children)
// Base case: height(null) = 0, height(leaf) = 1
// Recursively find max height among children
//
// TIME COMPLEXITY:
// - Access specific node: O(n) worst case - may need to traverse entire tree
// - Search: O(n) - must check all nodes in worst case
// - Insert: O(1) if parent known, O(n) if must find parent
// - Delete: O(1) if node known + has no children, else O(n)
// - Traversal: O(n) - visit each node exactly once
// - Height calculation: O(n) - must visit all nodes
//
// SPACE COMPLEXITY: 
// - O(n) for storing n nodes
// - O(h) for recursion stack during DFS where h is height
// - O(w) for queue during BFS where w is max width (nodes at one level)
//
// USE CASES:
// - File system hierarchy (folders and files)
// - Organization charts (employees and managers)
// - XML/HTML DOM (nested elements)
// - Expression trees in compilers
// - Game trees (chess moves, decision trees)
// - Taxonomy classifications
struct TreeNode {
    int val;
    vector<TreeNode*> children;
    
    TreeNode(int x) : val(x) {}
};

void treeExample() {
    cout << "\n=== TREE EXAMPLE ===" << endl;
    
    // Create a general tree
    //        1
    //      / | \
    //     2  3  4
    //    /|     |
    //   5 6     7
    
    TreeNode* root = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);
    
    root->children = {node2, node3, node4};
    node2->children = {node5, node6};
    node4->children = {node7};
    
    // Level-order traversal
    cout << "Level-order traversal: ";
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        
        for (TreeNode* child : node->children) {
            q.push(child);
        }
    }
    cout << endl;
    
    // DFS (preorder) traversal
    cout << "DFS (preorder) traversal: ";
    function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        for (TreeNode* child : node->children) {
            dfs(child);
        }
    };
    dfs(root);
    cout << endl;
    
    // Find height
    function<int(TreeNode*)> height = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int maxHeight = 0;
        for (TreeNode* child : node->children) {
            maxHeight = max(maxHeight, height(child));
        }
        return maxHeight + 1;
    };
    
    cout << "Tree height: " << height(root) << endl;
    
    // Count nodes
    function<int(TreeNode*)> countNodes = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int count = 1;
        for (TreeNode* child : node->children) {
            count += countNodes(child);
        }
        return count;
    };
    
    cout << "Total nodes: " << countNodes(root) << endl;
}

// ============================================
// 19b. HEAP (Binary Heap - Min and Max)
// ============================================
// HOW HEAP WORKS IN DETAIL:
// - Complete binary tree stored as array (implicit structure)
// - Heap property: parent ≥ children (max heap) or parent ≤ children (min heap)
// - Root is always max/min element
// - Efficiently supports: insert, extractMin/Max, peek
//
// ARRAY REPRESENTATION:
// Index:  0   1   2   3   4   5   6
// Array: [50, 30, 40, 10, 20, 15, 35]
//
// Tree visualization:
//           50 (index 0)
//         /    \
//       30(1)   40(2)
//      /  \     /  \
//    10(3) 20(4) 15(5) 35(6)
//
// PARENT-CHILD RELATIONSHIPS (0-indexed):
// Parent of i: (i-1)/2
// Left child of i: 2*i+1
// Right child of i: 2*i+2
//
// COMPLETE TREE PROPERTY:
// - All levels filled except possibly last
// - Last level filled left to right
// - No "holes" in array representation
// - This makes array storage efficient and natural
//
// HEAP OPERATIONS:
//
// 1. INSERT (Bubble Up):
//    - Add element at end of array (maintains complete tree)
//    - Compare with parent
//    - If violates heap property, swap with parent
//    - Repeat until heap property satisfied or reach root
//    Time: O(log n) - at most height comparisons
//
// 2. EXTRACT_MAX/MIN (Bubble Down):
//    - Remove root (max/min element)
//    - Move last element to root
//    - Compare with children
//    - Swap with larger child (max heap) or smaller child (min heap)
//    - Repeat until heap property satisfied or reach leaf
//    Time: O(log n)
//
// 3. HEAPIFY (Build heap from array):
//    - Start from last non-leaf: (n/2 - 1)
//    - Apply bubble down on each node going backwards
//    - More efficient than n insertions!
//    Time: O(n) - surprising but provable
//
// HEAP vs BST:
// Heap: partial ordering (only parent-child), O(1) find min/max
// BST: total ordering (inorder sorted), O(log n) find min/max
// Heap: better for priority queue, BST: better for searching

template<typename T>
class MinHeap {
private:
    vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void bubbleUp(int i) {
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void bubbleDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }
        if (right < heap.size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }
        
        if (i != minIndex) {
            swap(heap[i], heap[minIndex]);
            bubbleDown(minIndex);
        }
    }
    
public:
    MinHeap() {}
    
    MinHeap(vector<T> arr) {
        heap = arr;
        // Build heap - start from last non-leaf and bubble down
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            bubbleDown(i);
        }
    }
    
    void insert(T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }
    
    T extractMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        
        T minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            bubbleDown(0);
        }
        
        return minVal;
    }
    
    T getMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }
    
    bool empty() { return heap.size() == 0; }
    int size() { return heap.size(); }
    
    void print() {
        cout << "Heap array: [";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i];
            if (i < heap.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    void printTree() {
        if (heap.empty()) return;
        
        int height = log2(heap.size()) + 1;
        int index = 0;
        int levelSize = 1;
        
        for (int level = 0; level < height && index < heap.size(); level++) {
            for (int i = 0; i < levelSize && index < heap.size(); i++) {
                cout << heap[index++] << " ";
            }
            cout << endl;
            levelSize *= 2;
        }
    }
};

template<typename T>
class MaxHeap {
private:
    vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void bubbleUp(int i) {
        while (i > 0 && heap[i] > heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void bubbleDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }
        if (right < heap.size() && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }
        
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            bubbleDown(maxIndex);
        }
    }
    
public:
    MaxHeap() {}
    
    MaxHeap(vector<T> arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            bubbleDown(i);
        }
    }
    
    void insert(T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }
    
    T extractMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        
        T maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            bubbleDown(0);
        }
        
        return maxVal;
    }
    
    T getMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }
    
    bool empty() { return heap.size() == 0; }
    int size() { return heap.size(); }
    
    void print() {
        cout << "Heap array: [";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i];
            if (i < heap.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    void printTree() {
        if (heap.empty()) return;
        
        int height = log2(heap.size()) + 1;
        int index = 0;
        int levelSize = 1;
        
        for (int level = 0; level < height && index < heap.size(); level++) {
            for (int i = 0; i < levelSize && index < heap.size(); i++) {
                cout << heap[index++] << " ";
            }
            cout << endl;
            levelSize *= 2;
        }
    }
};

void heapExample() {
    cout << "\n=== HEAP EXAMPLE ===" << endl;
    
    // MIN HEAP EXAMPLE
    cout << "--- MIN HEAP ---" << endl;
    MinHeap<int> minHeap;
    
    cout << "Inserting: 50, 30, 40, 10, 20, 15, 35" << endl;
    minHeap.insert(50);
    minHeap.insert(30);
    minHeap.insert(40);
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(15);
    minHeap.insert(35);
    
    minHeap.print();
    cout << "\nTree representation (level-order):" << endl;
    minHeap.printTree();
    
    cout << "\nMinimum element: " << minHeap.getMin() << endl;
    cout << "Heap size: " << minHeap.size() << endl;
    
    cout << "\nExtracting elements (will come out in sorted order):" << endl;
    while (!minHeap.empty()) {
        cout << minHeap.extractMin() << " ";
    }
    cout << endl;
    
    // MAX HEAP EXAMPLE
    cout << "\n--- MAX HEAP ---" << endl;
    MaxHeap<int> maxHeap;
    
    cout << "Inserting: 10, 20, 15, 30, 25, 40, 35" << endl;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(15);
    maxHeap.insert(30);
    maxHeap.insert(25);
    maxHeap.insert(40);
    maxHeap.insert(35);
    
    maxHeap.print();
    cout << "\nTree representation (level-order):" << endl;
    maxHeap.printTree();
    
    cout << "\nMaximum element: " << maxHeap.getMax() << endl;
    
    cout << "\nExtracting elements (descending order):" << endl;
    while (!maxHeap.empty()) {
        cout << maxHeap.extractMax() << " ";
    }
    cout << endl;
    
    // BUILD HEAP FROM ARRAY (HEAPIFY)
    cout << "\n--- HEAPIFY (Build heap from array) ---" << endl;
    vector<int> arr = {50, 30, 20, 15, 10, 8, 16};
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    MinHeap<int> heapFromArray(arr);
    cout << "After heapify (min heap): ";
    heapFromArray.print();
    
    MaxHeap<int> maxHeapFromArray(arr);
    cout << "After heapify (max heap): ";
    maxHeapFromArray.print();
    
    // HEAP SORT
    cout << "\n--- HEAP SORT ---" << endl;
    vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    cout << "Unsorted array: ";
    for (int x : unsorted) cout << x << " ";
    cout << endl;
    
    // Build max heap
    MaxHeap<int> sortHeap(unsorted);
    
    // Extract elements (they come out in descending order)
    vector<int> sorted;
    while (!sortHeap.empty()) {
        sorted.push_back(sortHeap.extractMax());
    }
    
    // Reverse for ascending order
    reverse(sorted.begin(), sorted.end());
    cout << "Sorted array: ";
    for (int x : sorted) cout << x << " ";
    cout << endl;
    
    // PRIORITY QUEUE SIMULATION
    cout << "\n--- PRIORITY QUEUE SIMULATION ---" << endl;
    cout << "Task scheduling with priorities (higher number = higher priority)" << endl;
    
    struct Task {
        string name;
        int priority;
        
        bool operator>(const Task& other) const {
            return priority > other.priority;
        }
        bool operator<(const Task& other) const {
            return priority < other.priority;
        }
    };
    
    MaxHeap<int> taskQueue;
    map<int, string> tasks;
    
    tasks[5] = "Email";
    tasks[10] = "Meeting";
    tasks[3] = "Coffee";
    tasks[8] = "Code Review";
    tasks[7] = "Documentation";
    
    cout << "\nAdding tasks:" << endl;
    for (auto& [priority, name] : tasks) {
        cout << "  " << name << " (priority: " << priority << ")" << endl;
        taskQueue.insert(priority);
    }
    
    cout << "\nProcessing tasks by priority:" << endl;
    while (!taskQueue.empty()) {
        int priority = taskQueue.extractMax();
        cout << "  Executing: " << tasks[priority] << " (priority: " << priority << ")" << endl;
    }
    
    // K LARGEST ELEMENTS
    cout << "\n--- FIND K LARGEST ELEMENTS ---" << endl;
    vector<int> nums = {12, 5, 787, 1, 23, 56, 89, 34, 100};
    int k = 3;
    
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    
    MinHeap<int> kHeap;
    for (int num : nums) {
        kHeap.insert(num);
        if (kHeap.size() > k) {
            kHeap.extractMin();  // Remove smallest to keep only k largest
        }
    }
    
    cout << k << " largest elements: ";
    vector<int> kLargest;
    while (!kHeap.empty()) {
        kLargest.push_back(kHeap.extractMin());
    }
    sort(kLargest.rbegin(), kLargest.rend());
    for (int x : kLargest) cout << x << " ";
    cout << endl;
    
    // MEDIAN MAINTENANCE
    cout << "\n--- MEDIAN MAINTENANCE (Two Heaps) ---" << endl;
    cout << "Find median dynamically as numbers arrive" << endl;
    
    MaxHeap<int> lowerHalf;  // Max heap for lower half
    MinHeap<int> upperHalf;  // Min heap for upper half
    
    vector<int> stream = {5, 15, 1, 3, 8, 7, 9, 10};
    cout << "\nStream: ";
    for (int x : stream) cout << x << " ";
    cout << endl << endl;
    
    cout << "Medians as numbers arrive:" << endl;
    for (int num : stream) {
        // Add to appropriate heap
        if (lowerHalf.empty() || num <= lowerHalf.getMax()) {
            lowerHalf.insert(num);
        } else {
            upperHalf.insert(num);
        }
        
        // Rebalance heaps (sizes differ by at most 1)
        if (lowerHalf.size() > upperHalf.size() + 1) {
            upperHalf.insert(lowerHalf.extractMax());
        } else if (upperHalf.size() > lowerHalf.size() + 1) {
            lowerHalf.insert(upperHalf.extractMin());
        }
        
        // Calculate median
        double median;
        if (lowerHalf.size() == upperHalf.size()) {
            median = (lowerHalf.getMax() + upperHalf.getMin()) / 2.0;
        } else if (lowerHalf.size() > upperHalf.size()) {
            median = lowerHalf.getMax();
        } else {
            median = upperHalf.getMin();
        }
        
        cout << "  After " << num << ": median = " << median << endl;
    }
    
    // TIME COMPLEXITY ANALYSIS
    cout << "\n--- COMPLEXITY ANALYSIS ---" << endl;
    cout << "Operation         | Time Complexity | Space" << endl;
    cout << "------------------|-----------------|-------" << endl;
    cout << "Insert            | O(log n)        | O(1)" << endl;
    cout << "Extract Min/Max   | O(log n)        | O(1)" << endl;
    cout << "Get Min/Max       | O(1)            | O(1)" << endl;
    cout << "Build Heap        | O(n)            | O(1)" << endl;
    cout << "Heap Sort         | O(n log n)      | O(1)" << endl;
    cout << "Find Kth largest  | O(n log k)      | O(k)" << endl;
    cout << "Median (2 heaps)  | O(log n) insert | O(n)" << endl;
}

// ============================================
// 20. BINARY SEARCH TREE (BST)
// ============================================
// HOW IT WORKS:
// - Binary tree with ordering property: left < parent < right
// - Each node has at most 2 children
// - For any node N: all values in left subtree < N, all in right subtree > N
// - This property enables binary search: O(log n) average case
//
// BST PROPERTY:
//         50
//        /  \
//      30    70
//     / \    / \
//   20  40  60  80
//
// All in left subtree of 50: {20,30,40} < 50
// All in right subtree of 50: {60,70,80} > 50
//
// SEARCH OPERATION:
// To find value x starting at root:
// 1. If node is null, not found
// 2. If node.val == x, found!
// 3. If x < node.val, search left subtree
// 4. If x > node.val, search right subtree
// This eliminates half the tree at each step!
//
// INSERTION:
// To insert value x:
// 1. Search for position (as above)
// 2. When reach null, create new node there
// 3. Maintains BST property automatically
// Example: Insert 35 into above tree
// 50 > 35, go left → 30 < 35, go right → 40 > 35, go left → insert
//
// DELETION (3 cases):
// Case 1: Node is leaf (no children)
//   - Simply remove it
// Case 2: Node has one child
//   - Replace node with its child
// Case 3: Node has two children
//   - Find inorder successor (smallest in right subtree)
//   - Copy successor's value to node
//   - Delete successor (which has at most one child)
//
// TRAVERSALS:
// Inorder (left, root, right): 20,30,40,50,60,70,80 - SORTED!
// Preorder (root, left, right): 50,30,20,40,70,60,80
// Postorder (left, right, root): 20,40,30,60,80,70,50
//
// INORDER gives sorted output - key property of BST!
//
// HEIGHT:
// - Balanced BST: height = O(log n)
// - Skewed BST (basically linked list): height = O(n)
// Example of skewed: insert 1,2,3,4,5 in order:
//   1
//    \
//     2
//      \
//       3
//        \
//         4
//          \
//           5
//
// TIME COMPLEXITY:
// Best/Average case (balanced tree):
// - Search: O(log n) - eliminate half each time
// - Insert: O(log n) - search for position + insert
// - Delete: O(log n) - search + restructure
//
// Worst case (skewed tree):
// - All operations: O(n) - degenerates to linked list
//
// Self-balancing BSTs (AVL, Red-Black) guarantee O(log n) by rebalancing
//
// SPACE COMPLEXITY: O(n) for n nodes + O(h) recursion stack
//
// USE CASES:
// - Implementing set/map (though usually use self-balancing variants)
// - Database indexing
// - Priority queues with search capability
// - Symbol tables in compilers
// - Finding kth smallest/largest element
// - Range queries (find all elements between x and y)
struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    
    BSTNode* insert(BSTNode* node, int val) {
        if (!node) return new BSTNode(val);
        
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        return node;
    }
    
    BSTNode* search(BSTNode* node, int val) {
        if (!node || node->val == val) return node;
        
        if (val < node->val) {
            return search(node->left, val);
        }
        return search(node->right, val);
    }
    
    BSTNode* findMin(BSTNode* node) {
        while (node->left) node = node->left;
        return node;
    }
    
    BSTNode* remove(BSTNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->val) {
            node->left = remove(node->left, val);
        } else if (val > node->val) {
            node->right = remove(node->right, val);
        } else {
            // Node found
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            } else {
                // Two children
                BSTNode* temp = findMin(node->right);
                node->val = temp->val;
                node->right = remove(node->right, temp->val);
            }
        }
        return node;
    }
    
    void inorder(BSTNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }
    
    void preorder(BSTNode* node) {
        if (!node) return;
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }
    
    void postorder(BSTNode* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }
    
    int height(BSTNode* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
    
public:
    BST() : root(nullptr) {}
    
    void insert(int val) {
        root = insert(root, val);
    }
    
    bool search(int val) {
        return search(root, val) != nullptr;
    }
    
    void remove(int val) {
        root = remove(root, val);
    }
    
    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
    
    void preorderTraversal() {
        preorder(root);
        cout << endl;
    }
    
    void postorderTraversal() {
        postorder(root);
        cout << endl;
    }
    
    int getHeight() {
        return height(root);
    }
};

void bstExample() {
    cout << "\n=== BINARY SEARCH TREE EXAMPLE ===" << endl;
    
    BST bst;
    
    // Insert elements
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    cout << "Inorder traversal (sorted): ";
    bst.inorderTraversal();
    
    cout << "Preorder traversal: ";
    bst.preorderTraversal();
    
    cout << "Postorder traversal: ";
    bst.postorderTraversal();
    
    cout << "Tree height: " << bst.getHeight() << endl;
    
    // Search
    cout << "Search for 40: " << (bst.search(40) ? "Found" : "Not found") << endl;
    cout << "Search for 25: " << (bst.search(25) ? "Found" : "Not found") << endl;
    
    // Remove
    cout << "Removing 30..." << endl;
    bst.remove(30);
    cout << "Inorder after removal: ";
    bst.inorderTraversal();
}

// ============================================
// 21. NETWORK FLOW (Max Flow - Ford-Fulkerson)
// ============================================
// HOW IT WORKS:
// Flow network: directed graph with capacities on edges
// Goal: maximize flow from source s to sink t
//
// CONCEPTS:
// - Capacity: maximum flow an edge can carry
// - Flow: actual amount flowing through edge (0 ≤ flow ≤ capacity)
// - Source (s): node where flow originates (infinite supply)
// - Sink (t): node where flow terminates (infinite demand)
// - Conservation: for all nodes except s,t: inflow = outflow
//
// RESIDUAL GRAPH:
// For each edge with capacity c and flow f:
// - Forward edge: residual capacity = c - f (can push more flow)
// - Backward edge: residual capacity = f (can cancel existing flow)
//
// Example: edge A→B, capacity=10, current flow=7
// Residual: A→B with capacity 3 (can add 3 more)
//           B→A with capacity 7 (can cancel up to 7)
//
// FORD-FULKERSON ALGORITHM:
// 1. Start with zero flow on all edges
// 2. While there exists augmenting path from s to t in residual graph:
//    a. Find path using BFS/DFS
//    b. Compute bottleneck = min capacity along path
//    c. Push bottleneck units of flow along path
//    d. Update residual graph (decrease forward, increase backward)
// 3. Return sum of flows leaving source
//
// AUGMENTING PATH:
// Path from s to t in residual graph with positive capacity
// Finding one means we can increase total flow
//
// EXAMPLE:
//      10           10
//  s -----> 1 -----> t
//  |                 ^
//  |10              |10
//  v                |
//  2 -------------->
//        10
//
// Iteration 1: Path s→1→t, flow=10
// Iteration 2: Path s→2→t, flow=10
// Max flow = 20
//
// WHY BACKWARD EDGES?
// Allow algorithm to "undo" bad decisions
// Example: pushed flow through wrong path, backward edge lets us reroute
//
// EDMONDS-KARP (using BFS):
// Ford-Fulkerson with BFS to find augmenting paths
// Guarantees O(VE²) time complexity
// BFS finds shortest augmenting path (fewest edges)
//
// MAX-FLOW MIN-CUT THEOREM:
// Maximum flow value = minimum cut capacity
// Cut: partition of vertices into S (contains s) and T (contains t)
// Cut capacity: sum of capacities of edges from S to T
//
// TIME COMPLEXITY:
// - Ford-Fulkerson: O(E * max_flow) - depends on flow value!
// - Edmonds-Karp (BFS): O(V * E²) - polynomial guarantee
// - Dinic's algorithm: O(V² * E) - faster for dense graphs
//
// SPACE COMPLEXITY: O(V²) for capacity matrix, O(V) for BFS
//
// USE CASES:
// - Network routing (internet traffic, water/gas distribution)
// - Bipartite matching (assign workers to jobs)
// - Image segmentation (cut graph to separate foreground/background)
// - Airline scheduling (flights and connections)
// - Project selection (maximize profit with dependencies)
// - Baseball elimination (determine if team can win)
class MaxFlow {
private:
    int n;
    vector<vector<int>> capacity;
    vector<vector<int>> adjList;
    
    bool bfs(int source, int sink, vector<int>& parent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adjList[u]) {
                if (!visited[v] && capacity[u][v] > 0) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                    
                    if (v == sink) return true;
                }
            }
        }
        return false;
    }
    
public:
    MaxFlow(int vertices) : n(vertices) {
        capacity.resize(n, vector<int>(n, 0));
        adjList.resize(n);
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    int fordFulkerson(int source, int sink) {
        vector<int> parent(n);
        int maxFlow = 0;
        
        // While there exists augmenting path
        while (bfs(source, sink, parent)) {
            // Find minimum capacity along the path
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, capacity[u][v]);
            }
            
            // Update residual capacities
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= pathFlow;
                capacity[v][u] += pathFlow;
            }
            
            maxFlow += pathFlow;
        }
        
        return maxFlow;
    }
    
    void printFlow() {
        cout << "Flow network edges:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (capacity[i][j] > 0) {
                    cout << i << " -> " << j << " (capacity: " << capacity[i][j] << ")" << endl;
                }
            }
        }
    }
};

void networkFlowExample() {
    cout << "\n=== NETWORK FLOW EXAMPLE ===" << endl;
    
    // Create a flow network
    //        10
    //    0 ----> 1
    //    |       |
    // 10 |       | 10
    //    v       v
    //    2 ----> 3
    //        10
    
    MaxFlow flow(4);
    flow.addEdge(0, 1, 10);
    flow.addEdge(0, 2, 10);
    flow.addEdge(1, 3, 10);
    flow.addEdge(2, 3, 10);
    
    cout << "Network structure:" << endl;
    flow.printFlow();
    
    int source = 0, sink = 3;
    int maxFlow = flow.fordFulkerson(source, sink);
    
    cout << "\nMaximum flow from " << source << " to " << sink << ": " << maxFlow << endl;
    
    // Another example with more complex network
    MaxFlow flow2(6);
    flow2.addEdge(0, 1, 16);
    flow2.addEdge(0, 2, 13);
    flow2.addEdge(1, 2, 10);
    flow2.addEdge(1, 3, 12);
    flow2.addEdge(2, 1, 4);
    flow2.addEdge(2, 4, 14);
    flow2.addEdge(3, 2, 9);
    flow2.addEdge(3, 5, 20);
    flow2.addEdge(4, 3, 7);
    flow2.addEdge(4, 5, 4);
    
    int maxFlow2 = flow2.fordFulkerson(0, 5);
    cout << "\nComplex network max flow from 0 to 5: " << maxFlow2 << endl;
}

// ============================================
// 22. CIRCULATION (Flow with Demands)
// ============================================
// HOW IT WORKS:
// Extension of max flow where:
// - Edges have BOTH lower and upper bounds: l(e) ≤ f(e) ≤ u(e)
// - Nodes may have demands/supplies (not just source/sink)
// - Goal: find feasible flow satisfying all constraints
//
// CONSTRAINTS:
// 1. Capacity: lower_bound ≤ flow ≤ upper_bound on each edge
// 2. Conservation: Σ(inflow) - Σ(outflow) = demand(v) for each node
//    - demand > 0: node requires net inflow (sink-like)
//    - demand < 0: node provides net outflow (source-like)
//    - demand = 0: flow conservation like regular nodes
// 3. Feasibility: sum of all demands must equal zero
//
// EXAMPLE:
// Node demands: d(A)=-10, d(B)=+5, d(C)=+5
// Edge A→B: [lower=2, upper=8]
// Edge A→C: [lower=3, upper=7]
// Edge B→C: [lower=0, upper=5]
//
// Valid circulation:
// f(A→B)=5, f(A→C)=5, f(B→C)=0
// Check: A sends 10, B receives 5 (needs 5), C receives 5 (needs 5) ✓
//
// REDUCTION TO MAX FLOW:
// Transform circulation problem to standard max flow:
// 1. For each edge with lower bound l:
//    - Send l units as "mandatory flow"
//    - Adjust node demands: demand(u) -= l, demand(v) += l
//    - New edge capacity: upper - lower
// 2. Create super-source s' and super-sink t'
// 3. For each node v with demand > 0: add edge s'→v with capacity=demand
// 4. For each node v with demand < 0: add edge v→t' with capacity=-demand
// 5. Find max flow from s' to t'
// 6. Circulation exists iff max flow = sum of positive demands
//
// WHY LOWER BOUNDS MATTER:
// Example: Pipeline must maintain minimum pressure
// Contractual obligations: must ship at least X units
// Physical constraints: valve must be partially open
//
// FEASIBILITY CHECK:
// Necessary condition: Σ demands = 0
// If Σ > 0: need more inflow than available
// If Σ < 0: producing more than consumed
//
// TIME COMPLEXITY:
// Same as max flow algorithm used (typically O(VE²) with Edmonds-Karp)
// Plus O(E) for transformation
//
// SPACE COMPLEXITY: O(V + E) for graph representation
//
// USE CASES:
// - Supply chain with minimum shipping requirements
// - Power grids with load balancing
// - Traffic networks with minimum/maximum capacity roads
// - Irrigation systems with minimum water requirements
// - Production planning with quotas and limits
class Circulation {
private:
    struct Edge {
        int to, capacity, flow, demand;
    };
    
    int n;
    vector<vector<int>> adjList;
    vector<Edge> edges;
    vector<int> excess;
    
public:
    Circulation(int vertices) : n(vertices) {
        adjList.resize(n);
        excess.resize(n, 0);
    }
    
    void addEdge(int from, int to, int lowerBound, int upperBound) {
        int edgeIdx = edges.size();
        
        edges.push_back({to, upperBound - lowerBound, 0, lowerBound});
        adjList[from].push_back(edgeIdx);
        
        // Reverse edge
        edges.push_back({from, 0, 0, 0});
        adjList[to].push_back(edgeIdx + 1);
        
        // Update excess based on lower bound
        excess[from] -= lowerBound;
        excess[to] += lowerBound;
    }
    
    bool hasCirculation() {
        // Simple check: sum of excesses should be 0
        int totalExcess = 0;
        for (int e : excess) {
            totalExcess += e;
        }
        return totalExcess == 0;
    }
    
    void printCirculation() {
        cout << "Circulation edges (with demands):" << endl;
        for (int u = 0; u < n; u++) {
            for (int edgeIdx : adjList[u]) {
                Edge& e = edges[edgeIdx];
                if (edgeIdx % 2 == 0 && e.capacity > 0) {
                    cout << u << " -> " << e.to 
                         << " [" << e.demand << ", " << (e.capacity + e.demand) << "]" << endl;
                }
            }
        }
        
        cout << "\nNode excesses:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Node " << i << ": " << excess[i] << endl;
        }
    }
};

void circulationExample() {
    cout << "\n=== CIRCULATION EXAMPLE ===" << endl;
    
    // Create a circulation network with lower and upper bounds
    Circulation circ(4);
    
    // addEdge(from, to, lowerBound, upperBound)
    circ.addEdge(0, 1, 2, 10);
    circ.addEdge(0, 2, 1, 8);
    circ.addEdge(1, 3, 3, 12);
    circ.addEdge(2, 3, 2, 9);
    
    circ.printCirculation();
    
    cout << "\nHas valid circulation: " 
         << (circ.hasCirculation() ? "Yes" : "No") << endl;
    
    cout << "\nCirculation is a flow that satisfies:" << endl;
    cout << "1. Capacity constraints: lower_bound <= flow <= upper_bound" << endl;
    cout << "2. Conservation: inflow = outflow at each node" << endl;
    cout << "3. Demands: flow must satisfy minimum requirements" << endl;
}

// ============================================
// 23. MIN CUT (From Max Flow)
// ============================================
// HOW IT WORKS:
// Cut: partition of graph vertices into two sets S and T
// - S contains source s, T contains sink t
// - Cut edges: edges going from S to T
// - Cut capacity: sum of capacities of cut edges
//
// MIN CUT PROBLEM:
// Find cut with minimum total capacity
// Separates source from sink with least capacity removed
//
// MAX-FLOW MIN-CUT THEOREM:
// Value of maximum flow = Capacity of minimum cut
// This is fundamental duality in network flows!
//
// PROOF INTUITION:
// - Flow out of S = flow into T (conservation)
// - Flow ≤ capacity of cut edges (can't exceed)
// - At max flow, some cut becomes saturated (all edges full)
// - This saturated cut is the minimum cut
//
// FINDING MIN CUT (after computing max flow):
// 1. Compute max flow from s to t
// 2. In residual graph, find all vertices reachable from s (BFS/DFS)
// 3. S = reachable vertices, T = unreachable vertices
// 4. Min cut = edges from S to T
//
// WHY THIS WORKS:
// After max flow, no augmenting path exists
// Reachable vertices: can still push flow (not saturated path)
// Cut edges between reachable/unreachable must be saturated
// These form the bottleneck = minimum cut
//
// EXAMPLE:
//      10           10
//  s -----> 1 -----> t
//  |                 ^
//  |10              |10
//  v                |
//  2 -------------->
//        10
//
// After max flow = 20:
// Residual graph: s has no path to t
// Reachable: {s}, Unreachable: {1, 2, t}
// Min cut edges: s→1 (cap 10) and s→2 (cap 10)
// Min cut capacity = 20 = max flow ✓
//
// TIME COMPLEXITY:
// O(max flow algorithm) + O(V+E) for finding reachable set
// Typically O(VE²) total with Edmonds-Karp
//
// SPACE COMPLEXITY: O(V+E)
//
// USE CASES:
// - Network reliability: find weakest links
// - Image segmentation: separate object from background
// - Clustering: partition graph into cohesive groups
// - VLSI design: minimize wire cuts between components
// - Social network analysis: identify community boundaries
// - Security: find minimum set of connections to monitor
void minCutExample() {
    cout << "\n=== MIN CUT EXAMPLE ===" << endl;
    
    cout << "Min-Cut is dual to Max-Flow (Max-Flow Min-Cut Theorem)" << endl;
    cout << "After computing max flow, perform DFS from source in residual graph" << endl;
    
    // Simple example
    MaxFlow flow(4);
    flow.addEdge(0, 1, 10);
    flow.addEdge(0, 2, 10);
    flow.addEdge(1, 3, 10);
    flow.addEdge(2, 3, 10);
    
    int maxFlow = flow.fordFulkerson(0, 3);
    
    cout << "\nMax flow = Min cut capacity = " << maxFlow << endl;
    cout << "The min-cut separates the graph into two sets:" << endl;
    cout << "Source side: {0, 1, 2}" << endl;
    cout << "Sink side: {3}" << endl;
    cout << "Cut edges: (1->3) and (2->3)" << endl;
}

// ============================================
// 24. BIPARTITE MATCHING (Using Max Flow)
// ============================================
// HOW IT WORKS:
// Bipartite graph: vertices divided into two disjoint sets L and R
// - All edges go between L and R (no edges within L or within R)
// - Matching: set of edges with no shared vertices
// - Maximum matching: matching with maximum number of edges
//
// BIPARTITE STRUCTURE:
// Left (L)    Right (R)
//   A ----------- 1
//   A ----------- 2
//   B ----------- 1
//   B ----------- 3
//   C ----------- 2
//
// Valid matching: {A-1, B-3, C-2} - all vertices matched
// Invalid: {A-1, B-1} - vertex 1 used twice
//
// REDUCTION TO MAX FLOW:
// Transform bipartite matching to flow problem:
// 1. Add source s connected to all left vertices (capacity 1)
// 2. Add sink t connected from all right vertices (capacity 1)
// 3. Original edges have capacity 1
// 4. Max flow = maximum matching size
//
// Why capacity 1? Each vertex can be in at most one matching edge
//
// FLOW INTERPRETATION:
// Flow of 1 on edge (L_i, R_j) means L_i matched to R_j
// Source ensures each left vertex matched at most once
// Sink ensures each right vertex matched at most once
//
// AUGMENTING PATH = ALTERNATING PATH:
// Path that alternates between unmatched and matched edges
// Finding one means we can increase matching size
//
// EXAMPLE:
// L={Workers: Alice, Bob, Carol}
// R={Jobs: Job1, Job2, Job3}
// Edges (qualifications):
// Alice-Job1, Alice-Job2
// Bob-Job1, Bob-Job3  
// Carol-Job2
//
// Flow network:
// s → Alice (1) → Job1 (1) → t
//   → Bob (1) → Job2 (1) → t
//   → Carol (1) → Job3 (1) → t
//
// Max flow = 3, so maximum matching = 3 (everyone gets a job)
// Matching: {Alice-Job2, Bob-Job3, Carol-Job1}
//
// PERFECT MATCHING:
// Matching that covers all vertices
// Exists if max matching = min(|L|, |R|) = |L| (when |L|≤|R|)
//
// HALL'S MARRIAGE THEOREM:
// Perfect matching exists iff:
// For every subset S ⊆ L, |neighbors(S)| ≥ |S|
// i.e., every k left vertices collectively connect to ≥ k right vertices
//
// TIME COMPLEXITY:
// Using max flow: O(VE²) with Edmonds-Karp
// Specialized algorithms (Hopcroft-Karp): O(E√V) - faster!
//
// SPACE COMPLEXITY: O(V+E)
//
// USE CASES:
// - Job assignment (workers to tasks)
// - Stable marriage problem
// - Course scheduling (students to courses)
// - Organ donor matching
// - Network switching (input ports to output ports)
// - Resource allocation in systems
void bipartiteMatchingExample() {
    cout << "\n=== BIPARTITE MATCHING EXAMPLE ===" << endl;
    
    // Bipartite graph: Left set = {0, 1, 2}, Right set = {3, 4, 5}
    // Convert to max flow problem
    // Add source connected to left set, sink connected to right set
    
    int leftSize = 3, rightSize = 3;
    int n = 2 + leftSize + rightSize; // source + left + right + sink
    
    MaxFlow flow(n);
    int source = 0;
    int sink = n - 1;
    
    // Connect source to left set (nodes 1, 2, 3)
    for (int i = 1; i <= leftSize; i++) {
        flow.addEdge(source, i, 1);
    }
    
    // Connect right set (nodes 4, 5, 6) to sink
    for (int i = 0; i < rightSize; i++) {
        flow.addEdge(leftSize + 1 + i, sink, 1);
    }
    
    // Add edges in bipartite graph
    flow.addEdge(1, 4, 1); // Left node 0 to Right node 0
    flow.addEdge(1, 5, 1); // Left node 0 to Right node 1
    flow.addEdge(2, 4, 1); // Left node 1 to Right node 0
    flow.addEdge(2, 6, 1); // Left node 1 to Right node 2
    flow.addEdge(3, 5, 1); // Left node 2 to Right node 1
    
    int maxMatching = flow.fordFulkerson(source, sink);
    
    cout << "Bipartite graph:" << endl;
    cout << "Left set: {0, 1, 2}" << endl;
    cout << "Right set: {3, 4, 5}" << endl;
    cout << "Edges: 0-3, 0-4, 1-3, 1-5, 2-4" << endl;
    cout << "\nMaximum matching size: " << maxMatching << endl;
}

// ============================================
// MAIN FUNCTION
// ============================================
int main() {
    cout << "\n========================================" << endl;
    cout << "C++ DATA STRUCTURES EXAMPLES" << endl;
    cout << "========================================" << endl;
    
    arrayExample();
    vectorExample();
    listExample();
    forwardListExample();
    dequeExample();
    stackExample();
    queueExample();
    priorityQueueExample();
    setExample();
    multisetExample();
    unorderedSetExample();
    mapExample();
    multimapExample();
    unorderedMapExample();
    bitsetExample();
    pairTupleExample();
    stringExample();
    graphExample();
    adjacencyListExample();
    treeExample();
    bstExample();
    heapExample();
    networkFlowExample();
    circulationExample();
    minCutExample();
    bipartiteMatchingExample();
    
    cout << "\n========================================" << endl;
    cout << "ALL EXAMPLES COMPLETED!" << endl;
    cout << "========================================\n" << endl;
    
    return 0;
}
