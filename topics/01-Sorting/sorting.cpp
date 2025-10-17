#include "sorting.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main() {
    // Initialize random seed for generating random numbers
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int n = 5;
    std::vector<int> arr;

    read_vector(arr, n);

    std::cout << "Initial array" << std::endl;
    print_vector<int>(arr);

    auto v1 = arr;
    bubble_sort(v1);
    std::cout << std::endl
              << "Sorted by Bubble Sort (ascending)" << std::endl;
    print_vector<int>(v1);

    auto v2 = arr;
    insertion_sort(v2);
    std::cout << std::endl
              << "Sorted by Insertion Sort (ascending)" << std::endl;
    print_vector<int>(v2);

    auto v3 = arr;
    selection_sort(v3);
    std::cout << std::endl
              << "Sorted by Selection Sort (ascending)" << std::endl;
    print_vector<int>(v3);

    auto v4 = arr;
    // merge_sort arguments: vector v4, start index, end index
    merge_sort(v4, 0, static_cast<int>(v4.size()) - 1);

    std::cout << std::endl
              << "Sorted by Merge Sort (ascending)" << std::endl;
    print_vector<int>(v4);

    auto v5 = arr;
    quick_sort(v5, 0, static_cast<int>(v5.size()) - 1);
    std::cout << std::endl
              << "Sorted by Quick Sort (ascending)" << std::endl;
    print_vector<int>(v5);

    auto v6 = arr;
    // std::less<T> is the default comparator (ascending order)
    sort(v6.begin(), v6.end());
    std::cout << std::endl
              << "Sorted by std::sort (ascending)" << std::endl;
    print_vector<int>(v6);

    auto v7 = arr;
    count_sort(v7);
    std::cout << std::endl
              << "Sorted by count_sort (ascending)" << std::endl;
    print_vector<int>(v7);

    return 0;
}
