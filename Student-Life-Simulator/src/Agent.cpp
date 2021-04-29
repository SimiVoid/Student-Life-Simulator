#include "Agent.h"
#include "Util.h"

uint16_t Agent::idCounter = 0;

Agent::Agent(const uint16_t& boardSize)
	: m_position(randomNumberWithinRange(0, boardSize - 1), randomNumberWithinRange(0, boardSize - 1)) {}

const sf::Vector2i& Agent::getPosition() const {
	return m_position;
}

void Agent::draw(sf::RenderWindow& window, const bool isSingle) {
	if (isSingle)
		window.draw(m_singleView);
	else
		window.draw(m_multipleView);
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

	const float fieldSize = static_cast<float>(1000 / boardSize);
	const float offset = static_cast<float>(1000 % boardSize / 2);
	m_singleView.setPosition(200 + fieldSize * m_position.x + offset, fieldSize * m_position.y + offset);
	m_multipleView.setPosition(200 + fieldSize * m_position.x + offset, fieldSize * m_position.y + offset);
}