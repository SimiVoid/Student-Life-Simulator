#include "gtest/gtest.h"

#include "../src/BoardField.h"

TEST(BoardField, SetAndReadAgents) {
	BoardField boardField;

	std::vector<std::shared_ptr<Agent>> agentsIn = {
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

	boardField.clearField();
}

TEST(BoardField, SetAndClearAgents) {
	BoardField boardField;

	std::vector<std::shared_ptr<Agent>> emptySet = {};
	std::vector<std::shared_ptr<Agent>> agentsIn = {
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10))
	};

	for (auto& agent : agentsIn)
		boardField.addAgent(agent);

	boardField.clearField();

	const auto agentsOut = boardField.getAgents();

	ASSERT_EQ(agentsOut, emptySet);
}