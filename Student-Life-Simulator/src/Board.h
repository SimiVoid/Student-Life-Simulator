#pragma once

#include "BoardField.h"

typedef std::vector<std::vector<BoardField>> BoardArray;

class Board {
	BoardArray m_fields;
	uint16_t m_size;
	void checkFieldPosition(const sf::Vector2i& position) const;

public:
	explicit Board(uint16_t size);
	~Board() = default;

	[[nodiscard]] BoardField getField(const sf::Vector2i& position) const;
	[[nodiscard]] uint16_t getBoardSize() const;
	void draw(sf::RenderWindow& window);
	void updateField(sf::Vector2i position, const std::set<Agent*>& agents);
};
