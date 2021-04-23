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
	uint16_t studentsCount = 0;
	uint16_t examinersCount = 0;

	const float fieldSize = 1000.f / boardSize;
	
	for (const auto& agent : m_agentsOnField) {
		if (castAgentTo<Student>(agent))
			studentsCount++;
		else if (castAgentTo<Examiner>(agent))
			examinersCount++;
	}
	
	for (auto& agent : m_agentsOnField) {
		if (studentsCount >= 1 && examinersCount >= 1)
			agent->draw(window, fieldSize, false);
		else
			agent->draw(window, fieldSize);
	}
}