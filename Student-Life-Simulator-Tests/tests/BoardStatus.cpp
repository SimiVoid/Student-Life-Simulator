#include "gtest/gtest.h"

#include "../src/BoardStatus.h"

#include "../src/Examiner.h"
#include "../src/Student.h"

TEST(BoardStatus, BoardStatusClassTest) {
	const int16_t students = 10;
	const uint16_t examiners = 2;
	const uint16_t drunkStudents = 3;

	std::list<std::shared_ptr<Agent>> agents;

	for (auto i = 0; i < students - drunkStudents; i++)
		agents.push_back(std::make_shared<Student>(Student(std::make_pair(0, 100), std::make_pair(0, 100), 10)));

	for (auto i = 0; i < drunkStudents; i++) {
		auto student = Student(std::make_pair(0, 100), std::make_pair(0, 100), 10);
		student.drinkBeer();
		
		agents.push_back(std::make_shared<Student>(student));
	}

	for (auto i = 0; i < examiners; i++)
		agents.push_back(std::make_shared<Examiner>(Examiner(std::make_pair(0, 100), 10)));

	BoardStatus boardStatus(agents);

	ASSERT_EQ(drunkStudents, boardStatus.getDrunkStudentsCount());
	ASSERT_EQ(students, boardStatus.getStudyingStudentsCount());
	ASSERT_EQ(0, boardStatus.getFailedStudentsCount());
	ASSERT_EQ(0, boardStatus.getPassedStudentsCount());
	
}