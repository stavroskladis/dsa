# Searching Algorithms

This directory contains implementations of various searching algorithms in C++. All algorithms are implemented as template functions to work with any comparable data type.

## Table of Contents

1. [Basic Search Algorithms](#basic-search-algorithms)
2. [Binary Search Variants](#binary-search-variants)
3. [Standard Library Equivalents](#standard-library-equivalents)
4. [Usage Examples](#usage-examples)
5. [Complexity Comparison](#complexity-comparison)
6. [Notes](#notes)

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

**Requirements:** None (works on any array)

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

**Space Complexity:** O(log n) - Due to recursion call stack

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

**Note:** This function shares the name with `std::lower_bound`. Use namespace qualification if you need the standard library version.

---

### Upper Bound

**Function:** `upper_bound(const std::vector<T>& A, T target)`

**Description:**  
Finds the first position where `element > target`. Returns the index of the first element that is greater than target. Useful for finding the end of a range of equal elements.

**Time Complexity:** O(log n)

**Space Complexity:** O(1)

**Requirements:** Array must be sorted in ascending order

**Returns:** Index of first element > target, or -1 if all elements are <= target

**Note:** This function shares the name with `std::upper_bound`. Use namespace qualification if you need the standard library version.

---

## Usage Examples

### Basic Usage

```cpp
#include "searching.hpp"
#include <vector>

int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    
    // Linear search (works on any array)
    int idx1 = linear_search(arr, 7);  // Returns 3
    
    // Binary search (requires sorted array)
    int idx2 = binary_search(arr, 7);   // Returns 3
    
    // Binary search recursive (wrapper - safer, uses default bounds)
    int idx2b = binary_search_recursive(arr, 7);  // Returns 3
    
    // Binary search recursive (with custom bounds)
    int idx2c = binary_search_recursive(arr, 7, 0, static_cast<int>(arr.size()) - 1);  // Returns 3
    
    // Lower bound
    int idx3 = lower_bound(arr, 6);    // Returns 3 (first element >= 6)
    
    // Upper bound
    int idx4 = upper_bound(arr, 6);     // Returns 3 (first element > 6)
    
    return 0;
}
```

## Standard Library Equivalents

The C++ standard library (`<algorithm>`) provides equivalent functions with different return types. Here's a comparison:

| Custom Function | Standard Library | Return Type | Notes |
|----------------|------------------|-------------|-------|
| `linear_search` | `std::find` | Index vs Iterator | `std::find` returns an iterator |
| `binary_search` | `std::binary_search` | Index vs Bool | `std::binary_search` returns `bool` (found/not found), not the index |
| `lower_bound` | `std::lower_bound` | Index vs Iterator | `std::lower_bound` returns an iterator |
| `upper_bound` | `std::upper_bound` | Index vs Iterator | `std::upper_bound` returns an iterator |

### Key Differences:

1. **Return Types:**
   - **Custom functions:** Return `int` index (-1 if not found)
   - **Standard library:** Return iterators (or `bool` for `std::binary_search`)
   - **Note:** To convert iterators to indices, use `std::distance(begin, iterator)`

2. **Usage Example Comparison:**

```cpp
#include <algorithm>
#include <vector>

std::vector<int> arr = {1, 3, 5, 7, 9};

// Custom function - direct index return
int idx = linear_search(arr, 5);  // Returns 2

// Standard library - iterator return
auto it = std::find(arr.begin(), arr.end(), 5);
if (it != arr.end()) {
    int idx = std::distance(arr.begin(), it);  // Returns 2
}

// Custom function - direct index return
int idx = binary_search(arr, 5);  // Returns 2

// Standard library - bool return (no index)
bool found = std::binary_search(arr.begin(), arr.end(), 5);  // Returns true
// To get index, need to use std::lower_bound:
auto it = std::lower_bound(arr.begin(), arr.end(), 5);
if (it != arr.end() && *it == 5) {
    int idx = std::distance(arr.begin(), it);  // Returns 2
}
```

---

## Complexity Comparison

Complete complexity analysis for all implemented search algorithms:

| Algorithm | Best Case | Average Case | Worst Case | Space Complexity |
|-----------|-----------|--------------|------------|------------------|
| `linear_search` | O(1) | O(n) | O(n) | O(1) |
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

5. **Name Conflicts:** `lower_bound` and `upper_bound` share names with STL functions. Use namespace qualification if you need the standard library versions.

6. **Overflow Protection:** Binary search functions use `low + (high - low) / 2` instead of `(low + high) / 2` to prevent integer overflow when calculating the midpoint.
