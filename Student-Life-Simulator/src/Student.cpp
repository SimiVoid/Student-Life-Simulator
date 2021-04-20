#include "Student.h"

Student::Student(const std::pair<uint16_t, uint16_t> knowledgeRange, const std::pair<uint16_t, uint16_t> alcoholResistanceRange, uint16_t boardSize)
	: Agent(boardSize), m_status(Status::OnStudies) {
	m_knowledge = randomNumberWithinRange(knowledgeRange);
	m_alcoholResistance = randomNumberWithinRange(alcoholResistanceRange);

	// TODO: setup drawable elements (Student)
}

bool Student::isSleeping() const {
	return m_isSleeping;
}

uint16_t Student::getIntoxication() const {
	return m_intoxication;
}

uint16_t Student::getKnowledge() const {
	return m_knowledge;
}

uint16_t Student::getFailedExams() const {
	return m_failedExams;
}

uint16_t Student::getPassedExams() const {
	return m_passedExams;
}

uint16_t Student::getAlcoholResistance() const {
	return m_alcoholResistance;
}

Student::Status Student::getStatus() const {
	return m_status;
}

void Student::acceptExamResult(const bool hasPassed) {
	if (hasPassed)
		m_passedExams++;
	else
		m_failedExams++;
}

void Student::drinkBeer() {
	// If drunk beers count exceeds alcohol resistance student goes to sleep
	if (m_intoxication == m_alcoholResistance) {
		m_isSleeping = true;
		m_intoxication = 0;
		m_roundsWithoutDrinking = 0;
	}
	else {
		m_intoxication++;
		m_roundsWithoutDrinking = 0;
	}
}

void Student::nextRound() {
	if (m_isSleeping) {
		if (m_sleepingRounds == 4) {
			m_isSleeping = false;
			m_sleepingRounds = 0;
		}
		else
			m_sleepingRounds++;

		return;
	}

	if (m_roundsWithoutDrinking == 4) {
		m_roundsWithoutDrinking = 0;
		if (m_intoxication != 0)
			m_intoxication--;
	}
	else
		m_roundsWithoutDrinking++;
}
