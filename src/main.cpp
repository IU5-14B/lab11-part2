#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <iomanip>

#include "../include/avl_tree.h"
#include "../include/two_three_tree.h"
#include "../include/sort_algorithms.h"

/**
 * Entry point for the demonstration program.  This program illustrates
 * construction of AVL and 2–3 trees and compares the running time of
 * merge sort, quick sort and heap sort on different types of input.
 */
int main() {
    // Demonstrate AVL tree construction
    std::vector<int> demoValues = {10, 20, 5, 6, 15, 30, 25, 16, 8};
    AVLNode* avlRoot = nullptr;
    for (int val : demoValues) {
        avlRoot = avlInsert(avlRoot, val);
    }
    std::cout << "Inorder traversal of AVL tree: ";
    inorder(avlRoot);
    std::cout << std::endl;
    deleteTree(avlRoot);

    // Demonstrate 2–3 tree construction
    Node23* root23 = nullptr;
    for (int val : demoValues) {
        insert23(root23, val);
    }
    std::cout << "Inorder traversal of 2-3 tree: ";
    inorder23(root23);
    std::cout << std::endl;
    deleteTree23(root23);

    // Demonstrate heap sort on simple lists
    std::vector<int> listA = {1, 2, 3, 4, 5};
    heapSort(listA);
    std::cout << "Heap sort on [1,2,3,4,5]: ";
    for (int v : listA) std::cout << v << " ";
    std::cout << std::endl;
    std::vector<int> listB = {5, 4, 3, 2, 1};
    heapSort(listB);
    std::cout << "Heap sort on [5,4,3,2,1]: ";
    for (int v : listB) std::cout << v << " ";
    std::cout << std::endl;
    std::vector<char> listC = {'S', 'O', 'R', 'T', 'I', 'N', 'G'};
    heapSortChar(listC);
    std::cout << "Heap sort on [S,O,R,T,I,N,G]: ";
    for (char c : listC) std::cout << c << " ";
    std::cout << std::endl;

    // Performance comparison of sorting algorithms
    // sizes to test: 10^2, 10^3, 10^4, 10^5, 10^6
    std::vector<std::size_t> sizes = {100, 1000, 10000, 100000, 1000000};
    std::vector<std::string> distributions = {"random", "ascending", "descending"};
    std::vector<std::string> algorithms = {"merge", "quick", "heap"};
    // Set up random number generator
    std::mt19937 gen(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::ofstream fout("results.csv");
    if (!fout) {
        std::cerr << "Failed to open results.csv for writing" << std::endl;
        return 1;
    }
    fout << "algorithm,n,distribution,time_ms";
    for (const auto& alg : algorithms) {
        for (std::size_t n : sizes) {
            for (const auto& dist : distributions) {
                // Generate input array
                std::vector<int> arr;
                arr.reserve(n);
                if (dist == "random") {
                    std::uniform_int_distribution<> dis(1, static_cast<int>(n));
                    for (std::size_t i = 0; i < n; ++i) {
                        arr.push_back(dis(gen));
                    }
                } else if (dist == "ascending") {
                    for (std::size_t i = 0; i < n; ++i) {
                        arr.push_back(static_cast<int>(i + 1));
                    }
                } else { // descending
                    for (std::size_t i = 0; i < n; ++i) {
                        arr.push_back(static_cast<int>(n - i));
                    }
                }
                // Make a copy to sort
                std::vector<int> toSort = arr;
                auto start = std::chrono::steady_clock::now();
                if (alg == "merge") {
                    mergeSort(toSort, 0, toSort.size() - 1);
                } else if (alg == "quick") {
                    quickSort(toSort, 0, toSort.size() - 1);
                } else if (alg == "heap") {
                    heapSort(toSort);
                }
                auto end = std::chrono::steady_clock::now();
                double elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
                fout << "\n" << alg << "," << n << "," << dist << "," << std::fixed << std::setprecision(3) << elapsed_ms;
                // flush after each measurement to preserve data even if program stops early
                fout.flush();
                // Print progress to console for long runs
                std::cout << "Finished " << alg << " sort for n=" << n << " distribution=" << dist << " time=" << elapsed_ms << " ms" << std::endl;
            }
        }
    }
    fout.close();
    std::cout << "Results written to results.csv" << std::endl;
    return 0;
}