#include "gtest/gtest.h"

#include "../src/BoardField.h"

TEST(BoardField, SetAndReadAgents) {
	BoardField boardField({ 0,0 });

	std::set<std::shared_ptr<Agent>> agentsIn = {
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10)),
		std::make_shared<Agent>(Agent(10))
	};

	boardField.setAgents(agentsIn);

	const auto agentsOut = boardField.getAgents();

	ASSERT_EQ(agentsIn, agentsOut);
}