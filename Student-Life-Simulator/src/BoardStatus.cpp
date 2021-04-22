#include "BoardStatus.h"

BoardStatus::BoardStatus(const std::list<std::shared_ptr<Agent>>& agents) : noStudentsInSemester(7) {
	for (auto& agent : agents)
		if (isAgentTypeof<Student>(agent))
			switch (castAgentTo<Student>(agent)->getStatus()) {
			case Student::Status::Studying:
				m_studentsOnStudiesCount++;
				noStudentsInSemester[castAgentTo<Student>(agent)->getCurrentSemester() - 1]++;
				break;
			case Student::Status::Failed:
				m_studentsFailedCount++;
				break;
			case Student::Status::Passed:
				m_studentsPassedCount++;
				break;
			}
}

uint16_t BoardStatus::getStudentsOnStudiesCount() const {
	return m_studentsOnStudiesCount;
}

uint16_t BoardStatus::getStudentsFailedCount() const {
	return m_studentsFailedCount;
}

uint16_t BoardStatus::getStudentsPassedCount() const {
	return m_studentsPassedCount;
}

std::string BoardStatus::csvExportStudentsInSemester() const {
	std::string tmp{};
	for (auto& count : noStudentsInSemester)
		tmp += std::to_string(count) + ";";

	// Remove semicolon at the end
	tmp.pop_back();

	return tmp;
}