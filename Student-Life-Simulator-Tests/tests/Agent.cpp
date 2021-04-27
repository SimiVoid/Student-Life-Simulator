#include "gtest/gtest.h"

#include "../src/Agent.h"

TEST(Agent, AgentTestClass) {
	Agent agent(1);

	ASSERT_EQ(agent.getPosition(), sf::Vector2i(0, 0));
}