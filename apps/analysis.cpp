#include "ArrayGenerator.hpp"
#include "SortTester.hpp"
#include "merge_sorts.hpp"

#include <iostream>

int main() {
    ArrayGenerator generator;
    SortTester tester(generator);

    const auto sizes = ArrayGenerator::defaultSizes();
    const std::vector<ArrayGenerator::DatasetType> datasets = {
        ArrayGenerator::DatasetType::Random,
        ArrayGenerator::DatasetType::Sorted,
        ArrayGenerator::DatasetType::Reversed,
        ArrayGenerator::DatasetType::NearlySorted,
    };

    const std::vector<std::pair<std::string, SortTester::SortFunction>> algorithms = {
        {"merge_sort", [](auto& data) { mergeSort(data); }},
        {"merge_insertion_t15", [](auto& data) { hybridMergeSort(data, 15); }},
    };

    const auto measurements = tester.benchmark(datasets, sizes, algorithms, 1);

    const std::string output_path = "results/measurements.csv";
    SortTester::exportToCsv(output_path, measurements);
    std::cout << "Measurements stored in " << output_path << '\n';

    for (const auto& dataset : datasets) {
        const auto dataset_name = ArrayGenerator::datasetName(dataset);
        double merge_total = 0.0;
        double hybrid_total = 0.0;
        std::size_t count = 0;
        for (const auto& measurement : measurements) {
            if (measurement.dataset != dataset_name) {
                continue;
            }
            if (measurement.algorithm == "merge_sort") {
                merge_total += measurement.milliseconds;
            } else if (measurement.algorithm == "merge_insertion_t15") {
                hybrid_total += measurement.milliseconds;
            }
            ++count;
        }
        if (count > 0) {
            std::cout << dataset_name << ": avg merge " << merge_total / count << " ms, avg hybrid "
                      << hybrid_total / count << " ms\n";
        }
    }
    return 0;
}
