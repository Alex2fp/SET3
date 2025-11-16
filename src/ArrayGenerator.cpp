#include "ArrayGenerator.hpp"

#include <algorithm>
#include <numeric>

namespace {
constexpr int kMinValue = -1e9;
constexpr int kMaxValue = 1e9;
}

ArrayGenerator::ArrayGenerator()
    : rng_(std::random_device{}()) {}

std::vector<ArrayGenerator::ValueType> ArrayGenerator::generate(DatasetType type,
                                                                std::size_t size) {
    return generateBase(type, size);
}

std::vector<std::vector<ArrayGenerator::ValueType>> ArrayGenerator::generateSeries(
    DatasetType type,
    const std::vector<std::size_t>& sizes) {
    std::vector<std::vector<ValueType>> series;
    if (sizes.empty()) {
        return series;
    }
    const std::size_t max_size = *std::max_element(sizes.begin(), sizes.end());
    auto base = generateBase(type, max_size);
    series.reserve(sizes.size());
    for (std::size_t length : sizes) {
        series.emplace_back(base.begin(), base.begin() + static_cast<std::ptrdiff_t>(length));
    }
    return series;
}

std::vector<std::size_t> ArrayGenerator::defaultSizes(std::size_t min,
                                                      std::size_t max,
                                                      std::size_t step) {
    std::vector<std::size_t> sizes;
    for (std::size_t value = min; value <= max; value += step) {
        sizes.push_back(value);
    }
    return sizes;
}

std::string ArrayGenerator::datasetName(DatasetType type) {
    switch (type) {
        case DatasetType::Random:
            return "random";
        case DatasetType::Sorted:
            return "sorted";
        case DatasetType::Reversed:
            return "reversed";
        case DatasetType::NearlySorted:
            return "nearly_sorted";
    }
    return "unknown";
}

std::vector<ArrayGenerator::ValueType> ArrayGenerator::generateBase(DatasetType type,
                                                                    std::size_t size) {
    std::uniform_int_distribution<ValueType> dist(kMinValue, kMaxValue);
    std::vector<ValueType> data(size);
    switch (type) {
        case DatasetType::Random: {
            for (auto& value : data) {
                value = dist(rng_);
            }
            break;
        }
        case DatasetType::Sorted: {
            for (auto& value : data) {
                value = dist(rng_);
            }
            std::sort(data.begin(), data.end());
            break;
        }
        case DatasetType::Reversed: {
            for (auto& value : data) {
                value = dist(rng_);
            }
            std::sort(data.begin(), data.end(), std::greater<>());
            break;
        }
        case DatasetType::NearlySorted: {
            for (auto& value : data) {
                value = dist(rng_);
            }
            std::sort(data.begin(), data.end());
            const std::size_t swaps = std::max<std::size_t>(1, size / 50);
            std::uniform_int_distribution<std::size_t> index_dist(0, size - 1);
            for (std::size_t i = 0; i < swaps; ++i) {
                std::size_t lhs = index_dist(rng_);
                std::size_t rhs = index_dist(rng_);
                std::swap(data[lhs], data[rhs]);
            }
            break;
        }
    }
    return data;
}
