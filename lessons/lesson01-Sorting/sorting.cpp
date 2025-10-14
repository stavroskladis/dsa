#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void read_vector(vector<int>& A, int n);

template <typename T>
void print_vector(const vector<T>& A);

template <typename T, typename Compare>
void bubble_sort(vector<T>& A, Compare comp);

template <typename T>
void bubble_sort(vector<T>& A);

template <typename T, typename Compare>
void selection_sort(vector<T>& A, Compare comp);

template <typename T>
void selection_sort(vector<T>& A);

template <typename T, typename Compare>
void insertion_sort(vector<T>& A, Compare comp);

template <typename T>
void insertion_sort(vector<T>& A);

template <typename T, typename Compare>
void merge(vector<T>& A, int l, int m, int r, Compare);

template <typename T>
void merge(vector<T>& A, int l, int m, int r);

template <typename T>
void merge_sort(vector<T>& A, int l, int r);

template <typename T>
void quick_sort(vector<T>& A, int low, int high);

template <typename T>
int partition(vector<T>& A, int low, int high);

/* std::sort: O(n log n) - highly optimized, uses introsort */

int main() {
    // Initialize random seed for generating random numbers
    srand(static_cast<unsigned>(time(nullptr)));

    const int n = 5;
    vector<int> arr;

    read_vector(arr, n);

    cout << "Initial array" << endl;
    print_vector<int>(arr);

    auto v1 = arr;
    bubble_sort(v1);
    cout << endl << "Sorted by Bubble Sort (ascending)" << endl;
    print_vector<int>(v1);

    auto v2 = arr;
    insertion_sort(v2);
    cout << endl << "Sorted by Insertion Sort (ascending)" << endl;
    print_vector<int>(v2);

    auto v3 = arr;
    selection_sort(v3);
    cout << endl << "Sorted by Selection Sort (ascending)" << endl;
    print_vector<int>(v3);

    auto v4 = arr;
    // merge_sort arguments: vector v4, start index, end index
    merge_sort(v4, 0, static_cast<int>(v4.size()) - 1);

    cout << endl << "Sorted by Merge Sort (ascending)" << endl;
    print_vector<int>(v4);

    // auto v5 = arr; // TODO: restore
    vector<int> v5{7, 2, 1, 6, 4, 5}; // TODO: delete
    quick_sort(v5, 0, static_cast<int>(v5.size()) - 1);
    cout << endl << "Sorted by Quick Sort (ascending)" << endl;
    print_vector<int>(v5);

    auto v6 = arr;
    // std::less<T> is the default comparator (ascending order)
    sort(v6.begin(), v6.end());
    cout << endl << "Sorted by std::sort (ascending)" << endl;
    print_vector<int>(v6);

    return 0;
}

/**
 * Reads n random integers into vector A
 * @param A Reference to vector (modifies the original)
 * @param n Number of elements to read
 */
void read_vector(vector<int>& A, int n) {
    A.resize(n); // Resize vector to exactly n elements

    for (int i = 0; i < n; ++i) {
        // Generate random numbers from 1 to 10
        A[i] = rand() % 10 + 1;
    }
}

/**
 * Prints vector elements separated by tabs
 * @param A Const reference to vector (guarantees no
 * modification)
 */
template <typename T>
void print_vector(const vector<T>& A) {
    for (const auto& elem : A) {
        cout << elem << "\t";
    }
    cout << endl;
}

/**
 * Bubble Sort Algorithm (ascending sorting) - O(n^2) time
 * complexity Repeatedly steps through the list, compares
 * adjacent elements and swaps them if they are in the wrong
 * order. The process is repeated until no swaps are needed.
 */
template <typename T, typename Compare>
void bubble_sort(vector<T>& A, Compare comp) {
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
                swap(A[j], A[j + 1]);
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
void bubble_sort(vector<T>& A) {
    bubble_sort(A, std::less<T>());
}

/**
 * Selection Sort Algorithm - O(n^2) time complexity
 * Finds the minimum element in the unsorted portion and swaps
 * it with the first element of the unsorted portion.
 */
template <typename T, typename Compare>
void selection_sort(vector<T>& A, Compare comp) {
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
            swap(A[i], A[idx]);
        }
    }
}

/**
 * Selection Sort Algorithm (default ascending) - O(n^2) time
 * complexity Uses std::less<T> comparator for ascending sort by
 * default
 */
template <typename T>
void selection_sort(vector<T>& A) {
    selection_sort(A, std::less<T>());
}

/**
 * Insertion Sort Algorithm - O(n^2) time complexity
 * Builds the final sorted array one item at a time by taking
 * elements from the unsorted portion and inserting them into
 * their correct position.
 */
template <typename T, typename Compare>
void insertion_sort(vector<T>& A, Compare comp) {
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
void insertion_sort(vector<T>& A) {
    insertion_sort(A, std::less<T>());
}

/**
 * Merge Sort Algorithm - O(n log n) time complexity
 * Divides the array into two halves, recursively sorts them,
 * and then merges the two sorted halves.
 */
template <typename T>
void merge_sort(vector<T>& A, int left, int right) {
    // Base case: array has 0 or 1 element
    if (left >= right) {
        return;
    }

    // Calculate middle position (truncation toward zero)
    int m = left + (right - left) / 2;

    // Recursively divide the left half of the vector.
    merge_sort(A, left, m);

    // Recursively divide the right half of the vector.
    merge_sort(A, m + 1, right);

    // Merge the two sorted halves (Conquer and Combine)
    merge(A, left, m, right);
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
void merge(vector<T>& A, int left, int m, int right, Compare comp) {
    int n1 = m - left + 1; // Size of left subarray
    int n2 = right - m;    // Size of right subarray

    vector<T> L(n1), R(n2);

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
void merge(vector<T>& A, int left, int m, int right) {
    merge(A, left, m, right, std::less<T>());
}

/**
 * Quick Sort Algorithm - O(n log n) average, O(n^2) worst case
 * Picks a pivot element and partitions the array around the
 * pivot, then recursively sorts the sub-arrays.
 */
template <typename T>
void quick_sort(vector<T>& A, int low, int high) {
    if (low < high) {
        int pivot_index = partition(A, low, high);
        quick_sort(A, low, pivot_index - 1);  // Sort left subarray
        quick_sort(A, pivot_index + 1, high); // Sort right subarray
    }
}

/**
 * Partition function for Quick Sort - O(n) time complexity
 * Partitions the array around a pivot element and returns the
 * pivot's final position.
 * For demonstration purposes we will use the Lomuto partition scheme
 * instead of the Hoare partition scheme, which is more efficient.
 */
template <typename T>
int partition(vector<T>& A, int low, int high) {
    T pivot = A[high]; // Choose last element as pivot
    int i = low - 1;   // Index of smaller element

    for (int j = low; j < high; ++j) {
        if (A[j] <= pivot) {
            ++i;
            swap(A[i], A[j]);
        }
    }

    swap(A[i + 1], A[high]);
    return i + 1;
}
