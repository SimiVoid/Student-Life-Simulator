#include "BoardStatus.h"

BoardStatus::BoardStatus(const std::list<std::shared_ptr<Agent>>& agents) {
	for (auto& agent : agents)
		if (typeid(agent).name() == typeid(Student).name())
			switch (std::dynamic_pointer_cast<Student>(agent)->getStatus()) {
			case Student::Status::OnStudies:
				m_studentsOnStudiesCount++;
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
