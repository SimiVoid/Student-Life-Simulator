#include "Student.h"

Student::Student(const std::pair<uint16_t, uint16_t> knowledgeRange, const std::pair<uint16_t, uint16_t> alcoholResistanceRange)
	: Agent(), m_status(Status::OnStudies) {
	m_knowledge = randomNumberWithinRange(knowledgeRange);
	m_alcoholResistance = randomNumberWithinRange(alcoholResistanceRange);
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

uint16_t Student::getSleepingRounds() const {
	return m_sleepingRounds;
}

Student::Status Student::getStatus() const {
	return m_status;
}

void Student::failExam() {
	m_failedExams++;
}

void Student::passExam() {
	m_passedExams++;
}

void Student::drinkBeer() {
	// If drunk beers count exceeds alcohol resistance student goes to sleep
	if (m_intoxication == m_alcoholResistance) {
		m_isSleeping = true;
		m_intoxication = 0;
	}
	else
		m_intoxication++;
}

void Student::sleepNextRound() {
	
}

void Student::soberUp() {
	
}
