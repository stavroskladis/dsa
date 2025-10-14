#include <iostream>
#include <utility> // for swap()
#include <vector>
using namespace std;

template <typename T>
int partition(vector<T>& arr, int low_index, int high_index) {
    // Consider the last element as pivot
    T pivot = arr[high_index];
    int i = low_index;
    int j = high_index - 1;

    while (true) {

        // Find element larger than pivot
        while (i < high_index && arr[i] < pivot)
            ++i;

        // Find element smaller than pivot
        while (j >= low_index && arr[j] > pivot)
            --j;

        // If two pointers crossover
        if (i >= j)
            break;

        // If a smaller element exists after the larger element
        swap(arr[i], arr[j]);
    }

    // Position the pivot at its final position
    swap(arr[i], arr[high_index]);

    // Return the final index of the pivot
    return i;
}

template <typename T>

void quick_sort(vector<T>& arr, int low_index, int high_index) {

    // Return vector has less than two elements

    if (low_index >= high_index)

        return;

    // Partition the vector and get the final index of the pivot

    int pivot_index = partition(arr, low_index, high_index);

    // Recursively sort the left part

    quick_sort(arr, low_index, pivot_index - 1);

    // Recursively sort the right part

    quick_sort(arr, pivot_index + 1, high_index);
}

// Template to print elements of a vector.

template <typename T>

void print_vector(const vector<T>& arr) {

    for (const auto elem : arr) {

        cout << elem << ' ';
    }

    cout << '\n';
}

int main() {

    // Initialize and print an unsorted vector

    vector<int> nums{7, 2, 1, 6, 8, 5, 3, 4};

    cout << "Unsorted Vector: ";

    print_vector(nums);

    // Sort the vector using quick sort

    cout << "Sorted Vector: ";

    quick_sort(nums, 0, nums.size() - 1);

    print_vector(nums);

    return 0;
}