#include "merge_sorts.hpp"

#include <algorithm>

namespace {
void merge(std::vector<int>& data, std::vector<int>& buffer, std::size_t left, std::size_t mid,
           std::size_t right) {
    std::size_t i = left;
    std::size_t j = mid;
    std::size_t k = left;
    while (i < mid && j < right) {
        if (data[i] <= data[j]) {
            buffer[k++] = data[i++];
        } else {
            buffer[k++] = data[j++];
        }
    }
    while (i < mid) {
        buffer[k++] = data[i++];
    }
    while (j < right) {
        buffer[k++] = data[j++];
    }
    for (std::size_t idx = left; idx < right; ++idx) {
        data[idx] = buffer[idx];
    }
}

void mergeSortImpl(std::vector<int>& data, std::vector<int>& buffer, std::size_t left,
                   std::size_t right) {
    if (right - left <= 1) {
        return;
    }
    const std::size_t mid = left + (right - left) / 2;
    mergeSortImpl(data, buffer, left, mid);
    mergeSortImpl(data, buffer, mid, right);
    merge(data, buffer, left, mid, right);
}

void insertionSort(std::vector<int>& data, std::size_t left, std::size_t right) {
    for (std::size_t i = left + 1; i < right; ++i) {
        int key = data[i];
        std::size_t j = i;
        while (j > left && data[j - 1] > key) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = key;
    }
}

void hybridMergeSortImpl(std::vector<int>& data, std::vector<int>& buffer, std::size_t left,
                         std::size_t right, std::size_t threshold) {
    if (right - left <= threshold) {
        insertionSort(data, left, right);
        return;
    }
    const std::size_t mid = left + (right - left) / 2;
    hybridMergeSortImpl(data, buffer, left, mid, threshold);
    hybridMergeSortImpl(data, buffer, mid, right, threshold);
    merge(data, buffer, left, mid, right);
}
} // namespace

void mergeSort(std::vector<int>& data) {
    if (data.empty()) {
        return;
    }
    std::vector<int> buffer(data.size());
    mergeSortImpl(data, buffer, 0, data.size());
}

void hybridMergeSort(std::vector<int>& data, std::size_t threshold) {
    if (data.empty()) {
        return;
    }
    std::vector<int> buffer(data.size());
    hybridMergeSortImpl(data, buffer, 0, data.size(), threshold);
}
