#include "merge_sorts.hpp"

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    hybridMergeSort(data, 30);
    for (int i = 0; i < n; ++i) {
        if (i) {
            std::cout << ' ';
        }
        std::cout << data[i];
    }
    std::cout << '\n';
    return 0;
}
