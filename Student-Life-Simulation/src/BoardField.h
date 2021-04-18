#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Agent.h"

class BoardField {
	std::list<uint16_t> m_agentIds;
	sf::Vector2i m_position;

public:
	explicit BoardField(sf::Vector2i position);
	~BoardField() = default;

	[[nodiscard]] std::list<uint16_t> getAgentIds() const;
	[[nodiscard]] sf::Vector2i getPosition() const;
	void setAgentIds(std::list<uint16_t> agentIds);
	void draw(sf::RenderWindow& window, std::list<std::unique_ptr<Agent>> agents);
};
