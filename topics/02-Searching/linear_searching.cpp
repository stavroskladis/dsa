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
    std::vector<int> nums{9, 10, 5, 8, 7, 4, 11, 6, 15, 3};
    int target = 5;

    int idx = linear_search(nums, target);

    std::cout << idx << std::endl;
    return 0;
}