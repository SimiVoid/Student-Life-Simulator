#include "BoardStatus.h"

BoardStatus::BoardStatus(const uint16_t& studentsOnStudiesCount, const uint16_t& studentsFailedCount, const uint16_t& studentPassedCount)
	:m_studentsOnStudiesCount(studentsOnStudiesCount), m_studentsFailedCount(studentsFailedCount), m_studentsPassedCount(studentPassedCount) {

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
