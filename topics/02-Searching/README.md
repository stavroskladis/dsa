# Searching Algorithms

This directory contains implementations of various searching algorithms in C++. All algorithms are implemented as template functions to work with any comparable data type.

## Table of Contents

1. [Basic Search Algorithms](#basic-search-algorithms)
2. [Binary Search Variants](#binary-search-variants)
3. [Usage Examples](#usage-examples)
4. [Standard Library Equivalents](#standard-library-equivalents)
5. [Complexity Comparison](#complexity-comparison)
6. [Notes](#notes)
7. [General Recommendations](#general-recommendations)
   - [When to Use Linear Search](#when-to-use-linear-search-stdfind)
   - [When to Use Binary Search Variants](#when-to-use-binary-search-variants)
   - [Iterative vs Recursive Implementation](#iterative-vs-recursive-implementation)
   - [Performance Trade-off Example](#performance-trade-off-example)
   - [Understanding Amortized Complexity](#understanding-amortized-complexity)

---

## Basic Search Algorithms

### Linear Search

**Function:** `linear_search(const std::vector<T>& A, T target)`

**Description:**  
Searches for a target element by checking each element sequentially from the beginning of the array.

**Time Complexity:**
- Best Case: O(1) - Target found at first position
- Worst Case: O(n) - Target found at last position or not found
- Average Case: O(n)

**Space Complexity:** O(1)

**Requirements:** None (works on any array, unsorted or sorted)

**Returns:** Index of target if found, -1 otherwise

---

## Binary Search Variants

### Binary Search (Iterative)

**Function:** `binary_search(const std::vector<T>& A, T target)`

**Description:**  
Classic binary search algorithm that divides the search space in half at each step. Requires the array to be sorted.

**Time Complexity:**
- Best Case: O(1) - Target found at middle position
- Worst Case: O(log n)
- Average Case: O(log n)

**Space Complexity:** O(1)

**Requirements:** Array must be sorted in ascending order

**Returns:** Index of target if found, -1 otherwise

---

### Binary Search (Recursive)

**Function:** `binary_search_recursive(const std::vector<T>& A, T target, int low, int high)`

**Description:**  
Recursive implementation of binary search. Same algorithm as iterative version but uses recursion. Accepts custom search range via `low` and `high` parameters.

**Time Complexity:**
- Best Case: O(1)
- Worst Case: O(log n)
- Average Case: O(log n)

**Space Complexity:** O(log n) - Due to recursion call stack. This is why the iterative version is more space-efficient (O(1)).

**Requirements:** Array must be sorted in ascending order. `low` and `high` must be valid indices.

**Returns:** Index of target if found, -1 otherwise

**Note:** Invalid indices (out of bounds or `high < low`) will return -1.

---

**Function:** `binary_search_recursive(const std::vector<T>& A, T target)` (Wrapper)

**Description:**  
Wrapper function for recursive binary search with default search range (entire array). Safer alternative that automatically sets valid bounds.

**Time Complexity:**
- Best Case: O(1)
- Worst Case: O(log n)
- Average Case: O(log n)

**Space Complexity:** O(log n) - Due to recursion call stack

**Requirements:** Array must be sorted in ascending order

**Returns:** Index of target if found, -1 otherwise

---

### Lower Bound

**Function:** `lower_bound(const std::vector<T>& A, T target)`

**Description:**  
Finds the first position where `element >= target`. Returns the index of the first element that is not less than target. Useful for finding insertion points in sorted arrays.

**Time Complexity:** O(log n)

**Space Complexity:** O(1)

**Requirements:** Array must be sorted in ascending order

**Returns:** Index of first element >= target, or -1 if all elements are less than target

---

### Upper Bound

**Function:** `upper_bound(const std::vector<T>& A, T target)`

**Description:**  
Finds the first position where `element > target`. Returns the index of the first element that is greater than target. Useful for finding the end of a range of equal elements.

**Time Complexity:** O(log n)

**Space Complexity:** O(1)

**Requirements:** Array must be sorted in ascending order

**Returns:** Index of first element > target, or -1 if all elements are <= target

---

## Usage Examples

### Basic Usage

```cpp
#include "searching.hpp"
#include <vector>

int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    
    // Linear search (works on any array)
    int idx1 = searching::linear_search(arr, 7);  // Returns 3
    
    // Binary search (requires sorted array)
    int idx2 = searching::binary_search(arr, 7);   // Returns 3
    
    // Binary search recursive (wrapper - safer, uses default bounds)
    int idx2b = searching::binary_search_recursive(arr, 7);  // Returns 3
    
    // Binary search recursive (with custom bounds)
    int idx2c = searching::binary_search_recursive(arr, 7, 0, static_cast<int>(arr.size()) - 1);  // Returns 3
    
    // Lower bound
    int idx3 = searching::lower_bound(arr, 6);    // Returns 3 (first element >= 6)
    
    // Upper bound
    int idx4 = searching::upper_bound(arr, 6);     // Returns 3 (first element > 6)
    
    return 0;
}
```

## Standard Library Equivalents

The C++ standard library (`<algorithm>`) provides equivalent functions with different return types. Here's a comparison:

| Custom Function | Standard Library | Return Type |
|----------------|------------------|-------------|
| `searching::linear_search` | `std::find` | Index vs Iterator |
| `searching::binary_search` | `std::binary_search` | Index vs Bool |
| `searching::lower_bound` | `std::lower_bound` | Index vs Iterator |
| `searching::upper_bound` | `std::upper_bound` | Index vs Iterator |

### Key Differences:

1. **Return Types:**
   - **Custom functions:** Return `int` index (-1 if not found)
   - **Standard library:** Return iterators (or `bool` for `std::binary_search`)
   - **Note:** To convert iterators to indices, use `std::distance(begin, iterator)`

2. **Usage Example Comparison:**

```cpp
#include "searching.hpp"
#include <algorithm>
#include <vector>

std::vector<int> arr = {1, 3, 5, 7, 9};

// Custom function - direct index return
int idx = searching::linear_search(arr, 5);  // Returns 2

// Standard library - iterator return
auto it = std::find(arr.begin(), arr.end(), 5);
if (it != arr.end()) {
    int idx = std::distance(arr.begin(), it);  // Returns 2
}

// Custom function - direct index return
int idx = searching::binary_search(arr, 5);  // Returns 2

// Standard library - bool return (no index)
bool found = std::binary_search(arr.begin(), arr.end(), 5);  // Returns true
// To get index, need to use std::lower_bound:
auto it = std::lower_bound(arr.begin(), arr.end(), 5);
if (it != arr.end() && *it == 5) {
    int idx = std::distance(arr.begin(), it);  // Returns 2
}

// Alternative: Using iterator subtraction (shorthand method)
int idx = std::lower_bound(arr.begin(), arr.end(), 5) - arr.begin();  // Returns 2
```

### Converting Iterators to Indices

When using standard library functions that return iterators, if we need to convert them to indices, there are two common methods:

#### Method 1: Using `std::distance()` (Explicit)

```cpp
auto it = std::lower_bound(arr.begin(), arr.end(), target);
int index = std::distance(arr.begin(), it);
```

**How it works:** `std::distance()` calculates the number of elements between two iterators. It returns a `difference_type` (typically `ptrdiff_t`).

#### Method 2: Using Iterator Subtraction (Shorthand)

```cpp
int index = std::lower_bound(arr.begin(), arr.end(), target) - arr.begin();
```

**How it works:**
- When we subtract two iterators of the same type (e.g., `vector<int>::iterator`), C++ returns the **distance** between them as a signed integer type (`difference_type`).
- `arr.begin()` points to the first element (index 0).
- `std::lower_bound(...)` returns an iterator pointing to a specific position.
- The subtraction `iterator - arr.begin()` gives the number of elements between the start and that position, which equals the **index**.

**Why it works:**
- Random access iterators (like those for `std::vector`, `std::array`, `std::deque`) support arithmetic operations.
- Subtracting two iterators yields the number of elements between them.
- Since `arr.begin()` represents position 0, subtracting it from any iterator gives the index.

**Example:**
```cpp
std::vector<int> arr = {1, 3, 5, 7, 9};
// arr.begin() points to element at index 0 (value 1)
// std::lower_bound(arr.begin(), arr.end(), 5) points to element at index 2 (value 5)
// So: iterator_at_index_2 - iterator_at_index_0 = 2 (the index)
int idx = std::lower_bound(arr.begin(), arr.end(), 5) - arr.begin();  // idx = 2
```

**Which method to use?**

- **For `std::vector`/`std::array`/`std::deque`:** Iterator subtraction (`it - begin()`) is the idiomatic approach in production code - it's concise and shows you're working with random access iterators.
- **For generic/template code:** Use `std::distance()` when your code must work with different iterator types (forward, bidirectional, etc.). It works with all iterator categories but may be O(n) for non-random-access iterators.

**Note:** For production code, prefer the standard library search functions (`std::find`, `std::binary_search`, `std::lower_bound`, `std::upper_bound`). While performance is comparable, the standard library functions are battle-tested, standardized, and work seamlessly with all STL containers and algorithms. The custom implementations in this repository are for educational purposes only.

---

## Complexity Comparison

Complete complexity analysis for all implemented search algorithms:

| Algorithm | Best Case | Average Case | Worst Case | Space Complexity |
|-----------|-----------|--------------|------------|------------------|
| `linear_search / std::find` | O(1) | O(n) | O(n) | O(1) |
| `binary_search` | O(1) | O(log n) | O(log n) | O(1) |
| `binary_search_recursive` (3-param) | O(1) | O(log n) | O(log n) | O(log n) |
| `binary_search_recursive` (wrapper) | O(1) | O(log n) | O(log n) | O(log n) |
| `lower_bound` | O(log n) | O(log n) | O(log n) | O(1) |
| `upper_bound` | O(log n) | O(log n) | O(log n) | O(1) |

### Notes on Complexity:

1. **Best Case Scenarios:**
   - `linear_search`: Target found at the first position
   - `binary_search`: Target found at the middle position (first comparison)
   - `lower_bound`/`upper_bound`: Always O(log n) - must verify first occurrence

2. **Worst Case Scenarios:**
   - `linear_search`: Target found at last position or not found
   - `binary_search`: Target not found or found at leaf of search tree
   - `lower_bound`/`upper_bound`: Must traverse full binary search tree

3. **Space Complexity:**
   - Iterative algorithms: O(1) - only use a few variables
   - Recursive algorithms: O(log n) - recursion call stack depth equals tree height

4. **Requirements:**
   - Binary search variants require sorted arrays
   - Linear search works on any array (sorted or unsorted)

---

## Notes

1. **Template Functions:** All search functions are templated to work with any comparable data type (int, float, string, etc.).

2. **Return Values:** All functions return -1 when the target is not found or when invalid bounds are provided.

3. **Sorted Arrays:** Most efficient algorithms (binary search variants) require sorted arrays. Use `std::sort()` if needed.

4. **Edge Cases:** All functions handle empty arrays and edge cases appropriately.

5. **Name Conflicts:** `lower_bound` and `upper_bound` share names with STL functions. Always use explicit namespace qualification (`searching::` or `std::`) to distinguish between them. Avoid `using namespace std;` and `using namespace searching;` to prevent ambiguity.

6. **Overflow Protection:** Binary search functions use `low + (high - low) / 2` instead of `(low + high) / 2` to prevent integer overflow when calculating the midpoint.

---

## General Recommendations

### When to Use Linear Search (`std::find`)

Use linear search when:
- **Data is unsorted** and cannot or should not be sorted
- **Small datasets** (n < 100) where the overhead of sorting outweighs the benefit
- **Single searches** where the cost of sorting (O(n log n)) exceeds the search cost (O(n))
- **Frequently changing data** where maintaining sorted order is impractical

### When to Use Binary Search Variants

Use binary search when:
- **Data is already sorted** - binary search always wins! O(log n) vs O(n) with no sorting overhead
- **Data can be sorted once for multiple searches** - the one-time sorting cost O(n log n) is spread across k searches, making the average cost per search approach O(log n) as k increases (see amortized analysis below)
- **Large datasets** (n > 1000) - logarithmic complexity provides significant speedup
- **Multiple searches** on the same dataset - sort once, search many times efficiently

### Choosing the Right Binary Search Variant

- **`std::binary_search`:** When you only need to check if an element exists (yes/no)
- **`std::lower_bound`:** When you need the first position where element ≥ target (insertion point for sorted order)
- **`std::upper_bound`:** When you need the first position where element > target (end of range for duplicates)

### Iterative vs Recursive Implementation

**Prefer iterative implementations** for production code:
- **Space complexity:** O(1) vs O(log n) for recursive versions
- **No stack overhead:** Recursive calls create a call stack with depth equal to tree height (log n)
- **Performance:** Iterative versions are slightly faster due to no function call overhead
- **Stack safety:** Deep recursion can cause stack overflow in constrained environments

**When recursive might be acceptable:**
- Educational purposes to understand the algorithm
- Code readability in contexts where space is not constrained
- Very small datasets where the overhead is negligible

**Note:** The standard library functions (`std::binary_search`, `std::lower_bound`, `std::upper_bound`) use iterative implementations for optimal performance and space efficiency.

### Performance Trade-off Example

**Important: If data is already sorted, binary search always wins!**

When data is pre-sorted:
- Linear search: **O(n)**
- Binary search: **O(log n)**
- Since **O(log n) < O(n)**, binary search is always faster (no sorting cost!)
- Example: For n=1,000,000, binary ≈ 20 operations vs linear ≈ 1,000,000 operations

The analysis below applies only to **unsorted data** where sorting is required:

---

**For a single search on unsorted data:**

```cpp
// Linear search: O(n) - just search through the data
int idx = searching::linear_search(unsorted_data, target);

// Binary search: O(n log n) + O(log n) ≈ O(n log n) - must sort first!
std::sort(data.begin(), data.end());  // O(n log n)
int idx = searching::binary_search(data, target);  // O(log n)
```

**Why linear search wins for single searches:**
- Linear search cost: **O(n)**
- Binary search cost: **O(n log n)** (sorting dominates)
- Since **n log n > n** for any reasonable n, linear search is faster!
- Example: For n=1000, linear ≈ 1000 operations, binary ≈ 10,000 operations

**For k searches on the same dataset:**

```cpp
// Linear search: k * O(n) = O(k*n)
for (int i = 0; i < k; ++i) {
    int idx = searching::linear_search(data, targets[i]);  // O(n) each time
}

// Binary search: sort once, then k fast searches
std::sort(data.begin(), data.end());  // O(n log n) - one-time cost
for (int i = 0; i < k; ++i) {
    int idx = searching::binary_search(data, targets[i]);  // O(log n) each time
}
// Total: O(n log n + k log n)
```

**When does binary search become worth it?**

Binary search wins for k such that: **O(n log n + k log n) < O(k * n)**

Simplifying:
```
n log n + k log n < k * n
n log n < k * n - k log n
n log n < k(n - log n)
```

For large n where n >> log n, this approximately becomes:
```
n log n < k * n
log n < k
```

**Therefore: Binary search wins when k > log n**

**Concrete example:**
- For n = 1,000,000 (1 million elements)
- log₂(1,000,000) ≈ 20
- **If you're doing more than ~20 searches, binary search wins!**
- Sort once (expensive), then 20+ fast searches beat 20+ slow linear searches

---

### Understanding Amortized Complexity

**Amortized complexity** is the average cost per operation over a sequence of operations, rather than the worst-case cost of a single operation.

**In the context of searching:**

When you sort once and then perform k searches:
- **Total cost:** O(n log n + k log n)
- **Average cost per search (amortized):** O(n log n + k log n) / k = O(n log n / k + log n)

As k increases:
- The sorting cost O(n log n) is "spread" across more searches
- The per-search cost approaches O(log n)
- For large k, the amortized cost ≈ O(log n)

**Example with numbers:**
- n = 1,000,000, sort cost = 20,000,000 operations
- For k = 20 searches: amortized cost = (20,000,000 + 20×20) / 20 ≈ 1,000,000 per search
- For k = 100 searches: amortized cost = (20,000,000 + 100×20) / 100 ≈ 200,000 per search
- For k = 10,000 searches: amortized cost = (20,000,000 + 10,000×20) / 10,000 ≈ 2,020 per search
- As k -> inf, amortized cost -> 20 per search (just the binary search cost!)

**Other common examples of amortized analysis:**
1. **Dynamic array (std::vector) push_back:**
   - Most pushes: O(1)
   - Occasional resize: O(n)
   - Amortized: O(1) per push
   
2. **Hash table insertions:**
   - Most insertions: O(1)
   - Occasional rehashing: O(n)
   - Amortized: O(1) per insertion

**Key insight:** Amortized analysis shows that expensive operations are acceptable if they happen rarely enough that the average cost remains low.
