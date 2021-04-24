#pragma once

#include <cstdint>
#include <list>

#include "Student.h"

class BoardStatus {
	uint16_t m_studyingStudentsCount{ 0 };
	uint16_t m_drunkStudentsCount{ 0 };
	uint16_t m_sleepingStudentsCount{ 0 };
	uint16_t m_failedStudentsCount{ 0 };
	uint16_t m_passedStudentsCount{ 0 };
	std::vector<uint16_t> m_noStudentsInSemester;

public:
	explicit BoardStatus(const std::list<std::shared_ptr<Agent>>& agents);
	~BoardStatus() = default;

	[[nodiscard]] const uint16_t& getStudyingStudentsCount() const;
	[[nodiscard]] const uint16_t& getDrunkStudentsCount() const;
	[[nodiscard]] const uint16_t& getSleepingStudentsCount() const;
	[[nodiscard]] const uint16_t& getFailedStudentsCount() const;
	[[nodiscard]] const uint16_t& getPassedStudentsCount() const;
	[[nodiscard]] const std::string csvExportStudentsInSemester() const;
};