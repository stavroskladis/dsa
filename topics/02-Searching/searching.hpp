#ifndef SEARCHING_HPP
#define SEARCHING_HPP

#include <vector>

namespace searching {

/**
 * Basic Search Algorithms
 */

/**
 * Linear searching on a vector.
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(n)
 *  - Average Time Complexity O(n)
 *  - Space Complexity O(1)
 *  - Returns: Index of target if found, -1 otherwise
 *  - Note: Works on both sorted and unsorted vectors
 */
template <typename T>
int linear_search(const std::vector<T>& A, T target) {

    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] == target) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

/**
 * Binary Search and Binary Search Variants
 */

/**
 * Binary searching on a vector.
 *  - Precondition: The vector must be sorted in ascending order
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(log n)
 *  - Average Time Complexity O(log n)
 *  - Space Complexity O(1)
 *  - Returns: Index of target if found, -1 otherwise
 */
template <typename T>
int binary_search(const std::vector<T>& A, T target) {
    if (A.empty()) {
        return -1;
    }

    int low = 0;
    int high = static_cast<int>(A.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (target == A[mid]) {
            return mid; // The target was found at index mid.
        }
        else if (target < A[mid]) {
            high = mid - 1; // Continue searching in the left half.
        }
        else {
            low = mid + 1; // Continue searching in the right half.
        }
    }

    return -1; // The target was not found in the array.
}

/**
 * Binary searching on a vector using recursion.
 *  - Precondition: The vector must be sorted in ascending order
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(log n)
 *  - Average Time Complexity O(log n)
 *  - Space Complexity O(log n) due to recursion call stack
 *  - Returns: Index of target if found, -1 otherwise
 *  - Note: Not found or invalid indices will return -1.
 */
template <typename T>
int binary_search_recursive(const std::vector<T>& A, T target, int low, int high) {
    int max_index = static_cast<int>(A.size()) - 1;
    if (A.empty() || high < low || low < 0 || high > max_index) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (target == A[mid]) {
        return mid; // The target was found at index mid.
    }
    else if (target < A[mid]) {
        // Continue searching in the left half.
        return binary_search_recursive(A, target, low, mid - 1);
    }
    else {
        // Continue searching in the right half.
        return binary_search_recursive(A, target, mid + 1, high);
    }
}

/**
 * Wrapper function for binary search recursive with default search range.
 *  - Precondition: The vector must be sorted in ascending order
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(log n)
 *  - Average Time Complexity O(log n)
 *  - Space Complexity O(log n) due to recursion call stack
 *  - Returns: Index of target if found, -1 otherwise
 *  - Note: Safer alternative to binary_search with default search range.
 */
template <typename T>
int binary_search_recursive(const std::vector<T>& A, T target) {
    if (A.empty()) {
        return -1;
    }
    return binary_search_recursive(A, target, 0, static_cast<int>(A.size()) - 1);
}

/**
 * Lower bound search - finds the first position where element >= target.
 *  - Precondition: The vector must be sorted in ascending order
 *  - Time Complexity O(log n)
 *  - Space Complexity O(1)
 *  - Returns: Index of first element >= target, or -1 if all elements < target
 */
template <typename T>
int lower_bound(const std::vector<T>& A, T target) {
    if (A.empty()) {
        return -1;
    }

    int low = 0;
    int high = static_cast<int>(A.size()) - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (A[mid] >= target) {
            result = mid;   // Found a candidate index.
            high = mid - 1; // Continue searching in the left half.
        }
        else {
            low = mid + 1; // Continue searching in the right half.
        }
    }

    return result; // Returns -1 if all elements are less than target
}

/**
 * Upper bound search - finds the first position where element > target.
 *  - Precondition: The vector must be sorted in ascending order
 *  - Time Complexity O(log n)
 *  - Space Complexity O(1)
 *  - Returns: Index of first element > target, or -1 if all elements <= target
 */
template <typename T>
int upper_bound(const std::vector<T>& A, T target) {
    if (A.empty()) {
        return -1;
    }

    int low = 0;
    int high = static_cast<int>(A.size()) - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (A[mid] > target) {
            result = mid;   // Found a candidate index
            high = mid - 1; // Continue searching in the left half.
        }
        else {
            low = mid + 1; // Continue searching in the right half.
        }
    }

    return result; // Returns -1 if all elements are <= target
}

} // namespace searching

#endif
