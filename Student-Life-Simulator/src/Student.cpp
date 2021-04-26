#include "Student.h"

Student::Student(const std::pair<uint16_t, uint16_t>& knowledgeRange, const std::pair<uint16_t, uint16_t>& alcoholResistanceRange, const uint16_t& boardSize)
	: Agent(boardSize), m_status(Status::Studying) {
	m_knowledge = randomNumberWithinRange(knowledgeRange);
	m_alcoholResistance = randomNumberWithinRange(alcoholResistanceRange);

	const float fieldSize = static_cast<float>(1000 / boardSize - 1);

	m_singleView.setSize({ fieldSize, fieldSize });
	m_singleView.setFillColor(sf::Color::Green);

	m_multipleView.setPointCount(3);
	m_multipleView.setPoint(0, { 0, 0 });
	m_multipleView.setPoint(1, { fieldSize, 0 });
	m_multipleView.setPoint(2, { 0, fieldSize });
	m_multipleView.setFillColor(sf::Color::Green);
}

void Student::move(const uint16_t& boardSize) {
	nextRound();

	if (m_isSleeping || m_status != Student::Status::Studying)
		return;

	Agent::move(boardSize);
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

uint16_t Student::getCurrentSemester() const {
	return m_inSemester;
}

Student::Status Student::getStatus() const {
	return m_status;
}

void Student::acceptExamResult(const bool& hasPassed) {
	if (hasPassed)
		m_passedExams++;
	else
		m_failedExams++;

	if (m_passedExams == 4) {
		if (m_inSemester < 7)
			m_inSemester++;
		else
			m_status = Status::Passed;

		m_passedExams = 0;
		m_failedExams = 0;
	}
	else if (m_failedExams == 4) {
		m_status = Status::Failed;
	}
}

void Student::drinkBeer() {
	// If drunk beers count exceeds alcohol resistance student goes to sleep
	if (m_intoxication == m_alcoholResistance) {
		m_isSleeping = true;
		m_intoxication = 0;
		m_roundsWithoutDrinking = 0;

		m_singleView.setFillColor(sf::Color(105, 105, 105));
		m_multipleView.setFillColor(sf::Color(105, 105, 105));
	}
	else {
		m_intoxication++;
		m_roundsWithoutDrinking = 0;

		m_singleView.setFillColor(sf::Color::Yellow);
		m_multipleView.setFillColor(sf::Color::Yellow);
	}
}

void Student::nextRound() {
	if (m_isSleeping) {
		if (m_sleepingRounds == 4) {
			m_isSleeping = false;
			m_sleepingRounds = 0;

			m_multipleView.setFillColor(sf::Color::Green);
			m_singleView.setFillColor(sf::Color::Green);
		}
		else
			m_sleepingRounds++;

		return;
	}

	if (m_roundsWithoutDrinking == 4) {
		m_roundsWithoutDrinking = 0;
		if (m_intoxication != 0) {
			m_intoxication--;
			if (m_intoxication == 0) {
				m_multipleView.setFillColor(sf::Color::Green);
				m_singleView.setFillColor(sf::Color::Green);
			}
		}
	}
	else
		m_roundsWithoutDrinking++;
}
