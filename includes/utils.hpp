#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

/**
 * Reads n random integers into vector A
 * @param A Reference to vector (modifies the original)
 * @param n Number of elements to read
 */
inline void read_vector(std::vector<int>& A, int n) {
    A.resize(n); // Resize vector to exactly n elements

    for (int i = 0; i < n; ++i) {
        // Generate random numbers from 1 to 10
        A[i] = std::rand() % 10 + 1;
    }
}

/**
 * Prints vector elements separated by tabs
 * @param A Const reference to vector (guarantees no
 * modification)
 */
template <typename T>
void print_vector(const std::vector<T>& A) {
    for (const auto& elem : A) {
        std::cout << elem << "\t";
    }
    std::cout << std::endl;
}

#endif
