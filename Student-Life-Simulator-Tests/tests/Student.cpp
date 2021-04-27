#include "gtest/gtest.h"

#include "../src/Student.h"
#include "../src/Agent.h"

TEST(Student, StudentClassTest) {
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	ASSERT_EQ(student.getKnowledge(), 1);
	ASSERT_EQ(student.getAlcoholResistance(), 1);
}

TEST(Student, StudentPassExam) {
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), 1);
	student.acceptExamResult(true);

	ASSERT_EQ(student.getPassedExams(), 1);
	ASSERT_EQ(student.getFailedExams(), 0);
}

TEST(Student, StudentFailExam) {
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), 1);
	student.acceptExamResult(false);

	ASSERT_EQ(student.getFailedExams(), 1);
	ASSERT_EQ(student.getPassedExams(), 0);
}

TEST(Student, StudentIntoxication) {
	int alcoholResistance = 10;
	Student student(std::make_pair(1, 1), std::make_pair(alcoholResistance, alcoholResistance), 10);

	while (alcoholResistance > 0) {
		student.drinkBeer();
		alcoholResistance--;
		ASSERT_EQ(student.getIntoxication(), 10 - alcoholResistance);
		ASSERT_FALSE(student.isSleeping());
	}
}

TEST(Student, StudentSleep) {
	int alcoholResistance = 10;
	Student student(std::make_pair(1, 1), std::make_pair(alcoholResistance, alcoholResistance), 10);

	while (alcoholResistance > 0) {
		student.drinkBeer();
		ASSERT_FALSE(student.isSleeping());
		alcoholResistance--;
	}

	student.drinkBeer();
	ASSERT_TRUE(student.isSleeping());
}

TEST(Student, StudentSleepingMove) {
	int roundsSleeping = 0;
	uint16_t boardSize = 10;
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), boardSize);
	sf::Vector2i position = student.getPosition();

	student.drinkBeer();
	student.drinkBeer();

	while (student.isSleeping() && roundsSleeping < 10 /* prevent infinite loop */) {
		roundsSleeping++;
		ASSERT_EQ(position, student.getPosition());
		student.move(boardSize);
	}

	/* Student is sleeping for 4 rounds
	 * at 5th round isSleeping should change to false
	 * and student position should change
	 */
	ASSERT_EQ(roundsSleeping, 4 + 1);
	ASSERT_NE(position, student.getPosition());
}

TEST(Student, StudentSemester) {
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	for (int i = 1; i < 4 * 7; i++) {
		student.acceptExamResult(true);
		ASSERT_EQ(student.getCurrentSemester() - 1, i / 4);
	}
}

TEST(Student, StudentFail) {
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	for (int i = 1; i <= 4; i++) {
		ASSERT_EQ(student.getCurrentSemester(), 1);
		ASSERT_EQ(student.getStatus(), Student::Status::Studying);
		student.acceptExamResult(false);
	}

	ASSERT_EQ(student.getStatus(), Student::Status::Failed);
}

TEST(Student, StudentFailMove) {
	uint16_t boardSize = 10;
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), boardSize);
	sf::Vector2i position = student.getPosition();

	for (int i = 1; i <= 4; i++) {
		student.acceptExamResult(false);
	}

	student.move(boardSize);
	ASSERT_EQ(position, student.getPosition());
}
TEST(Student, StudentPass) {
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	for (int i = 1; i <= 4 * 7; i++) {
		ASSERT_EQ(student.getStatus(), Student::Status::Studying);
		student.acceptExamResult(true);
	}

	ASSERT_EQ(student.getStatus(), Student::Status::Passed);
}

TEST(Student, StudentPassMove) {
	uint16_t boardSize = 10;
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), boardSize);
	sf::Vector2i position = student.getPosition();

	for (int i = 1; i <= 4 * 7; i++) {
		student.acceptExamResult(true);
	}

	student.move(boardSize);
	ASSERT_EQ(position, student.getPosition());
}

TEST(Student, StudentMove) {
	sf::Vector2i oldPosition;
	uint16_t boardSize = 10;
	Student student(std::make_pair(1, 1), std::make_pair(1, 1), boardSize);

	// Make 1000 randomized moves
	for (int i = 0; i < 1000; i++) {
		oldPosition = student.getPosition();
		student.move(boardSize);
		ASSERT_NE(oldPosition, student.getPosition());
		ASSERT_GE(student.getPosition().x, 0);
		ASSERT_GE(student.getPosition().y, 0);
		ASSERT_LT(student.getPosition().x, boardSize);
		ASSERT_LT(student.getPosition().y, boardSize);
	}
}