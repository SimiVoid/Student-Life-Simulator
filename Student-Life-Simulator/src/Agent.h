#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class Agent {
protected:
	uint16_t m_id;
	sf::Vector2i m_position;
	sf::RectangleShape m_singleView;
	sf::ConvexShape m_multipleView;
	std::string typeInfo;
	
public:
	explicit Agent(const uint16_t& boardSize);
	virtual ~Agent() = default;
		
	static uint16_t idCounter;

	[[nodiscard]] sf::Vector2i getPosition() const;
	[[nodiscard]] uint16_t getId() const;
	[[nodiscard]] std::string getTypeInfo() const;
	void draw(sf::RenderWindow& window, const bool& isSingle = true) const;
	void move(const uint16_t& boardSize);
};
