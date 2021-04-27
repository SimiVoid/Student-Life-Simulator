#include "gtest/gtest.h"

#include "../src/Board.h"

TEST(Board, BoardGetSize) {
	const uint16_t boardSize = 10;
	
	Board board(boardSize);

	ASSERT_EQ(board.getBoardSize(), boardSize);
}

TEST(Board, BoardGetField) {
	const uint16_t boardSize = 1;

	Board board(1);
	const std::set < std::shared_ptr<Agent>> agents{ std::make_shared<Agent>(Agent(1)) };

	board.getField({ 0, 0 }).setAgents(agents);
	
	ASSERT_EQ(board.getField({ 0, 0 }).getAgents(), agents);
}