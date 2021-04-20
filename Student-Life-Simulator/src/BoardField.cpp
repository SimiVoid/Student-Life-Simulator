#include "BoardField.h"

#include <utility>

#include "Student.h"
#include "Examiner.h"

BoardField::BoardField(const sf::Vector2i position)
	:m_position(position) {
	m_border.setOutlineThickness(1);
	m_border.setOutlineColor(sf::Color::White);
	
}

std::set<Agent*> BoardField::getAgents() const {
	return m_agentsOnField;
}

sf::Vector2i BoardField::getPosition() const {
	return m_position;
}

void BoardField::setAgents(std::set<Agent*> agents) {
	m_agentsOnField = std::move(agents);
}

void BoardField::draw(sf::RenderWindow& window, const uint16_t boardSize) {
	uint16_t studentsCount = 0;
	uint16_t examinersCount = 0;

	for (const auto& agent : m_agentsOnField) {
			if (typeid(agent).name() == typeid(Student).name())
				studentsCount++;
			else if (typeid(agent).name() == typeid(Examiner).name())
				examinersCount++;
	}
	
	if (studentsCount == 0 && examinersCount == 0)
		return;

	for (const auto& agent : m_agentsOnField) {
		if (studentsCount == 0 || examinersCount == 0)
			agent->draw(window);
		else
			agent->draw(window, false);
	}

	const auto fieldSize = floorf(static_cast<float>(window.getSize().y) / static_cast<float>(boardSize));
	m_border.setSize( sf::Vector2f(fieldSize, fieldSize));
	m_border.setPosition(200.f + boardSize * m_position.x, boardSize * m_position.y);

	window.draw(m_border);
}