#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class Agent {
protected:
	sf::Vector2i m_position;

	sf::RectangleShape m_singleView;
	sf::ConvexShape m_multipleView;

public:
	explicit Agent(const uint16_t& boardSize);
	virtual ~Agent() = default;
		
	static uint16_t idCounter;

	[[nodiscard]] const sf::Vector2i& getPosition() const;
	void draw(sf::RenderWindow& window, const bool isSingle = true);
	virtual void move(const uint16_t& boardSize);
};
