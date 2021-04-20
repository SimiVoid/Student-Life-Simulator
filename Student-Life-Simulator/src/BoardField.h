#pragma once

#include <SFML/Graphics.hpp>
#include <set>

#include "Agent.h"

class BoardField {
	std::set<Agent*> m_agentsOnField;
	sf::Vector2i m_position;
	sf::RectangleShape m_border;

public:
	explicit BoardField(sf::Vector2i position);
	~BoardField() = default;

	[[nodiscard]] std::set<Agent*> getAgents() const;
	[[nodiscard]] sf::Vector2i getPosition() const;
	void setAgents(std::set<Agent*> agents);
	void draw(sf::RenderWindow& window, uint16_t boardSize);
};
