#pragma once

#include "BoardField.h"

typedef std::vector<std::vector<BoardField>> BoardArray;

class Board {
	const sf::Color& m_gridColor = sf::Color(41, 41, 41);;
	sf::VertexArray m_boardGrid;

	BoardArray m_fields;
	uint16_t m_size;

	void checkFieldPosition(const sf::Vector2i& position) const;

public:
	explicit Board(uint16_t size);
	~Board() = default;

	[[nodiscard]] BoardField& getField(const sf::Vector2i& position);
	[[nodiscard]] uint16_t getBoardSize() const;
	void draw(sf::RenderWindow& window);
	void clearFields();
};
