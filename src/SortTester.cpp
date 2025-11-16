#include "SortTester.hpp"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <utility>

SortTester::SortTester(ArrayGenerator generator)
    : generator_(std::move(generator)) {}

std::vector<SortTester::Measurement> SortTester::benchmark(
    const std::vector<ArrayGenerator::DatasetType>& datasets,
    const std::vector<std::size_t>& sizes,
    const std::vector<std::pair<std::string, SortFunction>>& algorithms,
    std::size_t repetitions) {
    std::vector<Measurement> measurements;
    if (datasets.empty() || sizes.empty() || algorithms.empty()) {
        return measurements;
    }
    const auto max_size = *std::max_element(sizes.begin(), sizes.end());
    measurements.reserve(datasets.size() * sizes.size() * algorithms.size());

    for (auto dataset : datasets) {
        auto series = generator_.generateSeries(dataset, sizes);
        for (std::size_t index = 0; index < sizes.size(); ++index) {
            for (const auto& [name, algorithm] : algorithms) {
                std::vector<ArrayGenerator::ValueType> data = series[index];
                double total_ms = 0.0;
                for (std::size_t rep = 0; rep < repetitions; ++rep) {
                    auto copy = data;
                    const auto start = std::chrono::high_resolution_clock::now();
                    algorithm(copy);
                    const auto end = std::chrono::high_resolution_clock::now();
                    total_ms += std::chrono::duration<double, std::milli>(end - start).count();
                }
                measurements.push_back(Measurement{ArrayGenerator::datasetName(dataset),
                                                   sizes[index],
                                                   name,
                                                   total_ms / static_cast<double>(repetitions)});
            }
        }
    }
    return measurements;
}

void SortTester::exportToCsv(const std::string& path, const std::vector<Measurement>& data) {
    std::ofstream output(path);
    output << "dataset,size,algorithm,milliseconds\n";
    for (const auto& measurement : data) {
        output << measurement.dataset << ',' << measurement.size << ',' << measurement.algorithm << ','
               << measurement.milliseconds << '\n';
    }
}
