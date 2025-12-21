#pragma once
#include <vector>
#include <type_traits>
#include <stdexcept>

template<typename T>
T calculateAverageRating(const T* ratings, size_t count) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
    static_assert(!std::is_same_v<T, bool>, "bool is not allowed");

    if (count == 0)
        throw std::invalid_argument("Empty array");

    T sum = T{};
    for (size_t i = 0; i < count; ++i) {
        sum += ratings[i];
    }
    return sum / static_cast<T>(count);
}

template<typename T>
T calculateAverageRating(const std::vector<T>& ratings) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
    static_assert(!std::is_same_v<T, bool>, "bool is not allowed");
    return calculateAverageRating(ratings.data(), ratings.size());
}