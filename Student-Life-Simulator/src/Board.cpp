#include "Board.h"

Board::Board(const uint16_t size)
	:m_size(size) {
	for (uint16_t x = 0; x < size; x++) {
		std::vector<BoardField> column;
		for (uint16_t y = 0; y < size; y++) {
			column.emplace_back(BoardField(sf::Vector2i(x, y)));
		}
		m_fields.emplace_back(column);
	}
}

void Board::checkFieldPosition(const sf::Vector2i& position) const {
	if (position.x >= m_size || position.y >= m_size ||
		position.x < 0 || position.y < 0)
		throw std::out_of_range("Requested field position out of range!");
}

BoardField Board::getField(const sf::Vector2i& position) const {
	checkFieldPosition(position);

	return m_fields[position.x][position.y];
}

uint16_t Board::getBoardSize() const {
	return m_size;
}

void Board::draw(sf::RenderWindow& window) {
	for (auto& columns : m_fields)
		for (auto& field : columns)
			field.draw(window, m_size);
}

void Board::updateField(const sf::Vector2i& position, const std::set<std::shared_ptr<Agent>>& agents) {
	checkFieldPosition(position);

	m_fields[position.x][position.y].setAgents(agents);
}
