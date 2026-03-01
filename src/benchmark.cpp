#include "benchmark.h"
#include <chrono>
#include <iostream>

double measureSort(std::vector<int>& arr, std::function<void()> sortFn) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFn();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

void writeCSV(const std::string& path, const std::vector<Result>& results, bool append) {
    bool fileExists = std::ifstream(path).good();

    std::ofstream out(path, append ? std::ios::app : std::ios::trunc);
    if (!append || !fileExists)
        out << "algorithm,input_type,size,time_ms\n";

    for (auto& r : results)
        out << r.algorithm << "," << r.inputType << "," << r.size << "," << r.timeMs << "\n";
    out.close();
    std::cout << "Resultados salvos em " << path << std::endl;
}
