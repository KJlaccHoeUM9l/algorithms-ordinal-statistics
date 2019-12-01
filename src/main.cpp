#include <iostream>
#include <vector>
#include <exception>
#include <numeric>

#include "utils.h"
#include "../utils/tests.h"
#include "ordinal_statistics.h"


size_t size_of_item_selection;
const size_t simple_numbers_size = 1000000;
const std::vector<int> simple_numbers = SieveEratosthenes(simple_numbers_size);


enum Inputs {
    simple_numbers_array,
    vectors_of_simple_numbers,
    natural_numbers_uniform_distribution
};

std::vector<int> GetSimpleNumbers(size_t n) {
    return RandomSimpleNumbers(simple_numbers, n);
}

std::vector<std::vector<int>> GetVectorOfVectorsOfSimpleNumbers(size_t n) {
    std::vector<std::vector<int>> result(n);
    for (auto& vector: result) {
        vector = RandomSimpleNumbers(simple_numbers, static_cast<size_t>(Random(3, 47)));
    }
    return result;
}

std::vector<int> GetNumbersWithoutRepetitionsUniformDistribution(size_t n) {
    std::vector<int> result(n);
    std::iota(result.begin(), result.end(), -47);
    for (size_t i = 0; i < result.size(); i++) {
        std::swap(result[i], result[Random(0, n - 1)]);
    }
    return result;
}

template <typename DataFunction>
std::vector<std::vector<double>> ProcessData(DataFunction data_function, double quantile, const vector<size_t>& sizes) {
    std::vector<double> naive_times;
    std::vector<double> randomized_times;
    std::vector<double> determined_times;
    for (size_t N: sizes) {
        std::vector<double> current_naive_times(size_of_item_selection);
        std::vector<double> current_randomized_times(size_of_item_selection);
        std::vector<double> current_determined_times(size_of_item_selection);
        for (size_t i = 0; i < size_of_item_selection; i++) {
            auto data = data_function(N);
            auto k = static_cast<size_t>(quantile * N);

            auto[value_naive, time_naive] = NaiveSelect(data, k);
            auto[value_randomized, time_randomized] = NaiveSelect(data, k);
            auto[value_determined, time_determined] = NaiveSelect(data, k);

            if (value_naive != value_randomized && value_naive != value_determined) {
                throw std::runtime_error("Different answers");
            }

            current_naive_times[i] = time_naive;
            current_randomized_times[i] = time_randomized;
            current_determined_times[i] = time_determined;
        }
        naive_times.push_back(GetMean(current_naive_times));
        randomized_times.push_back(GetMean(current_randomized_times));
        determined_times.push_back(GetMean(current_determined_times));
    }

    return {naive_times, randomized_times, determined_times};
}

int main() {
//    RunTests();

    // Set parameters
    auto data_type = Inputs(2);
    double quantile = 1.0 / 3.0;
    size_of_item_selection = 10;
//    std::vector<size_t> sizes = {500, 1000, 1500, 2000, 2500};
//    std::vector<size_t> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    std::vector<size_t> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
//    std::vector<size_t> sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
//    std::vector<size_t> sizes = {1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000};

    // Process data
    std::cout << "C++: process data..." << std::endl;
    std::vector<std::vector<double>> times;
    switch (data_type) {
        case Inputs::simple_numbers_array: {
            times = ProcessData(GetSimpleNumbers, quantile, sizes);
            break;
        }
        case Inputs::vectors_of_simple_numbers: {
            times = ProcessData(GetVectorOfVectorsOfSimpleNumbers, quantile, sizes);
            break;
        }
        case Inputs::natural_numbers_uniform_distribution: {
            times = ProcessData(GetNumbersWithoutRepetitionsUniformDistribution, quantile, sizes);
            break;
        }
    }

    // Draw results
    DrawResults(quantile, sizes, times);

    return 0;
}
