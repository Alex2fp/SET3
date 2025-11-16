#pragma once

#include "ArrayGenerator.hpp"

#include <chrono>
#include <functional>
#include <string>
#include <utility>
#include <vector>

class SortTester {
public:
    struct Measurement {
        std::string dataset;
        std::size_t size;
        std::string algorithm;
        double milliseconds;
    };

    using SortFunction = std::function<void(std::vector<ArrayGenerator::ValueType>&)>;

    explicit SortTester(ArrayGenerator generator);

    std::vector<Measurement> benchmark(
        const std::vector<ArrayGenerator::DatasetType>& datasets,
        const std::vector<std::size_t>& sizes,
        const std::vector<std::pair<std::string, SortFunction>>& algorithms,
        std::size_t repetitions = 1);

    static void exportToCsv(const std::string& path, const std::vector<Measurement>& data);

private:
    ArrayGenerator generator_;
};
