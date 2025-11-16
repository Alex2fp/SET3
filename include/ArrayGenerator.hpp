#pragma once

#include <cstddef>
#include <random>
#include <string>
#include <vector>

class ArrayGenerator {
public:
    using ValueType = int;

    enum class DatasetType {
        Random,
        Sorted,
        Reversed,
        NearlySorted
    };

    ArrayGenerator();

    [[nodiscard]] std::vector<ValueType> generate(DatasetType type, std::size_t size);

    [[nodiscard]] std::vector<std::vector<ValueType>> generateSeries(
        DatasetType type,
        const std::vector<std::size_t>& sizes);

    static std::vector<std::size_t> defaultSizes(std::size_t min = 500,
                                                 std::size_t max = 100'000,
                                                 std::size_t step = 100);

    static std::string datasetName(DatasetType type);

private:
    std::vector<ValueType> generateBase(DatasetType type, std::size_t size);

    std::mt19937 rng_;
};
