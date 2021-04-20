#pragma once

#include <utility>
#include <random>

static std::mt19937 generator(std::random_device{}());

template<typename T>
T randomNumberWithinRange(const std::pair<T, T>& range) {
	const std::uniform_int<T> distribution(range.first, range.second);

	return distribution(generator);
}

template<typename T>
T randomNumberWithinRange(const T& first, const T& second) {
	const std::uniform_int<T> distribution(first, second);

	return distribution(generator);
}
