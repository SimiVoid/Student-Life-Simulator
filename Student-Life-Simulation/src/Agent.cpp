#include "Agent.h"

uint16_t Agent::idCounter = 0;

sf::Vector2i Agent::getPosition() const {
	return m_position;
}

uint16_t Agent::getId() const {
	return m_id;
}

void Agent::draw(sf::RenderWindow windows, bool isSingle) {
}

void Agent::move(uint16_t boardSize) {
}