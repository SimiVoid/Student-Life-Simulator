#include "gtest/gtest.h"

#include "../src/Examiner.h"
#include "../src/Student.h"

TEST(Examiner, ExaminerClassTest) {
	Examiner examiner(std::make_pair(1, 1), 1);
	
	ASSERT_EQ(examiner.getSuspicion(), 1);	
}

TEST(Examiner, ExaminerPassSober) {
	Examiner examiner(std::make_pair(100, 100), 1);
	std::shared_ptr<Student> student;
	student = std::make_shared<Student>(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	examiner.examinateStudent(student);

	ASSERT_EQ(student->getPassedExams(), 1);
	ASSERT_EQ(student->getFailedExams(), 0);
}

TEST(Examiner, ExaminerFailDrunk) {
	Examiner examiner(std::make_pair(100, 100), 1);
	std::shared_ptr<Student> student;
	student = std::make_shared<Student>(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	student->drinkBeer();
	examiner.examinateStudent(student);

	ASSERT_EQ(student->getPassedExams(), 0);
	ASSERT_EQ(student->getFailedExams(), 1);
}

TEST(Examiner, ExaminerFailSleeping) {
	Examiner examiner(std::make_pair(100, 100), 1);
	std::shared_ptr<Student> student;
	student = std::make_shared<Student>(std::make_pair(1, 1), std::make_pair(1, 1), 1);

	student->drinkBeer();
	student->drinkBeer();
	examiner.examinateStudent(student);

	ASSERT_EQ(student->getPassedExams(), 0);
	ASSERT_EQ(student->getFailedExams(), 1);
}