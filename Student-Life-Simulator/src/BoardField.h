#pragma once

#include <SFML/Graphics.hpp>
#include <set>

#include "Agent.h"

class BoardField {
	std::set<std::shared_ptr<Agent>> m_agentsOnField;

public:
	explicit BoardField() = default;
	~BoardField() = default;

	[[nodiscard]] std::set<std::shared_ptr<Agent>> getAgents() const;
	void addAgent(const std::shared_ptr<Agent>& agent);
	void clearField();
	void draw(sf::RenderWindow& window);
};
