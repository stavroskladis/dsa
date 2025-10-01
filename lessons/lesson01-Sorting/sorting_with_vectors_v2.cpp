#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// Function declarations with time complexity annotations
void read_vector(vector<int>& A, int n);
void print_vector(const vector<int>& A);
void bubble_sort(vector<int>& A);                // O(n^2)
void insertion_sort(vector<int>& A);             // O(n^2)
void selection_sort(vector<int>& A);             // O(n^2)
void merge(vector<int>& A, int l, int m, int r); // O(n)
void merge_sort(vector<int>& A, int l, int r);   // O(n log n)

int main() 
{
    // Initialize random seed for generating random numbers
    srand(static_cast<unsigned>(time(nullptr)));

    const int n = 5;
    vector<int> arr; // Vector starts with size 0

    read_vector(arr, n);

    cout << "Initial array" << endl;
    print_vector(arr);

    // Create copies so each algorithm works on the same unsorted vector
    auto v1 = arr; // Changes to v1 don't affect arr

    bubble_sort(v1);
    cout << "\nSorted by Bubble Sort (ascending)\n";
    print_vector(v1);

    auto v2 = arr;
    insertion_sort(v2);
    cout << "\nSorted by Insertion Sort (ascending)\n";
    print_vector(v2);

    auto v3 = arr;
    selection_sort(v3);
    cout << "\nSorted by Selection Sort (ascending)\n";
    print_vector(v3);

    auto v4 = arr;
    // merge_sort arguments: vector v4, start index, end index
    merge_sort(v4, 0, static_cast<int>(v4.size()) - 1);

    cout << "\nSorted by Merge Sort (ascending)\n";
    print_vector(v4);

    return 0;
}

/**
 * Reads n random integers into vector A
 * @param A Reference to vector (modifies the original)
 * @param n Number of elements to read
 */
void read_vector(vector<int>& A, int n) 
{
    A.resize(n); // Resize vector to exactly n elements

    for (int i = 0; i < n; ++i) {
        A[i] = rand() % 10 + 1; // Generate random numbers from 1 to 10
    }
}

/**
 * Prints vector elements separated by tabs
 * @param A Const reference to vector (guarantees no modification)
 */
void print_vector(const vector<int>& A) 
{
    for (int x : A) {
        cout << x << "\t";
    }
    cout << endl;
}

/**
 * Bubble Sort Algorithm - O(n^2) time complexity
 * Repeatedly steps through the list, compares adjacent elements and swaps them
 * if they are in the wrong order. The process is repeated until no swaps are needed.
 */
void bubble_sort(vector<int>& A)
{
    int n = static_cast<int>(A.size()); // Convert size_t to int to avoid warnings
    
    bool swapped;

    for (int b = 1; b < n; b++) {
        swapped = false;

        for (int i = 0; i < n - b; ++i) {
            if (A[i] > A[i + 1]) {
                swap(A[i], A[i + 1]); // Use built-in swap function
                swapped = true;
            }
        }

        if (!swapped) {
            break; // Array is already sorted
        }
    }
}

/**
 * Insertion Sort Algorithm - O(n^2) time complexity
 * Builds the final sorted array one item at a time by taking elements
 * from the unsorted portion and inserting them into their correct position.
 */
void insertion_sort(vector<int>& A)
{
    int n = static_cast<int>(A.size());

    for (int i = 1; i < n; ++i) { // Start from second element
        int key = A[i]; // Element to be inserted
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
 * Selection Sort Algorithm - O(n^2) time complexity
 * Finds the minimum element in the unsorted portion and swaps it
 * with the first element of the unsorted portion.
 */
void selection_sort(vector<int>& A) 
{
    int n = static_cast<int>(A.size());

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i; // Index of minimum element

        // Find minimum element in remaining array
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }

        // Swap if minimum element is not at current position
        if (min_idx != i) {
            swap(A[i], A[min_idx]);
        }
    }
}

/**
 * Merge Sort Algorithm - O(n log n) time complexity
 * Divides the array into two halves, recursively sorts them,
 * and then merges the two sorted halves.
 */
void merge_sort(vector<int>& A, int left, int right)
{
    if (left >= right) {
        return; // Base case: array has 0 or 1 element
    }

    int m = left + (right - left) / 2; // Calculate middle position

    merge_sort(A, left, m);     // Recursively sort left half
    merge_sort(A, m + 1, right); // Recursively sort right half
    merge(A, left, m, right);   // Merge the two sorted halves
}

/**
 * Merge function for Merge Sort - O(n) time complexity
 * Merges two sorted subarrays into a single sorted array.
 * @param A Array to merge
 * @param left Start index of first subarray
 * @param m End index of first subarray (middle)
 * @param right End index of second subarray
 */
void merge(vector<int>& A, int left, int m, int right) 
{
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
        } else {
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
