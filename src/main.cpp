#include "sorts.h"
#include "generator.h"
#include "benchmark.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

static const int TIMEOUT_MS = 30000;

struct SortEntry {
    std::string name;
    std::function<void(std::vector<int>&)> fn;
    bool isQuadratic;
};

int main(int argc, char* argv[]) {
    std::string mode = (argc > 1) ? argv[1] : "all";

    std::map<std::string, InputType> typeMap = {
        {"random",     InputType::Random},
        {"few_unique", InputType::FewUnique},
        {"sorted",     InputType::Sorted},
        {"reversed",   InputType::Reversed},
    };

    std::vector<InputType> inputTypes;
    bool append = false;

    if (mode == "all") {
        inputTypes = {InputType::Random, InputType::FewUnique, InputType::Sorted, InputType::Reversed};
    } else if (typeMap.count(mode)) {
        inputTypes = {typeMap[mode]};
        append = true;
    } else {
        std::cerr << "Uso: ./benchmark [random|few_unique|sorted|reversed|all]" << std::endl;
        return 1;
    }

    std::vector<int> sizes = {1000, 5000, 10000, 50000, 100000};

    std::vector<SortEntry> sorts = {
        {"insertion_sort", [](auto& v) { insertionSort(v); }, true},
        {"selection_sort", [](auto& v) { selectionSort(v); }, true},
        {"quick_sort",     [](auto& v) { quickSort(v, 0, v.size() - 1); }, false},
        {"merge_sort",     [](auto& v) { mergeSort(v, 0, v.size() - 1); }, false},
    };

    std::vector<bool> skipped(sorts.size(), false);
    std::vector<Result> results;

    for (auto type : inputTypes) {
        std::string typeName = inputTypeName(type);
        std::cout << "\n=== " << typeName << " ===" << std::endl;

        std::fill(skipped.begin(), skipped.end(), false);

        for (int size : sizes) {
            auto original = generateArray(type, size);

            for (int s = 0; s < (int)sorts.size(); s++) {
                if (skipped[s]) {
                    std::cout << "  " << sorts[s].name << " n=" << size << " -> SKIP" << std::endl;
                    continue;
                }

                auto copy = original;
                double ms = measureSort(copy, [&]() { sorts[s].fn(copy); });

                results.push_back({sorts[s].name, typeName, size, ms});
                std::cout << "  " << sorts[s].name << " n=" << size << " -> " << ms << " ms" << std::endl;

                if (sorts[s].isQuadratic && ms > TIMEOUT_MS)
                    skipped[s] = true;
            }
        }
    }

    writeCSV("results/results.csv", results, append);
    return 0;
}
