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
	auto tempPosition = m_position;
	
	do {
		switch (randomNumberWithinRange(std::make_pair<int, int>(1, 8))) {
		case 1:
			tempPosition.y--;
			break;
		case 2:
			tempPosition.y--;
			tempPosition.x++;
			break;
		case 3:
			tempPosition.x++;
			break;
		case 4:
			tempPosition.y++;
			tempPosition.x++;
			break;
		case 5:
			tempPosition.y++;
			break;
		case 6:
			tempPosition.y++;
			tempPosition.x--;
			break;
		case 7:
			tempPosition.x--;
			break;
		case 8:
			tempPosition.x--;
			tempPosition.y--;
			break;
		default:
			break;
		}

		if (tempPosition.x < 0 || tempPosition.x >= boardSize || tempPosition.y < 0 || tempPosition.y >= boardSize)
			inCollision = true;
		
	} while (inCollision);

	m_position = tempPosition;
}