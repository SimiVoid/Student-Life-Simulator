#pragma once

#include <cstdint>

class BoardStatus {
	uint16_t m_studentsOnStudiesCount;
	uint16_t m_studentsFailedCount;
	uint16_t m_studentsPassedCount;

public:
	explicit BoardStatus(uint16_t studentsOnStudiesCount, uint16_t studentsFailedCount, uint16_t studentPassedCount);
	~BoardStatus() = default;

	[[nodiscard]] uint16_t getStudentsOnStudiesCount() const;
	[[nodiscard]] uint16_t getStudentsFailedCount() const;
	[[nodiscard]] uint16_t getStudentsPassedCount() const;
};

