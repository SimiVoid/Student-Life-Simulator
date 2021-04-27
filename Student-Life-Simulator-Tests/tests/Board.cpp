#include "gtest/gtest.h"

#include "../src/Board.h"

TEST(Board, BoardGetSize) {
	const uint16_t boardSize = 10;
	Board board(boardSize);

	ASSERT_EQ(board.getBoardSize(), boardSize);
}

TEST(Board, BoardSize) {
	ASSERT_THROW(Board board(1), std::invalid_argument);
	ASSERT_THROW(Board board(0), std::invalid_argument);
}

TEST(Board, BoardFieldsRange) {
	const uint16_t boardSize = 10;
	Board board(boardSize);

	ASSERT_NO_THROW(board.getField({ 0,0 }));
	ASSERT_NO_THROW(board.getField({ 9, 9 }));

	ASSERT_THROW(board.getField({ 10, 10 }), std::out_of_range);
	ASSERT_THROW(board.getField({ 0, 10 }), std::out_of_range);
	ASSERT_THROW(board.getField({ 10, 0 }), std::out_of_range);

	ASSERT_THROW(board.getField({ -1, -1 }), std::out_of_range);
	ASSERT_THROW(board.getField({ 0, -1 }), std::out_of_range);
	ASSERT_THROW(board.getField({ -1, 0 }), std::out_of_range);
}

TEST(Board, BoardGetAndSetField) {
	const uint16_t boardSize = 10;
	Board board(boardSize);

	std::shared_ptr<Agent> agent;
	agent = std::make_shared<Agent>(boardSize);
	std::set<std::shared_ptr<Agent>> set{ agent };

	ASSERT_NO_THROW(board.getField({ 0,0 }).addAgent(agent));
	ASSERT_EQ(board.getField({ 0,0 }).getAgents(), set);
}