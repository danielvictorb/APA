#include "generator.h"
#include <random>
#include <algorithm>
#include <numeric>

std::vector<int> generateArray(InputType type, int size) {
    std::vector<int> arr(size);

    switch (type) {
        case InputType::Random: {
            std::mt19937 rng(42);
            std::uniform_int_distribution<int> dist(0, size);
            for (int& x : arr) x = dist(rng);
            break;
        }
        case InputType::FewUnique: {
            std::mt19937 rng(42);
            std::uniform_int_distribution<int> dist(0, 10);
            for (int& x : arr) x = dist(rng);
            break;
        }
        case InputType::Sorted:
            std::iota(arr.begin(), arr.end(), 0);
            break;

        case InputType::Reversed:
            std::iota(arr.begin(), arr.end(), 0);
            std::reverse(arr.begin(), arr.end());
            break;
    }

    return arr;
}

std::string inputTypeName(InputType type) {
    switch (type) {
        case InputType::Random:    return "random";
        case InputType::FewUnique: return "few_unique";
        case InputType::Sorted:    return "sorted";
        case InputType::Reversed:  return "reversed";
    }
    return "unknown";
}
