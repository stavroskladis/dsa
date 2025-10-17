#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <concepts>
#include <iostream>
#include <vector>

/**
 * This concept ensures that the comparator comp can compare two
 * objects of type T and provides clear compile-time error messages.
 */
template <typename T, typename Compare>
concept Comparable = requires(T a, T b, Compare comp) {
    { comp(a, b) } -> std::convertible_to<bool>;
};

/**
 * Bubble Sort Algorithm (ascending sorting) - O(n^2) time
 * complexity Repeatedly steps through the list, compares
 * adjacent elements and swaps them if they are in the wrong
 * order. The process is repeated until no swaps are needed.
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
void bubble_sort(std::vector<T>& A, Compare comp) {
    size_t n = A.size();
    // Avoid underflow (n - 1 underflows to SIZE_MAX) or
    // negative numbers in case of int type
    if (n <= 1) {
        return;
    }

    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;

        // Subtract i to avoid the comparison of sorted elements
        for (size_t j = 0; j < n - 1 - i; ++j) {
            if (comp(A[j + 1], A[j])) {
                std::swap(A[j], A[j + 1]);
                swapped = true;
            }
        }

        // Check if the array is already sorted
        if (!swapped) {
            break;
        }
    }
}

/**
 * Bubble Sort Algorithm (default ascending) - O(n^2) time
 * complexity Uses std::less<T> comparator for ascending sort by
 * default
 */
template <typename T>
void bubble_sort(std::vector<T>& A) {
    bubble_sort(A, std::less<T>());
}

/**
 * Selection Sort Algorithm - O(n^2) time complexity
 * Finds the minimum element in the unsorted portion and swaps
 * it with the first element of the unsorted portion.
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
void selection_sort(std::vector<T>& A, Compare comp) {
    size_t n = A.size();
    if (n <= 1) {
        return;
    }

    for (size_t i = 0; i < n - 1; ++i) {
        // Assume the first unsorted element is the minimum
        size_t idx = i;

        // Find minimum element in remaining unsorted array
        for (size_t j = i + 1; j < n; ++j) {

            // For ascending order, use std::less<T>
            // For descending order, use std::greater<T>
            if (comp(A[j], A[idx])) {
                idx = j;
            }
        }

        // Swap the smallest element with
        // the first element of the unsorted part
        if (idx != i) {
            std::swap(A[i], A[idx]);
        }
    }
}

/**
 * Selection Sort Algorithm (default ascending) - O(n^2) time
 * complexity Uses std::less<T> comparator for ascending sort by
 * default
 */
template <typename T>
void selection_sort(std::vector<T>& A) {
    selection_sort(A, std::less<T>());
}

/**
 * Insertion Sort Algorithm - O(n^2) time complexity
 * Builds the final sorted array one item at a time by taking
 * elements from the unsorted portion and inserting them into
 * their correct position.
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
void insertion_sort(std::vector<T>& A, Compare comp) {
    // Usage of size_t for index j, would result in underflow
    int n = static_cast<int>(A.size());

    // Assume the first element is sorted
    for (int i = 1; i < n; ++i) {
        // Set the key as the first element of the unsorted portion
        T key = A[i];
        int j = i - 1;

        while (j >= 0 && comp(key, A[j])) {
            // Shift element rightward
            A[j + 1] = A[j];
            --j;
        }

        A[j + 1] = key; // Insert the key at correct position
    }
}

template <typename T>
void insertion_sort(std::vector<T>& A) {
    insertion_sort(A, std::less<T>());
}

/**
 * Merge function for Merge Sort - O(n) time complexity
 * Merges two sorted subarrays into a single sorted array.
 * @param A Array to merge
 * @param left Start index of first subarray
 * @param m End index of first subarray (middle)
 * @param right End index of second subarray
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
void merge(std::vector<T>& A, int left, int m, int right,
           Compare comp) {
    int n1 = m - left + 1; // Size of left subarray
    int n2 = right - m;    // Size of right subarray

    std::vector<T> L(n1), R(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i) {
        L[i] = A[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        R[j] = A[m + 1 + j];
    }

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into A[left..right]
    while (i < n1 && j < n2) {
        // !(R[j] < L[i]) => R[j] >= L[i] => L[i] <= R[j]
        if (!comp(R[j], L[i])) {
            A[k++] = L[i++];
        }
        else {
            A[k++] = R[j++];
        }
    }

    // Copy remaining elements of L[] if any
    // j >= n2 (R is exhausted) -> Only L has remaining elements
    while (i < n1) {
        A[k++] = L[i++];
    }

    // Copy remaining elements of R[] if any
    // i >= n1 (L is exhausted) -> Only R has remaining elements
    while (j < n2) {
        A[k++] = R[j++];
    }
}

template <typename T>
void merge(std::vector<T>& A, int left, int m, int right) {
    merge(A, left, m, right, std::less<T>());
}

/**
 * Merge Sort Algorithm - O(n log n) time complexity
 * Divides the array into two halves, recursively sorts them,
 * and then merges the two sorted halves.
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
void merge_sort(std::vector<T>& A, int left, int right,
                Compare comp) {
    // Base case: array has 0 or 1 element
    if (left >= right) {
        return;
    }

    // Calculate middle position (truncation toward zero)
    int m = left + (right - left) / 2;

    // Recursively divide the left half of the vector.
    merge_sort(A, left, m, comp);

    // Recursively divide the right half of the vector.
    merge_sort(A, m + 1, right, comp);

    // Merge the two sorted halves (Conquer and Combine)
    merge(A, left, m, right, comp);
}

template <typename T>
void merge_sort(std::vector<T>& A, int left, int right) {
    merge_sort(A, left, right, std::less<T>());
}

/**
 * Partition function for Quick Sort - O(n) time complexity
 * For demonstration purposes we implement the Lomuto partition scheme
 * We don't use a comparator here for simplicity.
 */
template <typename T>
int lomuto_partition(std::vector<T>& A, int low, int high) {
    T pivot = A[high]; // Choose last element as pivot
    int i = low - 1;   // Index of smaller element

    for (int j = low; j < high; ++j) {
        if (A[j] <= pivot) {
            ++i;
            std::swap(A[i], A[j]);
        }
    }

    std::swap(A[i + 1], A[high]);
    return i + 1;
}

/**
 * Partitions the array around a pivot element and returns the
 * pivot's final position.
 * Implements the Pure Hoare partition scheme, which is more
 * efficient (fewer swaps, better with duplicates, better cache
 * performance, balanced partitions).
 * We prefer middle element O(nlogn) instead of low O(n^2)
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
int partition(std::vector<T>& A, int low, int high, Compare comp) {
    int mid = low + (high - low) / 2;
    T pivot = A[mid];
    int i = low - 1;  // start left pointer before the first element
    int j = high + 1; // start right pointer after the last element

    while (true) {

        // find next element larger than pivot from the left
        do {
            ++i;
        } while (comp(A[i], pivot));

        // find next element smaller than pivot from the right
        do {
            --j;
        } while (comp(pivot, A[j]));

        // Check if the two pointers meet or cross each other
        if (i >= j) {
            return j;
        }

        // if a smaller element exists after the larger element swap
        std::swap(A[i], A[j]);
    }
}

/**
 * Quick Sort Algorithm - O(n log n) average, O(n^2) worst case
 * Picks a pivot element and partitions the array around the
 * pivot, then recursively sorts the sub-arrays.
 */
template <typename T, typename Compare>
    requires Comparable<T, Compare>
void quick_sort(std::vector<T>& A, int low, int high, Compare comp) {
    if (low >= high) {
        return;
    }

    int pivot_index = partition(A, low, high, comp);
    quick_sort(A, low, pivot_index, comp);      // Sort left subarray
    quick_sort(A, pivot_index + 1, high, comp); // Sort right subarray
}

template <typename T>
void quick_sort(std::vector<T>& A, int low, int high) {
    quick_sort(A, low, high, std::less<T>());
}

/**
 * For simplicity we do not support negative numbers
 * To support negative numbers we can use a shifting range.
 * Time Complexity	O(n + k)
 * Space Complexity O(n + k)
 */
template <typename Compare>
    requires Comparable<int, Compare>
void count_sort(std::vector<int>& A, Compare /* comp */) {
    if (A.empty() || A.size() == 1) {
        return;
    }

    // Find the maximum element to determine the range
    int max_num = *max_element(A.begin(), A.end());

    // Create count array of size max_num + 1, initialized to 0
    std::vector<int> counting_vector(max_num + 1, 0);

    // Count each numbers occurence in the input vector
    for (int num : A) {
        ++counting_vector[num];
    }

    A.clear(); // capacity remains the same (no dynamic allocation)

    if constexpr (std::is_same_v<Compare, std::less<int>>) {
        for (int i = 0; i <= max_num; ++i) {
            for (int j = 0; j < counting_vector[i]; ++j) {
                A.push_back(i);
            }
        }
    }
    else if constexpr (std::is_same_v<Compare, std::greater<int>>) {
        for (int i = max_num; i >= 0; --i) {
            for (int j = 0; j < counting_vector[i]; ++j) {
                A.push_back(i);
            }
        }
    }
    else {
        std::cout << "Invalid comparison operator" << std::endl;
        return;
    }
}

inline void count_sort(std::vector<int>& A) {
    count_sort(A, std::less<int>());
}

#endif