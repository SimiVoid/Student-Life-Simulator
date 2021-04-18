#include "BoardField.h"

#include <utility>

#include "Student.h"
#include "Examiner.h"

BoardField::BoardField(const sf::Vector2i position)
	:m_position(position) {
}

std::list<uint16_t> BoardField::getAgentIds() const {
	return m_agentIds;
}

sf::Vector2i BoardField::getPosition() const {
	return m_position;
}

void BoardField::setAgentIds(std::list<uint16_t> agentIds) {
	m_agentIds = std::move(agentIds);
}

void BoardField::draw(sf::RenderWindow& window, std::list<Agent>& agents) {
	uint16_t studentsCount = 0;
	uint16_t examinersCount = 0;

	std::vector<Agent> agentsList;

	for (const auto& agent : agents)
		for (const auto& agentId : m_agentIds)
			if (agent.getId() == agentId) {
				if (typeid(agent).name() == typeid(Student).name())
					studentsCount++;
				else if (typeid(agent).name() == typeid(Examiner).name())
					examinersCount++;
				break;
			}

	for (auto& agent : agentsList)
		if (examinersCount >= 1 && !studentsCount)
			agent.draw(window);
		else if (!examinersCount && studentsCount >= 1)
			agent.draw(window);
		else if (examinersCount >= 1 && studentsCount >= 1)
			agent.draw(window, false);
}