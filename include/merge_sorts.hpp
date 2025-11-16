#pragma once

#include <cstddef>
#include <vector>

void mergeSort(std::vector<int>& data);

void hybridMergeSort(std::vector<int>& data, std::size_t threshold = 15);
