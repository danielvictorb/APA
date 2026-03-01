#pragma once
#include <string>
#include <vector>
#include <functional>
#include <fstream>

struct Result {
    std::string algorithm;
    std::string inputType;
    int size;
    double timeMs;
};

double measureSort(std::vector<int>& arr, std::function<void()> sortFn);

void writeCSV(const std::string& path, const std::vector<Result>& results, bool append = false);
