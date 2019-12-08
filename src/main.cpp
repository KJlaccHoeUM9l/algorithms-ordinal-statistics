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
        vector = RandomSimpleNumbers(simple_numbers, static_cast<size_t>(Random(3, 17)));
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
            auto k = std::clamp(static_cast<size_t>(quantile * N), 1u, N);

            auto[value_naive, time_naive] = NaiveSelect(data, k);
            auto[value_randomized, time_randomized] = RandomizedSelect(data, k);
            auto[value_determined, time_determined] = DeterminedSelect(data, k);

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

std::vector<std::vector<double>> GetWorkTimes(const Inputs& data_type, double quantile, const std::vector<size_t>& sizes) {
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
    return times;
}

void main1() {
    // Set up parameters
    auto data_type = Inputs(0);
    double quantile = 1.0 / 2.0;
//    std::vector<size_t> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    std::vector<size_t> sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};

    // Process data
    std::cout << "C++: process data..." << std::endl;
    std::vector<std::vector<double>> times = GetWorkTimes(data_type, quantile, sizes);

    // Draw results
    DrawResults(quantile, sizes, times);
}

void main2() {
    std::vector<double> quantiles = {0, 1.0 / 4.0, 1.0 / 3.0, 1.0 / 2.0, 2.0 / 3.0, 3.0 / 4.0, 1};
    std::vector<size_t> size = {1000000};
    std::vector<Inputs> data_types = {Inputs::simple_numbers_array, Inputs::vectors_of_simple_numbers,
                                      Inputs::natural_numbers_uniform_distribution};

    std::cout << "C++: process data..." << std::endl;
    std::vector<std::vector<std::vector<double>>> all_times;
    for (Inputs data_type: data_types) {
        std::cout << "Data type: " << data_type << std::endl;
        std::vector<std::vector<double>> times_for_current_data_type;
        for (double quantile: quantiles) {
            std::cout << "\tQuantile: " << quantile << std::endl;
            auto times_for_current_quantile = GetWorkTimes(data_type, quantile, size);
            times_for_current_data_type.emplace_back(std::vector<double>{times_for_current_quantile[0][0],
                                                                         times_for_current_quantile[1][0],
                                                                         times_for_current_quantile[2][0]});
        }
        all_times.push_back(times_for_current_data_type);
    }
    DrawHistogram(*size.begin(), quantiles.size(), quantiles, all_times);
}

int main() {
    size_of_item_selection = 10;
//    RunTests();
//    main1();
    main2();

    return 0;
}
