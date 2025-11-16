#include "ArrayGenerator.hpp"
#include "SortTester.hpp"
#include "merge_sorts.hpp"

#include <iostream>
#include <vector>
#include <string>

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
      {"merge_insertion_t30", [](auto& data) { hybridMergeSort(data, 30); }},
  };

  const auto measurements = tester.benchmark(datasets, sizes, algorithms, 1);
  const std::string output_path = "../results/measurements.csv";
  SortTester::exportToCsv(output_path, measurements);
  std::cout << "Данные сохранены в " << output_path << '\n';

  return 0;
}
