#include "BoardField.h"

#include <utility>

#include "Student.h"
#include "Examiner.h"

BoardField::BoardField(const sf::Vector2i& position)
	:m_position(position) {
	m_border.setOutlineThickness(1);
	m_border.setOutlineColor(sf::Color(31, 31, 31));
	m_border.setFillColor(sf::Color::Black);
}

std::set<std::shared_ptr<Agent>> BoardField::getAgents() const {
	return m_agentsOnField;
}

sf::Vector2i BoardField::getPosition() const {
	return m_position;
}

void BoardField::setAgents(std::set<std::shared_ptr<Agent>> agents) {
	m_agentsOnField = std::move(agents);
}

void BoardField::draw(sf::RenderWindow& window, const uint16_t boardSize) {
	uint16_t studentsCount = 0;
	uint16_t examinersCount = 0;

	const auto fieldSize = floorf(static_cast<float>(window.getSize().y) / static_cast<float>(boardSize));
	
	for (const auto& agent : m_agentsOnField) {
		if (castAgentTo<Student>(agent))
			studentsCount++;
		else if (castAgentTo<Examiner>(agent))
			examinersCount++;
	}
	
	for (auto& agent : m_agentsOnField) {
		if ((studentsCount == 1 && examinersCount == 0) || (studentsCount == 0 && examinersCount == 1))
			agent->draw(window, fieldSize);
		else
			agent->draw(window, fieldSize, false);
	}

	m_border.setSize(sf::Vector2f(fieldSize, fieldSize));
	m_border.setPosition(200.f + fieldSize * m_position.x, fieldSize * m_position.y);

	window.draw(m_border);
}