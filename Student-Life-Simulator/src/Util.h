#pragma once

#include <utility>
#include <random>

template<typename T>
T randomNumberWithinRange(std::pair<T, T> range) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	const std::uniform_real<> distribution(range.first, range.second);

	return static_cast<T>(distribution(generator));
}

template<typename T>
T randomNumberWithinRange(const T& first, const T& second) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	const std::uniform_real<> distribution(first, second);

	return static_cast<T>(distribution(generator));
}
