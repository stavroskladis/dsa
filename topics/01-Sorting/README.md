# Sorting Algorithms

This directory contains implementations of fundamental sorting algorithms in C++. All algorithms are templated to work with any comparable type and support custom comparators.

## Implemented Algorithms

### Comparison-Based Sorts
- **Bubble Sort** - Simple but inefficient, useful for educational purposes
- **Selection Sort** - Minimizes number of swaps, unstable
- **Insertion Sort** - Efficient for small or nearly sorted arrays
- **Merge Sort** - Stable, guaranteed O(n log n), good for linked lists
- **Quick Sort** - Fast average case, uses Hoare partition with middle pivot

### Non-Comparison Sort
- **Counting Sort** - Linear time for integers within a known range, only works with `std::less<int>` and `std::greater<int>`

## Algorithm Comparison

| Algorithm      | Time (Best) | Time (Avg)  | Time (Worst) | Space    | Stable |
|----------------|-------------|-------------|--------------|----------|--------|
| Bubble Sort    | O(n)        | O(n²)       | O(n²)        | O(1)     | Yes    |
| Selection Sort | O(n²)       | O(n²)       | O(n²)        | O(1)     | No     |
| Insertion Sort | O(n)        | O(n²)       | O(n²)        | O(1)     | Yes    |
| Merge Sort     | O(n log n)  | O(n log n)  | O(n log n)   | O(n)     | Yes    |
| Quick Sort     | O(n log n)  | O(n log n)  | O(n²)        | O(log n) | No     |
| Counting Sort  | O(n+k)*     | O(n+k)*     | O(n+k)*      | O(k)*    | Yes    |

*k = range of input values (max - min + 1)

## Usage

```cpp
#include <vector>
#include <functional>

// Note: Each algorithm modifies the vector in-place. In practice, you'd need
// to create a fresh copy of the data before each sort (omitted here).
std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

// Ascending order (default mode so we can omit: std::less<int>())
bubble_sort(data, std::less<int>());
selection_sort(data, std::less<int>());
insertion_sort(data, std::less<int>());
merge_sort(data, 0, data.size() - 1, std::less<int>());
quick_sort(data, 0, data.size() - 1, std::less<int>());
count_sort(data, std::less<int>());

// Descending order
bubble_sort(data, std::greater<int>());
selection_sort(data, std::greater<int>());
insertion_sort(data, std::greater<int>());
merge_sort(data, 0, data.size() - 1, std::greater<int>());
quick_sort(data, 0, data.size() - 1, std::greater<int>());
count_sort(data, std::greater<int>());
```

## When to Use Each Algorithm

**Bubble Sort**: Educational purposes only (inefficient for production)

**Selection Sort**: When minimizing memory writes is critical (only n-1 swaps)

**Insertion Sort**: Small datasets (n < 20) or nearly sorted data

**Merge Sort**: Guaranteed O(n log n), stable sorting, linked lists, external data

**Quick Sort**: General purpose sorting, excellent average performance in large random datasets (prefer insertion sort for small datasets)

**Counting Sort**: Integer values within a small known range, need linear time

## Requirements

C++20 or later compiler (due to the usage of concepts)

## Relationship to STL Algorithms

### `std::sort` - Introsort (Hybrid Algorithm)
Modern `std::sort` uses **introsort** (introspective sort), which combines:
1. **Quicksort** - for general case (O(n log n) average)
2. **Heapsort** - if recursion depth gets too deep (prevents O(n²) worst case)
3. **Insertion sort** - for small subarrays (< 16 elements typically)

This hybrid approach is why `std::sort` is so fast in practice!

### `std::stable_sort` - Merge Sort
`std::stable_sort` primarily uses **merge sort**

**Implementation details:**
- **Primary algorithm**: Merge sort (O(n log n) with O(n) space)
- **Optimization**: Insertion sort for small chunks
- **Fallback**: In-place merge sort when memory limited (O(n log² n) with O(1) space)
- **Stability**: Guaranteed by always taking from left subarray when elements are equal

## Which one to prefer and why
**Why std::sort uses Introsort (unstable):**
Quick Sort and Heap Sort (the core of introsort) are inherently unstable - 
their partitioning and heap operations reorder equal elements. This is 
acceptable because std::sort doesn't guarantee stability, allowing it to 
prioritize speed and memory efficiency.

**Why std::stable_sort uses Merge Sort (stable):**
Merge Sort is naturally stable - its merge operation can be implemented to 
always take from the left subarray when elements are equal, preserving their 
original relative order. The trade-off is O(n) extra space and slightly 
slower performance.

## Building and Running

```bash
# Navigate to the sorting directory
cd topics/01-Sorting

# Compile
make

# Run
./sorting
```

## Notes

- Counting Sort only supports `std::less<int>` and `std::greater<int>` comparators due to its counting-based nature
- All comparison-based sorts support any custom comparator
- Quick Sort uses Hoare partition scheme with middle element as pivot for better performance on sorted/reverse-sorted inputs
- For production code, prefer `std::sort` (introsort) over pure Quick Sort for guaranteed O(n log n) worst case
