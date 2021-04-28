#pragma once

#include <random>
#include <utility>

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

template<class T1, class T2>
std::shared_ptr<T1> castAgentTo(const std::shared_ptr<T2>& agent) {
	return std::dynamic_pointer_cast<T1>(agent);
}

template<class T1, class T2>
bool isAgentTypeof(const std::shared_ptr<T2>& agent) {
	return std::dynamic_pointer_cast<T1>(agent) != nullptr;
}
