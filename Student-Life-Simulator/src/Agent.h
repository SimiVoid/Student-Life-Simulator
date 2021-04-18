#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class Agent {
protected:
	uint16_t m_id;
	sf::Vector2i m_position;
	sf::RectangleShape m_singleView;
	sf::ConvexShape m_multipleView;

public:
	Agent();
	virtual ~Agent() = default;
		
	static uint16_t idCounter;

	[[nodiscard]] sf::Vector2i getPosition() const;
	[[nodiscard]] uint16_t getId() const;
	void draw(sf::RenderWindow windows, bool isSingle = true);
	void move(uint16_t boardSize);
};
