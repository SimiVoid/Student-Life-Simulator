#pragma once

#include <list>
#include "BoardField.h"

class Board {
	std::list<BoardField> m_fields;
	uint16_t m_size;

public:
	explicit Board(uint16_t size);
	~Board() = default;

	[[nodiscard]] BoardField getField(sf::Vector2i position) const;
	[[nodiscard]] uint16_t getBoardSize() const;
	void draw(sf::RenderWindow& window);
	void updateField(sf::Vector2i position, const std::set<Agent*>& agents);
};
