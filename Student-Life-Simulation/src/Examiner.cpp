#include "Examiner.h"

Examiner::Examiner(std::pair<uint16_t, uint16_t> suspicionRange) {
	m_suspicion = randomNumberWithinRange(suspicionRange);
}

uint16_t Examiner::getSuspicion() const {
	return m_suspicion;
}

void Examiner::examinateStudent(Student &student) {
}