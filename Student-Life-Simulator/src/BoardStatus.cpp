#include "BoardStatus.h"

BoardStatus::BoardStatus(const std::list<std::shared_ptr<Agent>>& agents) : m_noStudentsInSemester(7) {
	for (const auto& agent : agents)
		if (isAgentTypeof<Student>(agent)) {
			const auto student = castAgentTo<Student>(agent);
			switch (student->getStatus()) {
			case Student::Status::Studying:
				m_studyingStudentsCount++;
				m_noStudentsInSemester[student->getCurrentSemester() - 1]++;

				if (student->isSleeping())
					m_sleepingStudentsCount++;
				else if (student->getIntoxication() > 0)
					m_drunkStudentsCount++;
				break;
			case Student::Status::Failed:
				m_failedStudentsCount++;
				break;
			case Student::Status::Passed:
				m_passedStudentsCount++;
				break;
			}
		}
}

const uint16_t& BoardStatus::getStudyingStudentsCount() const {
	return m_studyingStudentsCount;
}

const uint16_t& BoardStatus::getFailedStudentsCount() const {
	return m_failedStudentsCount;
}

const uint16_t& BoardStatus::getPassedStudentsCount() const {
	return m_passedStudentsCount;
}

const uint16_t& BoardStatus::getDrunkStudentsCount() const {
	return m_drunkStudentsCount;
}

const uint16_t& BoardStatus::getSleepingStudentsCount() const {
	return m_sleepingStudentsCount;
}

const std::string BoardStatus::csvExportStudentsInSemester() const {
	std::string tmp{};
	for (const auto& count : m_noStudentsInSemester)
		tmp += std::to_string(count) + ";";

	// Remove semicolon at the end
	tmp.pop_back();

	return tmp;
}