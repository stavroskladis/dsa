#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "../../includes/utils.hpp"

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

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int n = 5;
    std::vector<int> nums;

    read_vector(nums, n);

    std::cout << "Initial array" << std::endl;
    print_vector<int>(nums);

    int target = 5;
    int idx = linear_search(nums, target);

    std::cout << "Linear searching" << std::endl;
    std::cout << "\nTarget " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << std::endl;

    std::sort(nums.begin(), nums.end());
    std::cout << "\nSorted array" << std::endl;
    print_vector<int>(nums);

    idx = binary_search(nums, target);

    std::cout << "Binary searching" << std::endl;
    std::cout << "\nTarget " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << std::endl;

    return 0;
}
