#ifndef ORDINAL_STATISTICS_TESTS_H
#define ORDINAL_STATISTICS_TESTS_H

#include <vector>

#include "test_runner.h"
#include "../src/ordinal_statistics.h"

// ********************************************* Naive Select **********************************************************
void naive_select_check_zero_index() {
    try {
        std::vector<int> array = {1, 2, 4};
        NaiveSelect(array, 0);
        ASSERT(false)
    } catch(exception& ex) {
        ASSERT_EQUAL(std::string(ex.what()), std::string("Ordinal statistic not in 1..n"))
    }
}

void naive_select_check_n_index() {
    try {
        std::vector<int> array = {1, 2, 4};
        NaiveSelect(array, 4);
        ASSERT(false)
    } catch(exception& ex) {
        ASSERT_EQUAL(std::string(ex.what()), std::string("Ordinal statistic not in 1..n"))
    }
}

void naive_select_array_without_repetitions() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = NaiveSelect(array, 4).first;

    ASSERT_EQUAL(result, 3)
}

void naive_select_array_with_repetitions() {
    std::vector<int> array = {1, 2, 3, 4, 6, 3, 5, 7, -1, 3};

    int result = NaiveSelect(array, 6).first;

    ASSERT_EQUAL(result, 3)
}

// ********************************************* Randomized Select *****************************************************
void randomized_select_array_without_repetitions() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = RandomizedSelect(array, 4).first;

    ASSERT_EQUAL(result, 3)
}

void randomized_select_array_without_repetitions_two() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = RandomizedSelect(array, 8).first;

    ASSERT_EQUAL(result, 7)
}

void randomized_select_array_without_repetitions_three() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = RandomizedSelect(array, 1).first;

    ASSERT_EQUAL(result, -1)
}

void randomized_select_array_without_repetitions_four() {
    std::vector<int> array = {2, -1};

    int result = RandomizedSelect(array, 1).first;

    ASSERT_EQUAL(result, -1)
}

void randomized_select_array_without_repetitions_five() {
    std::vector<int> array = {2, 3};

    int result = RandomizedSelect(array, 2).first;

    ASSERT_EQUAL(result, 3)
}

void randomized_select_array_with_repetitions() {
    std::vector<int> array = {1, 2, 3, 4, 6, 3, 5, 7, -1, 3};

    int result = RandomizedSelect(array, 6).first;

    ASSERT_EQUAL(result, 3)
}

// ***************************************** Determined Select *********************************************************
void determined_select_split_array() {
    std::vector<int> array = {1, 2, 3, 4, 6, 5, 7, -1, 3};
    auto boundaries = SplitArray(array.begin(), array.end());

    auto first_part = std::vector<int>{boundaries[0].first, boundaries[0].second};
    auto first_true =  std::vector<int>{1, 2, 3, 4, 6};
    auto second_part = std::vector<int>{boundaries[1].first, boundaries[1].second};
    auto second_true =  std::vector<int>{5, 7, -1, 3};

    ASSERT_EQUAL(first_part, first_true)
    ASSERT_EQUAL(second_part, second_true)
    ASSERT_EQUAL(boundaries.size(), 2)
}

void determined_select_split_array_two() {
    std::vector<int> array = {3, 5};
    auto boundaries = SplitArray(array.begin(), array.end());

    auto part = std::vector<int>{boundaries[0].first, boundaries[0].second};
    auto true_part = std::vector<int>{3, 5};

    ASSERT_EQUAL(part, true_part)
    ASSERT_EQUAL(boundaries.size(), 1)
}

void determined_select_split_array_three() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};
    auto boundaries = SplitArray(array.begin(), array.end());

    auto first_part = std::vector<int>{boundaries[0].first, boundaries[0].second};
    auto first_true =  std::vector<int>{1, 2, 4, 6, 3};
    auto second_part = std::vector<int>{boundaries[1].first, boundaries[1].second};
    auto second_true =  std::vector<int>{5, 7, -1};

    ASSERT_EQUAL(first_part, first_true)
    ASSERT_EQUAL(second_part, second_true)
    ASSERT_EQUAL(boundaries.size(), 2)
}

void determined_select_sort_array() {
    std::vector<int> array = {1, 4, 3, 2, 6, 5, 7, -1, 3};
    std::vector<int> sort_array = {-1, 1, 2, 3, 3, 4, 5, 6, 7};

    InsertionSort(array.begin(), array.end());

    ASSERT_EQUAL(array, sort_array)
}

void determined_select_sort_array_two() {
    std::vector<int> array = {};
    std::vector<int> sort_array = {};

    InsertionSort(array.begin(), array.end());

    ASSERT_EQUAL(array, sort_array)
}

void determined_select_sort_array_three() {
    std::vector<int> array = {-1};
    std::vector<int> sort_array = {-1};

    InsertionSort(array.begin(), array.end());

    ASSERT_EQUAL(array, sort_array)
}

void determined_select_median() {
    std::vector<int> array = {1, 4, 7, -1, 3};
    ASSERT_EQUAL(Median(array.begin(), array.end()), 3)
}

void determined_select_median_two() {
    std::vector<int> array = {1, 4, 7, -1};
    ASSERT_EQUAL(Median(array.begin(), array.end()), 1)
}

void determined_select_median_three() {
    std::vector<int> array = {-1};
    ASSERT_EQUAL(Median(array.begin(), array.end()), -1)
}

void determined_select_median_four() {
    std::vector<int> array = {-1, 3};
    ASSERT_EQUAL(Median(array.begin(), array.end()), -1)
}

void determined_select_array_without_repetitions() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = DeterminedSelect(array, 4).first;

    ASSERT_EQUAL(result, 3)
}

void determined_select_array_without_repetitions_two() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = DeterminedSelect(array, 8).first;

    ASSERT_EQUAL(result, 7)
}

void determined_select_array_without_repetitions_three() {
    std::vector<int> array = {1, 2, 4, 6, 3, 5, 7, -1};

    int result = DeterminedSelect(array, 1).first;

    ASSERT_EQUAL(result, -1)
}

void determined_select_array_without_repetitions_four() {
    std::vector<int> array = {2, -1};

    int result = DeterminedSelect(array, 1).first;

    ASSERT_EQUAL(result, -1)
}

void determined_select_array_with_repetitions() {
    std::vector<int> array = {3, 1, 2, 2, 3, 4, 6, 3, 5, 7, -1, 3};

    int result = DeterminedSelect(array, 6).first;

    ASSERT_EQUAL(result, 3)
}

void determined_select_array_with_repetitions_two() {
    std::vector<int> array = {2, 2, 2, 2, 2};

    int result = DeterminedSelect(array, 4).first;

    ASSERT_EQUAL(result, 2)
}

void determined_select_array_with_repetitions_three() {
    std::vector<int> array = {2, 1, 2, 2, 3, 3, 4, 3, 6, 2, 5, 7, 3, -1, 2, 3};

    int result = DeterminedSelect(array, 4).first;

    ASSERT_EQUAL(result, 2)
}

void determined_select_array_with_repetitions_four() {
    std::vector<int> array = {2, 1, 2, 2, 3, 3, 4, 3, 6, 2, 5, 7, 3, -1, 2, 3, 7, 7, 7, 7};

    int result = DeterminedSelect(array, 20).first;

    ASSERT_EQUAL(result, 7)
}

void determined_select_array_with_repetitions_five() {
    std::vector<int> array = {2, 1, 2, -1, 2, 3, 3, -1, 4, 3, 6, 2, -1, 5, 7, 3, -1, 2, 3, 7, 7, 7, 7};

    int result = DeterminedSelect(array, 1).first;

    ASSERT_EQUAL(result, -1)
}

void determined_select_array_with_repetitions_six() {
    std::vector<int> array = {2, 3, 3, 5, 5, 2, 3, 3, 3, 2, 3, 3, 2, 3, 5};

    int result = DeterminedSelect(array, 4).first;

    ASSERT_EQUAL(result, 2)
}

// *********************************************************************************************************************
void RunTests() {
    TestRunner tr;

    RUN_TEST(tr, naive_select_check_zero_index);
    RUN_TEST(tr, naive_select_check_n_index);
    RUN_TEST(tr, naive_select_array_without_repetitions);
    RUN_TEST(tr, naive_select_array_with_repetitions);

    RUN_TEST(tr, randomized_select_array_without_repetitions);
    RUN_TEST(tr, randomized_select_array_without_repetitions_two);
    RUN_TEST(tr, randomized_select_array_without_repetitions_three);
    RUN_TEST(tr, randomized_select_array_without_repetitions_four);
    RUN_TEST(tr, randomized_select_array_without_repetitions_five);
    RUN_TEST(tr, randomized_select_array_with_repetitions);

//    RUN_TEST(tr, determined_select_split_array);
//    RUN_TEST(tr, determined_select_split_array_two);
//    RUN_TEST(tr, determined_select_split_array_three);
    RUN_TEST(tr, determined_select_sort_array);
    RUN_TEST(tr, determined_select_sort_array_two);
    RUN_TEST(tr, determined_select_sort_array_three);
    RUN_TEST(tr, determined_select_median);
    RUN_TEST(tr, determined_select_median_two);
    RUN_TEST(tr, determined_select_median_three);
    RUN_TEST(tr, determined_select_median_four);
    RUN_TEST(tr, determined_select_array_without_repetitions);
    RUN_TEST(tr, determined_select_array_without_repetitions_two);
    RUN_TEST(tr, determined_select_array_without_repetitions_three);
    RUN_TEST(tr, determined_select_array_without_repetitions_four);
    RUN_TEST(tr, determined_select_array_with_repetitions);
    RUN_TEST(tr, determined_select_array_with_repetitions_two);
    RUN_TEST(tr, determined_select_array_with_repetitions_three);
    RUN_TEST(tr, determined_select_array_with_repetitions_four);
    RUN_TEST(tr, determined_select_array_with_repetitions_five);
    RUN_TEST(tr, determined_select_array_with_repetitions_six);
}

#endif //ORDINAL_STATISTICS_TESTS_H
