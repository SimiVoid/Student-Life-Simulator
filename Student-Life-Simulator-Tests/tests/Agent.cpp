#include "gtest/gtest.h"

#include "../src/Agent.h"

TEST(Agent, AgentTestClass) {
	Agent agent(1);

	ASSERT_EQ(agent.getPosition(), sf::Vector2i(0, 0));
}

TEST(Agent, AgentMove) {
	sf::Vector2i oldPosition;
	uint16_t boardSize = 3;
	Agent agent(boardSize);

	// Make 1000 randomized moves
	for (int i = 0; i < 1000; i++) {
		oldPosition = agent.getPosition();
		agent.move(boardSize);
		ASSERT_NE(oldPosition, agent.getPosition());
		ASSERT_GE(agent.getPosition().x, 0);
		ASSERT_GE(agent.getPosition().y, 0);
		ASSERT_LT(agent.getPosition().x, boardSize);
		ASSERT_LT(agent.getPosition().y, boardSize);
	}
}