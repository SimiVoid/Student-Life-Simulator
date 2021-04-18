#include "BoardField.h"

#include <utility>

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
	//TODO: draw agents on this field
}
