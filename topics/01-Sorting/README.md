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
- **Count Sort** - Linear time for integers within a known range, only works with `std::less<int>` and `std::greater<int>`

## Algorithm Comparison

| Algorithm      | Time (Best) | Time (Avg)  | Time (Worst) | Space    | Stable |
|----------------|-------------|-------------|--------------|----------|--------|
| Bubble Sort    | O(n)        | O(n²)       | O(n²)        | O(1)     | Yes    |
| Selection Sort | O(n²)       | O(n²)       | O(n²)        | O(1)     | No     |
| Insertion Sort | O(n)        | O(n²)       | O(n²)        | O(1)     | Yes    |
| Merge Sort     | O(n log n)  | O(n log n)  | O(n log n)   | O(n)     | Yes    |
| Quick Sort     | O(n log n)  | O(n log n)  | O(n²)        | O(log n) | No     |
| Count Sort     | O(n+k)*     | O(n+k)*     | O(n+k)*      | O(k)*    | Yes    |

*k = range of input values (max - min + 1)

## Usage

```cpp
#include <vector>
#include <functional>

// Note: Each algorithm modifies the vector in-place. In practice, you'd need
// to create a fresh copy of the data before each sort (omitted here).
std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

// Ascending order (default mode so we can ommit: std::less<int>())
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

**Bubble Sort**: Educational purposes only, avoid in production

**Selection Sort**: When memory writes are expensive (minimizes swaps)

**Insertion Sort**: Small arrays (n < 10-20) or nearly sorted data

**Merge Sort**: When stability is required or working with linked lists

**Quick Sort**: General purpose sorting, excellent average performance

**Count Sort**: Integers with small range, need linear time performance

## Requirements

C++17 or later compiler

## Notes

- Count Sort only supports `std::less<int>` and `std::greater<int>` comparators due to its counting-based nature
- All comparison-based sorts support any custom comparator
- Quick Sort uses Hoare partition scheme with middle element as pivot for better performance on sorted/reverse-sorted inputs
