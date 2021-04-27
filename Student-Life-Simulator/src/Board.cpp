#include "Board.h"

Board::Board(const uint16_t size)
	:m_size(size) {
	if (m_size < 2)
		throw std::invalid_argument("Board size must be at least 2");

	const float fieldSize = static_cast<float>(1000 / m_size);
	const float offset = static_cast<float>(1000 % m_size / 2);

	m_boardGrid.setPrimitiveType(sf::Lines);

	for (uint16_t x = 0; x < size; x++) {
		std::vector<BoardField> column;
		for (uint16_t y = 0; y < size; y++) {
			column.emplace_back(BoardField());
		}
		m_fields.emplace_back(column);

		// x offset is 200
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + offset, x * fieldSize + offset), m_gridColor));
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + fieldSize * size + offset, x * fieldSize + offset), m_gridColor));
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + x * fieldSize + offset, offset), m_gridColor));
		m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + x * fieldSize + offset, fieldSize * size + offset), m_gridColor));
	}

	m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + offset, size * fieldSize + offset), m_gridColor));
	m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + fieldSize * size + offset, size * fieldSize + offset), m_gridColor));
	m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + size * fieldSize + offset, 0 + offset), m_gridColor));
	m_boardGrid.append(sf::Vertex(sf::Vector2f(200 + size * fieldSize + offset, fieldSize * size + offset), m_gridColor));
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


	for (auto& columns : m_fields)
		for (auto& field : columns)
			field.draw(window);
	window.draw(m_boardGrid);
}
