#include "Agent.h"
#include "Util.h"

#include <random>

uint16_t Agent::idCounter = 0;

Agent::Agent()
	:m_id(idCounter++) {

}

sf::Vector2i Agent::getPosition() const {
	return m_position;
}

uint16_t Agent::getId() const {
	return m_id;
}

void Agent::draw(sf::RenderWindow& window, const bool isSingle) const {
	if (isSingle)
		window.draw(m_singleView);
	else
		window.draw(m_multipleView);
}

void Agent::move(const uint16_t boardSize) {
	/**
	 * Movment statemant
	 * 1 - Up
	 * 2 - Up-Right
	 * 3 - Right
	 * 4 - Down-Right
	 * 5 - Down
	 * 6 - Down-Left
	 * 7 - Left
	 * 8 - Up-Left
	 */

	auto inCollision = false;
	auto newPosition = m_position;
	
	do {
		switch (randomNumberWithinRange(std::make_pair<int, int>(1, 8))) {
		case 1:
			newPosition.y--;
			break;
		case 2:
			newPosition.y--;
			newPosition.x++;
			break;
		case 3:
			newPosition.x++;
			break;
		case 4:
			newPosition.y++;
			newPosition.x++;
			break;
		case 5:
			newPosition.y++;
			break;
		case 6:
			newPosition.y++;
			newPosition.x--;
			break;
		case 7:
			newPosition.x--;
			break;
		case 8:
			newPosition.x--;
			newPosition.y--;
			break;
		default:
			break;
		}

		if (newPosition.x < 0 || newPosition.x >= boardSize || newPosition.y < 0 || newPosition.y >= boardSize) {
			inCollision = true;
			newPosition = m_position;
		}
		
	} while (inCollision);

	m_position = newPosition;
}