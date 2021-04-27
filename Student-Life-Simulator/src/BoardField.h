#pragma once

#include <SFML/Graphics.hpp>
#include <set>

#include "Agent.h"

class BoardField {
	std::set<std::shared_ptr<Agent>> m_agentsOnField;
	sf::Vector2i m_position;

public:
	explicit BoardField(const sf::Vector2i& position);
	~BoardField() = default;

	[[nodiscard]] std::set<std::shared_ptr<Agent>> getAgents() const;
	[[nodiscard]] sf::Vector2i getPosition() const;
	void setAgents(std::set<std::shared_ptr<Agent>> agents);
	void addAgent(const std::shared_ptr<Agent>& agent);
	void clearField();
	void draw(sf::RenderWindow& window);
};
