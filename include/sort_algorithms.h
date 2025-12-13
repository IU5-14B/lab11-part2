#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>
#include <cstddef>
#include <string>

/**
 * A collection of basic sorting algorithm implementations.  The
 * functions defined here operate on std::vector<int> and mutate the
 * vector in‑place.  For demonstration purposes only – these
 * implementations are not optimised for production use.
 */

// Merge sort: sorts arr[l..r] in ascending order
void mergeSort(std::vector<int>& arr, std::size_t l, std::size_t r);

// Quick sort: sorts arr[l..r] in ascending order
void quickSort(std::vector<int>& arr, std::size_t l, std::size_t r);

// Heap sort: sorts entire array in ascending order
void heapSort(std::vector<int>& arr);

// Heap sort for characters; sorts arr in ascending (alphabetical) order
void heapSortChar(std::vector<char>& arr);

// Heap sort with step-by-step output (array-heap representation)
void heapSortWithSteps(std::vector<int>& arr);

// Heap sort for characters with step-by-step output
void heapSortCharWithSteps(std::vector<char>& arr);

#endif // SORT_ALGORITHMS_H