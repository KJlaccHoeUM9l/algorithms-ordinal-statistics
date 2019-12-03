#ifndef ORDINAL_STATISTICS_UTILS_H
#define ORDINAL_STATISTICS_UTILS_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <random>
#include <string>

std::mt19937 gen(time(0));
int Random(int a, int b) {
    std::uniform_int_distribution<> uid(a, b);
    return  uid(gen);
}

std::vector<int> SieveEratosthenes(size_t n) {
    std::vector<int> numbers(n + 1);
    std::iota(numbers.begin(), numbers.end(), 0);
    numbers[1] = 0;

    std::vector<int> simple_numbers;
    for (size_t i = 2; i < n + 1; i++) {
        if (numbers[i] != 0) {
            simple_numbers.push_back(numbers[i]);
            for (size_t j = i; j < n + 1; j += i) {
                numbers[j] = 0;
            }
        }
    }

    return simple_numbers;
}

std::vector<int> RandomSimpleNumbers(const std::vector<int>& simple_numbers, size_t n) {
    std::vector<int> result(n);
    for (int& number: result) {
        number = simple_numbers[Random(0, simple_numbers.size() - 1)];
    }
    return result;
}

template <typename T>
std::string ConvertVectorToString(const std::vector<T>& array) {
    std::string result = "";

    for (T value: array) {
        result += std::to_string(value) + " ";
    }
    result.pop_back();

    return result;
}

template <typename T>
bool operator<(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return lhs.size() < rhs.size();
    } else {
        for (size_t i = 0; i < lhs.size(); i++) {
            if (rhs[i] > lhs[i]) {
                return false;
            }
        }
        return true;
    }
}

double GetMean(const std::vector<double>& array) {
    return std::accumulate(array.begin(), array.end(), 0.0) / array.size();
}

void DrawResults(double quantile, const std::vector<size_t>& sizes, const std::vector<std::vector<double>>& times) {
    std::string python_file = "..\\3rdparty\\draw_graphs.py";
    std::string sizes_string = ConvertVectorToString(sizes);
    std::string times_naive = ConvertVectorToString(times[0]);
    std::string times_randomized = ConvertVectorToString(times[1]);
    std::string times_determined = ConvertVectorToString(times[2]);

    std::string cmd = "python " + python_file + " " + std::to_string(quantile) + " " + std::to_string(sizes.size()) + " " +
                      std::to_string(1 + times.size()) + " " + sizes_string + " " + times_naive + " " + times_randomized +
                      " " + times_determined;

    system(cmd.c_str());
}

#endif //ORDINAL_STATISTICS_UTILS_H
