#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// Function declarations with time complexity annotations
void read_vector(vector<int>& A, int n);

template <typename T>
void print_vector(const vector<T>& A);

template <typename T, typename Compare>
void bubble_sort(vector<T>& A, Compare comp); // O(n^2)

template <typename T>
void bubble_sort(vector<T>& A);

template <typename T>
void selection_sort(vector<T>& A); // O(n^2)

void insertion_sort(vector<int>& A);             // O(n^2)
void merge(vector<int>& A, int l, int m, int r); // O(n)
void merge_sort(vector<int>& A, int l, int r);   // O(n log n)
void quick_sort(vector<int>& A, int low,
                int high); // O(n log n) average, O(n^2) worst
int partition(vector<int>& A, int low, int high); // O(n)

/* std::sort: O(n log n) - highly optimized, uses introsort */

int main() {
    // Initialize random seed for generating random numbers
    srand(static_cast<unsigned>(time(nullptr)));

    const int n = 5;
    vector<int> arr; // Vector starts with size 0

    read_vector(arr, n);

    cout << "Initial array" << endl;
    print_vector<int>(arr);

    // Create copies so each algorithm works on the same
    // unsorted vector
    auto v1 = arr; // Changes to v1 don't affect arr

    bubble_sort(v1);
    cout << endl << "Sorted by Bubble Sort (ascending)" << endl;
    print_vector<int>(v1);

    auto v2 = arr;
    insertion_sort(v2);
    cout << endl
         << "Sorted by Insertion Sort (ascending)" << endl;
    print_vector<int>(v2);

    auto v3 = arr;
    selection_sort(v3);
    cout << endl
         << "Sorted by Selection Sort (ascending)" << endl;
    print_vector<int>(v3);

    auto v4 = arr;
    // merge_sort arguments: vector v4, start index, end index
    merge_sort(v4, 0, static_cast<int>(v4.size()) - 1);

    cout << endl << "Sorted by Merge Sort (ascending)" << endl;
    print_vector<int>(v4);

    auto v5 = arr;
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
        A[i] = rand() % 10 +
               1; // Generate random numbers from 1 to 10
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
template <typename T>
void selection_sort(vector<T>& A) {
    size_t n = A.size();
    if (n <= 1) {
        return;
    }

    for (size_t i = 0; i < n - 1; ++i) {
        // Assume the first unsorted element is the minimum
        size_t min_idx = i;

        // Find minimum element in remaining unsorted array
        for (size_t j = i + 1; j < n; ++j) {

            // Update if a smaller element is found
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the smallest element with
        // the first element of the unsorted part
        if (min_idx != i) {
            swap(A[i], A[min_idx]);
        }
    }
}

/**
 * Insertion Sort Algorithm - O(n^2) time complexity
 * Builds the final sorted array one item at a time by taking
 * elements from the unsorted portion and inserting them into
 * their correct position.
 */
void insertion_sort(vector<int>& A) {
    int n = static_cast<int>(A.size());

    for (int i = 1; i < n; ++i) { // Start from second element
        int key = A[i];           // Element to be inserted
        int j = i - 1;

        // Shift elements greater than key to the right
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = key; // Insert key at correct position
    }
}

/**
 * Merge Sort Algorithm - O(n log n) time complexity
 * Divides the array into two halves, recursively sorts them,
 * and then merges the two sorted halves.
 */
void merge_sort(vector<int>& A, int left, int right) {
    if (left >= right) {
        return; // Base case: array has 0 or 1 element
    }

    int m =
        left + (right - left) / 2; // Calculate middle position

    merge_sort(A, left, m);      // Recursively sort left half
    merge_sort(A, m + 1, right); // Recursively sort right half
    merge(A, left, m, right);    // Merge the two sorted halves
}

/**
 * Merge function for Merge Sort - O(n) time complexity
 * Merges two sorted subarrays into a single sorted array.
 * @param A Array to merge
 * @param left Start index of first subarray
 * @param m End index of first subarray (middle)
 * @param right End index of second subarray
 */
void merge(vector<int>& A, int left, int m, int right) {
    int n1 = m - left + 1; // Size of left subarray
    int n2 = right - m;    // Size of right subarray

    vector<int> L(n1), R(n2);

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
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        }
        else {
            A[k++] = R[j++];
        }
    }

    // Copy remaining elements of L[] if any
    while (i < n1) {
        A[k++] = L[i++];
    }

    // Copy remaining elements of R[] if any
    while (j < n2) {
        A[k++] = R[j++];
    }
}

/**
 * Quick Sort Algorithm - O(n log n) average, O(n^2) worst case
 * Picks a pivot element and partitions the array around the
 * pivot, then recursively sorts the sub-arrays.
 */
void quick_sort(vector<int>& A, int low, int high) {
    if (low < high) {
        int pivot_index = partition(A, low, high);
        quick_sort(A, low,
                   pivot_index - 1); // Sort left subarray
        quick_sort(A, pivot_index + 1,
                   high); // Sort right subarray
    }
}

/**
 * Partition function for Quick Sort - O(n) time complexity
 * Partitions the array around a pivot element and returns the
 * pivot's final position. Uses Lomuto partition scheme.
 */
int partition(vector<int>& A, int low, int high) {
    int pivot = A[high]; // Choose last element as pivot
    int i = low - 1;     // Index of smaller element

    for (int j = low; j < high; ++j) {
        if (A[j] <= pivot) {
            ++i;
            swap(A[i], A[j]);
        }
    }

    swap(A[i + 1], A[high]);
    return i + 1;
}
