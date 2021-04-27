#include "gtest/gtest.h"

#include "../src/Board.h"

TEST(Board, BoardGetSize) {
	const uint16_t boardSize = 10;
	
	Board board(boardSize);

	ASSERT_EQ(board.getBoardSize(), boardSize);
}