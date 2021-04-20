#pragma once

#include <cstdint>

class BoardStatus {
	uint16_t m_studentsOnStudiesCount;
	uint16_t m_studentsFailedCount;
	uint16_t m_studentsPassedCount;

public:
	explicit BoardStatus(const uint16_t& studentsOnStudiesCount, const uint16_t& studentsFailedCount, const uint16_t& studentPassedCount);
	~BoardStatus() = default;

	[[nodiscard]] uint16_t getStudentsOnStudiesCount() const;
	[[nodiscard]] uint16_t getStudentsFailedCount() const;
	[[nodiscard]] uint16_t getStudentsPassedCount() const;
};

