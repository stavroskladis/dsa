#include "utils.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

/**
 * Linear searching on a vector.
 *  - Best Case Time Complexity O(1)
 *  - Worst Case Time Complexity O(n)
 *  - Average Time Complexity O(n)
 *  - Space Complexity O(1)
 */
template <typename T>
int linear_search(const std::vector<T>& arr, T target) {

    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return static_cast<int>(i);
        }
    }

    return -1;
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

    std::cout << "\nTarget " << target << " found at index " << idx
              << std::endl;

    return 0;
}