#ifndef SEARCHING_H
#define SEARCHING_H

#include <vector>

/**
 * Linear searching on a vector.
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(n)
 *  - Average Time Complexity O(n)
 *  - Space Complexity O(1)
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
 * Binary searching on a vector.
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(log n)
 *  - Average Time Complexity O(log n)
 *  - Space Complexity O(1)
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
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(log n)
 *  - Average Time Complexity O(log n)
 *  - Space Complexity O(log n) due to recursion call stack
 */
template <typename T>
int binary_search_recursive(const std::vector<T>& A, T target,
                            int low, int high) {
    if (A.empty() || high < low) {
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

#endif