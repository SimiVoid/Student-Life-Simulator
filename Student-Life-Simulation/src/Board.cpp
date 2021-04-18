#include "Board.h"

Board::Board(const uint16_t size)
	:m_size(size) {
}

BoardField Board::getField(const sf::Vector2i position) const {
	for (const auto& field : m_fields)
		if (field.getPosition() == position)
			return field;

	throw std::out_of_range("Error! Cannot find correct field!");
}

uint16_t Board::getBoardSize() const {
	return m_size;
}

void Board::draw(sf::RenderWindow& window, std::list<std::unique_ptr<Agent>> agents) {
}

void Board::updateField(const sf::Vector2i position, const std::list<uint16_t>& agentIds) {
	for (auto& field : m_fields)
		if (field.getPosition() == position)
			field.setAgentIds(agentIds);
}
