#include "Examiner.h"
#include "Util.h"

Examiner::Examiner(const std::pair<uint16_t, uint16_t> suspicionRange)
	: Agent() {
	m_suspicion = randomNumberWithinRange(suspicionRange);
}

uint16_t Examiner::getSuspicion() const {
	return m_suspicion;
}

void Examiner::examinateStudent(Student* student) {
	// Examiners hate sleeping students...
	if (student->isSleeping()) {
		student->acceptExamResult(false);
	}
	// Sober student always passes an exam
	else if (student->getIntoxication() == 0) {
		student->acceptExamResult(true);
	}
	// Student is drunk
	// Choose a random number between 1 and 100
	// Compare it to m_suspicion which acts as
	// a likeliness of failing an exam
	else if (randomNumberWithinRange(std::make_pair(1, 100)) <= m_suspicion) {
		student->acceptExamResult(false);
	}

	// The chance of drunk student passing an
	// exam is (100 - m_suspicion) %
	student->acceptExamResult(true);
}