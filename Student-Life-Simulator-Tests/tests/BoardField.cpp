#include "gtest/gtest.h"

#include "../src/BoardField.h"

TEST(BoardField, SetAndReadAgents) {
	BoardField boardField;

	std::set<std::shared_ptr<Agent>> agentsIn = {
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10))
	};

	for (auto& agent : agentsIn)
		boardField.addAgent(agent);

	const auto agentsOut = boardField.getAgents();

	ASSERT_EQ(agentsIn, agentsOut);
}