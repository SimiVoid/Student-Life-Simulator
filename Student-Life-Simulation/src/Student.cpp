#include "Student.h"

Student::Student(){
}

bool Student::isSleeping() const {
	return m_isSleeping;
}

uint16_t Student::getIntoxcination() const {
	return m_intoxcination;
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

StudentStatus Student::getStatus() const {
	return m_status;
}

void Student::failExam() {
	m_failedExams++;
}

void Student::passExam() {
	m_passedExams++;
}

void Student::sleepNextRound() { 
}

void Student::soberUp() {
}
