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

    int idx = linear_search(nums, target);
    std::cout << "Linear searching" << std::endl;
    std::cout << "Target " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << std::endl;

    std::sort(nums.begin(), nums.end());
    std::cout << "\nSorted array" << std::endl;
    print_vector<int>(nums);
    std::cout << std::endl;

    idx = binary_search(nums, target);
    std::cout << "Binary searching" << std::endl;
    std::cout << "Target " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << "\n\n";

    idx = binary_search_recursive(nums, target, 0,
                                  static_cast<int>(nums.size()) - 1);
    std::cout << "Recursive Binary searching" << std::endl;
    std::cout << "Target " << target
              << (idx >= 0 ? " found at index " + std::to_string(idx)
                           : " not found")
              << "\n\n";

    return 0;
}
