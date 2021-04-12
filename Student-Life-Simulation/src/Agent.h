#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>

#include "Board.h"

class Agent {
protected:
	uint16_t m_id;
	sf::Vector2i m_position;
	sf::RectangleShape m_singleView;
	sf::ConvexShape m_multipleView;

public:
	static uint16_t idCounter;

	[[nodiscard]] sf::Vector2i getPosition() const;
	[[nodiscard]] uint16_t getId() const;
	void draw(sf::RenderWindow windows, bool isSingle = true);
	void move(Board board);
};

