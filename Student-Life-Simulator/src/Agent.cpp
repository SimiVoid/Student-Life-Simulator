#include "Agent.h"
#include "Util.h"

#include <random>

uint16_t Agent::idCounter = 0;

Agent::Agent(const uint16_t& boardSize)
	:m_id(idCounter++) {
	m_position = sf::Vector2i(randomNumberWithinRange<uint16_t>(0, boardSize - 1),
		randomNumberWithinRange<uint16_t>(0, boardSize - 1));	
}

sf::Vector2i Agent::getPosition() const {
	return m_position;
}

uint16_t Agent::getId() const {
	return m_id;
}

void Agent::draw(sf::RenderWindow& window, const float& fieldSize, const bool& isSingle) {
	if (isSingle) {
		m_singleView.setPosition(200 + fieldSize * m_position.x, fieldSize * m_position.y);
		window.draw(m_singleView);
	}
	else {
		m_multipleView.setPosition(200 + fieldSize * m_position.x, fieldSize * m_position.y);
		window.draw(m_multipleView);
	}
}

void Agent::move(const uint16_t& boardSize) {
	/**
	 * Moves table
	 * 1 - Up
	 * 2 - Up-Right
	 * 3 - Right
	 * 4 - Down-Right
	 * 5 - Down
	 * 6 - Down-Left
	 * 7 - Left
	 * 8 - Up-Left
	 */

	sf::Vector2i newPosition;

	do {
		newPosition = m_position;

		switch (randomNumberWithinRange(1, 8)) {
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
			throw std::exception("Moves enum value out of range!");
			break;
		}

	} while (newPosition.x < 0 || newPosition.y < 0 || newPosition.x >= boardSize || newPosition.y >= boardSize);

	m_position = newPosition;
}