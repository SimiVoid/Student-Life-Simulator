#include "BoardStatus.h"

BoardStatus::BoardStatus(const std::list<std::shared_ptr<Agent>>& agents) : noStudentsInSemester(7) {
	for (auto& agent : agents)
		if (agent->getTypeInfo() == typeid(Student).name())
			switch (std::dynamic_pointer_cast<Student>(agent)->getStatus()) {
			case Student::Status::Studying:
				m_studentsOnStudiesCount++;
				noStudentsInSemester[std::dynamic_pointer_cast<Student>(agent)->getCurrentSemester() - 1]++;
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
		tmp += count + ",";

	// Remove comma at the end
	tmp.pop_back();

	return tmp;
}