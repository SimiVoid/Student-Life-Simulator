#include "Util.h"

#include <random>

template<typename T>
T randomNumberWithinRange(std::pair<T, T> range) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_real<T> distribution(range.first, range.second);
	
	return distribution(generator);
}