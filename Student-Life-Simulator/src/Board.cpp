#include "Board.h"

Board::Board(const uint16_t size)
	:m_size(size) {
	const float fieldSize = (1000 * 1.f) / (m_size);

	for (uint16_t x = 0; x < size; x++) {
		std::vector<BoardField> column;
		for (uint16_t y = 0; y < size; y++) {
			column.emplace_back(BoardField(sf::Vector2i(x, y)));
		}
		m_fields.emplace_back(column);
		
		m_boardGrid.setPrimitiveType(sf::Lines);
		
		// x offset is 200, board size is 1000x1000
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200, x * fieldSize), m_gridColor));
		m_boardGrid.append(sf::Vertex(sf::Vector2f(1200, x * fieldSize), m_gridColor));
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + x * fieldSize, 0), m_gridColor));
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + x * fieldSize , 1000), m_gridColor));
	}
}

void Board::checkFieldPosition(const sf::Vector2i& position) const {
	if (position.x >= m_size || position.y >= m_size ||
		position.x < 0 || position.y < 0)
		throw std::out_of_range("Requested field position out of range!");
}

BoardField& Board::getField(const sf::Vector2i& position) {
	checkFieldPosition(position);

	return m_fields[position.x][position.y];
}

void Board::clearFields() {
	for (auto& columns : m_fields)
		for (auto& field : columns)
			field.clearField();
}

uint16_t Board::getBoardSize() const {
	return m_size;
}

void Board::draw(sf::RenderWindow& window) {
	window.draw(m_boardGrid);

	for (auto& columns : m_fields)
		for (auto& field : columns)
			field.draw(window, m_size);
}

void Board::updateField(const sf::Vector2i& position, const std::set<std::shared_ptr<Agent>>& agents) {
	checkFieldPosition(position);

	m_fields[position.x][position.y].setAgents(agents);
}
