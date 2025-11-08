#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "searching.hpp"
#include "utils.hpp"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int n = 5;
    std::vector<int> nums;
    int target = 5;

    read_vector(nums, n);

    std::cout << "Initial array" << std::endl;
    print_vector<int>(nums);
    std::cout << std::endl;

    /* Basic Search Algorithms: Linear Search */
    auto nums_ls = nums;
    int idx = linear_search(nums_ls, target);
    std::cout << "Linear searching" << std::endl;
    std::cout << "Target " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << std::endl;

    std::sort(nums.begin(), nums.end());
    std::cout << "\nSorted array" << std::endl;
    print_vector<int>(nums);
    std::cout << std::endl;

    /* Binary Search */
    auto nums_bs = nums;
    idx = binary_search(nums_bs, target);
    std::cout << "Binary searching" << std::endl;
    std::cout << "Target " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << "\n\n";

    /* Binary Search (using recursive calls) */
    auto nums_bsr = nums;
    idx = binary_search_recursive(nums_bsr, target, 0,
                                  static_cast<int>(nums.size()) - 1);
    std::cout << "Recursive Binary searching" << std::endl;
    std::cout << "Target " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << "\n\n";

    idx = lower_bound(nums, target);
    std::cout << "Lower bound for " << target << ": "
              << (idx >= 0 ? std::to_string(idx) : "not found") << std::endl;

    idx = upper_bound(nums, target);
    std::cout << "Upper bound for " << target << ": "
              << (idx >= 0 ? std::to_string(idx) : "not found") << std::endl;
    std::cout << std::endl;

    return 0;
}
