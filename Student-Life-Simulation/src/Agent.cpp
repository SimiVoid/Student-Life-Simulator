#include "Agent.h"

sf::Vector2i Agent::getPosition() const {
	return m_position;
}

uint16_t Agent::getId() const {
	return m_id;
}

void Agent::draw(sf::RenderWindow windows, bool isSingle = true) {
}

void Agent::move(Board board) {
}