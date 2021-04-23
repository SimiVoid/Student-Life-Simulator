#pragma once

#include <cstdint>
#include <list>

#include "Student.h"

class BoardStatus {
	uint16_t m_studentsOnStudiesCount = 0;
	uint16_t m_studentsFailedCount = 0;
	uint16_t m_studentsPassedCount = 0;
	std::vector<uint16_t> m_noStudentsInSemester;

public:
	explicit BoardStatus(const std::list<std::shared_ptr<Agent>>& agents);
	~BoardStatus() = default;

	[[nodiscard]] uint16_t getStudentsOnStudiesCount() const;
	[[nodiscard]] uint16_t getStudentsFailedCount() const;
	[[nodiscard]] uint16_t getStudentsPassedCount() const;
	[[nodiscard]] std::string csvExportStudentsInSemester() const;
};