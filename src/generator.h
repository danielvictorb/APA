#pragma once
#include <vector>
#include <string>

enum class InputType { Random, FewUnique, Sorted, Reversed };

std::vector<int> generateArray(InputType type, int size);
std::string inputTypeName(InputType type);
