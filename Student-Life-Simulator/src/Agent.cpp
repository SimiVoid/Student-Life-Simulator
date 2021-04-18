#include "Agent.h"

#include <random>

uint16_t Agent::idCounter;

Agent::Agent()
	:m_id(idCounter++) {

}

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