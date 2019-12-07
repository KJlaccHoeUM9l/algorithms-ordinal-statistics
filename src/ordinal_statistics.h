#ifndef ORDINAL_STATISTICS_ORDINAL_STATISTICS_H
#define ORDINAL_STATISTICS_ORDINAL_STATISTICS_H

#include <vector>
#include <algorithm>
#include <exception>
#include <chrono>

#include "utils.h"

// ********************************************** Helpers **************************************************************
template <typename T>
void CheckBoundaries(const std::vector<T>& array, std::size_t i) {
    if (array.empty() || i > array.size() || i < 1) {
        throw std::invalid_argument("Ordinal statistic not in 1..n");
    }
}

template <typename FirstIt, typename LastIt, typename DataType = typename std::iterator_traits<FirstIt>::value_type>
FirstIt ModifiedPartition(FirstIt first, LastIt last, DataType pivot_element) {
    FirstIt right_first = std::partition(first, last, [pivot_element](DataType element) {
//        return element <= pivot_element;
        return element < pivot_element;
    });
//    if (std::distance(first, right_first) == 0) {
//        right_first = std::next(right_first);
//    } else if (std::distance(right_first, last) == 0) {
//        auto max_element_it = std::max_element(first, right_first);
//        if (*std::prev(right_first) != *max_element_it) {
//            std::swap(*std::prev(right_first), *max_element_it);
//        }
//        right_first = std::prev(right_first);
//    }
    return right_first;
}

template <typename FirstIt, typename LastIt>
void InsertionSort(FirstIt first, LastIt last) {
    for (auto i = std::next(first); i < last; i++) {
        for (auto j = i; j > first && *std::prev(j) > *j; j--) {
            std::swap(*std::prev(j), *j);
        }
    }
}

// ****************************************** Naive Select *************************************************************
template <typename T>
std::pair<T, double> NaiveSelect(std::vector<T> array, std::size_t i) {
    CheckBoundaries(array, i);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::sort(array.begin(), array.end());
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();

    return std::make_pair(array.at(static_cast<int>(i) - 1), time);
}

// ***************************************** Randomized Select *********************************************************
template <typename FirstIt, typename LastIt>
FirstIt RandomizedPartition(FirstIt first, LastIt last) {
    FirstIt pivot_it = std::next(first, Random(0, std::distance(first, last) - 1));
    auto first_right = ModifiedPartition(first, last, *pivot_it);
    if (std::distance(first, first_right) == 0) {
        std::swap(*pivot_it, *first_right);
        first_right = std::next(first_right);
    }

    return first_right;
}

template <typename FirstIt, typename LastIt>
FirstIt RecursiveRandomizedSelect(FirstIt first, LastIt last, size_t i) {
    if (std::next(first) == last) {
        return first;
    }

    // Сделать иллюминацию хвостовой рекурсии
    FirstIt right_first_it = RandomizedPartition(first, last);
    int size_left_part = std::distance(first, right_first_it);
    if (i < size_left_part) {
        return RecursiveRandomizedSelect(first, right_first_it, i);
    } else {
        return RecursiveRandomizedSelect(right_first_it, last, i - size_left_part);
    }
}

template <typename T>
std::pair<T, double> RandomizedSelect(std::vector<T> array, std::size_t i) {
    CheckBoundaries(array, i);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    auto result = *(RecursiveRandomizedSelect(array.begin(), array.end(), i - 1));
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();

    return std::make_pair(result, time);
}

// ******************************************* Determined Select *******************************************************
template <typename FirstIt, typename LastIt>
std::vector<std::pair<FirstIt, LastIt>> SplitArray(FirstIt first, LastIt last) {
    auto num_groups = static_cast<size_t>(std::distance(first, last) / 5.0 + 0.9);
    std::vector<std::pair<FirstIt, LastIt>> split(num_groups);

    for (size_t i = 0; i < num_groups; i++) {
        split[i] = {std::next(first, i * 5),
                    std::next(first, std::min((i + 1) * 5, static_cast<size_t>(std::distance(first, last))))};
    }

    return split;
}

template <typename FirstIt, typename LastIt, typename DataType = typename std::iterator_traits<FirstIt>::value_type>
DataType Median(FirstIt first, LastIt last) {
    InsertionSort(first, last);
    return *std::next(first, static_cast<int>(std::distance(first, last) / 2.0 - 0.5));
}

template <typename FirstIt, typename LastIt, typename DataType = typename std::iterator_traits<FirstIt>::value_type>
FirstIt Select(FirstIt first, LastIt last, std::size_t i) {
    if (std::next(first) == last) {
        return first;
    }

    std::vector<DataType> medians;
    auto groups = SplitArray(first, last);
    for (const auto& group: groups) {
        medians.push_back(Median(group.first, group.second));
    }

//    DataType total_median = *Select(medians.begin(), medians.end(), static_cast<size_t>(medians.size() / 2.0 - 0.5));
    FirstIt total_median_it = Select(medians.begin(), medians.end(), static_cast<size_t>(medians.size() / 2.0 - 0.5));
//    FirstIt right_first = ModifiedPartition(first, last, total_median);
    FirstIt right_first = ModifiedPartition(first, last, *total_median_it);
    if (std::distance(first, right_first) == 0) {
        std::swap(*total_median_it, *right_first);
        right_first = std::next(right_first);
    }

    auto size_left_part = static_cast<size_t>(std::distance(first, right_first));
    if (i < size_left_part) {
        return Select(first, right_first, i);
    } else {
        return Select(right_first, last, i - size_left_part);
    }
}

template <typename T>
std::pair<T, double> DeterminedSelect(std::vector<T> array, std::size_t i) {
    CheckBoundaries(array, i);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    auto result = *Select(array.begin(), array.end(), i - 1);
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();

    return std::make_pair(result, time);
}

#endif //ORDINAL_STATISTICS_ORDINAL_STATISTICS_H
