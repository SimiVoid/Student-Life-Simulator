#include "BoardField.h"

#include <utility>

#include "Student.h"
#include "Examiner.h"

BoardField::BoardField(const sf::Vector2i position)
	:m_position(position) {
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

void BoardField::draw(sf::RenderWindow& window) {
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
}