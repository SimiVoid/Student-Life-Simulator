#include "gtest/gtest.h"

#include "../src/Simulation.h"
#include "../src/Examiner.h"
#include "../src/Util.h"
TEST(Simulation, SimulationClassTest) {
	/* Board size: 10
	 * Students: 50 (Sober: 40)
	 * Drunk students: 10
	 * Examiners: 30
	 * Suspicion: 1
	 * Knowledge: 2
	 * Alcohol resistance: 3
	 */
	Simulation simulation(10, 50, 30, 10, std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(2, 2), std::make_pair<uint16_t>(3, 3));

	ASSERT_EQ(simulation.getBoard()->getBoardSize(), 10);
	ASSERT_EQ(simulation.getAgents().size(), 50 + 30);

	unsigned examinerCount = 0, studentCount = 0, drunkStudentCount = 0;
	for (const auto& agent : simulation.getAgents()) {
		if (isAgentTypeof<Student>(agent)) {
			const auto student = castAgentTo<Student>(agent);

			if (student->getIntoxication() > 0)
				drunkStudentCount++;

			ASSERT_EQ(student->getAlcoholResistance(), 3);
			ASSERT_EQ(student->getKnowledge(), 2);

			studentCount++;
		}
		if (isAgentTypeof<Examiner>(agent)) {
			ASSERT_EQ(castAgentTo<Examiner>(agent)->getSuspicion(), 1);

			examinerCount++;
		}
	}

	ASSERT_EQ(examinerCount, 30);
	ASSERT_EQ(studentCount, 50);
	ASSERT_EQ(drunkStudentCount, 10);
}

TEST(Simulation, SimulationStatus1) {
	// One sober student, alcohol resist 1
	// A few examiners
	Simulation simulation(2, 1, 5, 0, std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(1, 1));

	std::shared_ptr<Student> student;

	for (const auto& agent : simulation.getAgents()) {
		if (isAgentTypeof<Student>(agent)) {
			student = castAgentTo<Student>(agent);
			break;
		}
	}

	ASSERT_TRUE(simulation.checkStatus());

	// Drunk student
	student->drinkBeer();

	ASSERT_TRUE(simulation.checkStatus());

	// Sleeping student
	student->drinkBeer();

	ASSERT_TRUE(simulation.checkStatus());
}

TEST(Simulation, SimulationStatus2) {
	// One sober student, alcohol resist 1
	// A few examiners
	Simulation simulation(2, 1, 5, 0, std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(1, 1));

	std::shared_ptr<Student> student;

	for (const auto& agent : simulation.getAgents()) {
		if (isAgentTypeof<Student>(agent)) {
			student = castAgentTo<Student>(agent);
			break;
		}
	}

	// Fail student
	while (student->getStatus() != Student::Status::Failed)
	{
		ASSERT_TRUE(simulation.checkStatus());
		student->acceptExamResult(false);
	}

	ASSERT_FALSE(simulation.checkStatus());
}

TEST(Simulation, SimulationStatus3) {
	// One sober student, alcohol resist 1
	// A few examiners
	Simulation simulation(2, 1, 5, 0, std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(1, 1), std::make_pair<uint16_t>(1, 1));

	std::shared_ptr<Student> student;

	for (const auto& agent : simulation.getAgents()) {
		if (isAgentTypeof<Student>(agent)) {
			student = castAgentTo<Student>(agent);
			break;
		}
	}

	// Pass student
	while (student->getStatus() != Student::Status::Passed)
	{
		ASSERT_TRUE(simulation.checkStatus());
		student->acceptExamResult(true);
	}

	ASSERT_FALSE(simulation.checkStatus());
}