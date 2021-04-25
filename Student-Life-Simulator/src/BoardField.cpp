#include "BoardField.h"

#include <utility>

#include "Student.h"
#include "Examiner.h"

BoardField::BoardField(const sf::Vector2i& position)
	:m_position(position) {}

std::set<std::shared_ptr<Agent>> BoardField::getAgents() const {
	return m_agentsOnField;
}

sf::Vector2i BoardField::getPosition() const {
	return m_position;
}

void BoardField::setAgents(std::set<std::shared_ptr<Agent>> agents) {
	m_agentsOnField = std::move(agents);
}

void BoardField::addAgent(const std::shared_ptr<Agent>& agent) {
	m_agentsOnField.insert(agent);
}

void BoardField::clearField() {
	m_agentsOnField.clear();
}

void BoardField::draw(sf::RenderWindow& window, const uint16_t& boardSize) {
	std::shared_ptr<Student> highestPrioStudent = nullptr;
	std::shared_ptr<Examiner> examinerInField = nullptr;

	const float fieldSize = 1000.f / boardSize;
	
	for (const auto& agent : m_agentsOnField) {
		if (isAgentTypeof<Student>(agent)) {
			const auto student = castAgentTo<Student>(agent);
			if (highestPrioStudent == nullptr)
				highestPrioStudent = student;
			else if (student->isSleeping())
				highestPrioStudent = student;
			else if (student->getIntoxication() > 0 && !highestPrioStudent->isSleeping())
				highestPrioStudent = student;
		}
		else if(!examinerInField){
			examinerInField = castAgentTo<Examiner>(agent);
		}
	}
	
	if (highestPrioStudent && examinerInField) {
		highestPrioStudent->draw(window, fieldSize, false);
		examinerInField->draw(window, fieldSize, false);
	}
	else {
		if (highestPrioStudent)
			highestPrioStudent->draw(window, fieldSize);
		else if(examinerInField)
			examinerInField->draw(window, fieldSize);
	}
}