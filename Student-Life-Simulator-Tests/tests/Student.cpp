#include "gtest/gtest.h"

#include "../src/Student.h"

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