#include "../include/sort_algorithms.h"
#include <algorithm>
#include <vector>

// Helper function for merge sort: merge two sorted halves
static void merge(std::vector<int>& arr, std::vector<int>& temp,
                  std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t i = left;     // index for left subarray
    std::size_t j = mid + 1;  // index for right subarray
    std::size_t k = left;     // index for merged array
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    // Copy back to original array
    for (std::size_t p = left; p <= right; ++p) {
        arr[p] = temp[p];
    }
}

// Recursive merge sort implementation
static void mergeSortRec(std::vector<int>& arr, std::vector<int>& temp,
                         std::size_t left, std::size_t right) {
    if (left >= right) return;
    std::size_t mid = left + (right - left) / 2;
    mergeSortRec(arr, temp, left, mid);
    mergeSortRec(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

void mergeSort(std::vector<int>& arr, std::size_t l, std::size_t r) {
    if (arr.empty() || l >= r) return;
    std::vector<int> temp(arr.size());
    mergeSortRec(arr, temp, l, r);
}

// Internal quick sort using long long indices to avoid size_t underflow
static void quickSortInternal(std::vector<int>& arr, long long left, long long right) {
    long long i = left;
    long long j = right;
    int pivot = arr[left + (right - left) / 2];
    while (i <= j) {
        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }
    if (left < j) quickSortInternal(arr, left, j);
    if (i < right) quickSortInternal(arr, i, right);
}

void quickSort(std::vector<int>& arr, std::size_t l, std::size_t r) {
    if (arr.empty() || l >= r) return;
    quickSortInternal(arr, static_cast<long long>(l), static_cast<long long>(r));
}

// Heapify a subtree rooted at index i
static void heapify(std::vector<int>& arr, std::size_t n, std::size_t i) {
    std::size_t largest = i;
    std::size_t left = 2 * i + 1;
    std::size_t right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    std::size_t n = arr.size();
    if (n <= 1) return;
    // Build max heap
    for (long long i = static_cast<long long>(n) / 2 - 1; i >= 0; --i) {
        heapify(arr, n, static_cast<std::size_t>(i));
    }
    // One by one extract elements
    for (long long i = static_cast<long long>(n) - 1; i > 0; --i) {
        std::swap(arr[0], arr[static_cast<std::size_t>(i)]);
        heapify(arr, static_cast<std::size_t>(i), 0);
    }
}

// Heapify for characters
static void heapifyChar(std::vector<char>& arr, std::size_t n, std::size_t i) {
    std::size_t largest = i;
    std::size_t left = 2 * i + 1;
    std::size_t right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapifyChar(arr, n, largest);
    }
}

void heapSortChar(std::vector<char>& arr) {
    std::size_t n = arr.size();
    if (n <= 1) return;
    for (long long i = static_cast<long long>(n) / 2 - 1; i >= 0; --i) {
        heapifyChar(arr, n, static_cast<std::size_t>(i));
    }
    for (long long i = static_cast<long long>(n) - 1; i > 0; --i) {
        std::swap(arr[0], arr[static_cast<std::size_t>(i)]);
        heapifyChar(arr, static_cast<std::size_t>(i), 0);
    }
}