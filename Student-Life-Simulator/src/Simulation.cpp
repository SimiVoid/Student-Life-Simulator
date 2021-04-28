#include "Simulation.h"

#include <sciplot/sciplot.hpp>
#include <fstream>
#include <chrono>
#include <thread>
#include <typeinfo>
#include <filesystem>
#include <exception>
#include <iostream>
#include <sstream>

#include "Examiner.h"
#include "Student.h"

void Simulation::updateBoardStatusList() {
	m_boardStatusList.emplace_back(BoardStatus(m_agents));
}

void Simulation::updateAgentsPosition() {
	m_board->clearFields();
	for (const auto& agent : m_agents) {
		if (isAgentTypeof<Student>(agent) && castAgentTo<Student>(agent)->getStatus() != Student::Status::Studying)
			continue;

		m_board->getField(agent->getPosition()).addAgent(agent);
	}
}

Simulation::Simulation(const uint16_t& boardSize, uint16_t studentsCount, uint16_t examinersCount, uint16_t drunkStudentsCount,
	const std::pair<uint16_t, uint16_t>& examinerSuspicionRange,
	const std::pair<uint16_t, uint16_t>& studentKnowledgeRange,
	const std::pair<uint16_t, uint16_t>& studentAlcoholResistanceRange) {
	m_board = std::make_unique<Board>(boardSize);

	studentsCount -= drunkStudentsCount;

	for (; drunkStudentsCount > 0; drunkStudentsCount--) {
		auto agent = std::make_shared<Student>(Student(studentKnowledgeRange, studentAlcoholResistanceRange, m_board->getBoardSize()));
		agent->drinkBeer();
		m_agents.push_back(agent);
	}

	for (; studentsCount > 0; studentsCount--) {
		auto agent = std::make_shared<Student>(Student(studentKnowledgeRange, studentAlcoholResistanceRange, m_board->getBoardSize()));
		m_agents.push_back(agent);
	}

	for (; examinersCount > 0; examinersCount--) {
		auto agent = std::make_shared<Examiner>(Examiner(examinerSuspicionRange, m_board->getBoardSize()));
		m_agents.push_back(agent);
	}

	// Add epoch 0 to stats
	updateBoardStatusList();

	updateAgentsPosition();
}

void Simulation::updateBoard() {
	for (const auto& agent : m_agents)
		agent->move(m_board->getBoardSize());

	updateAgentsPosition();

	for (uint16_t x = 0; x < m_board->getBoardSize(); x++) {
		for (uint16_t y = 0; y < m_board->getBoardSize(); y++) {
			const auto& agents = m_board->getField({ x, y }).getAgents();
			std::vector<std::shared_ptr<Student>> students;
			std::shared_ptr<Examiner> mainExaminer = nullptr;
			uint16_t minimumKnowledge = 101;
			uint16_t studentsCount = 0;
			bool isEveryStudentSober = true;

			/* Go through all agents in a field and find:
			 * 1. Highest suspicion among all Examiners
			 * 2. Lowest knowledge among all Students
			 */
			for (const auto& agent : agents) {
				if (isAgentTypeof<Examiner>(agent)) {
					const auto& examiner = castAgentTo<Examiner>(agent);
					if (mainExaminer == nullptr || mainExaminer->getSuspicion() < examiner->getSuspicion())
						mainExaminer = examiner;
				}
				else {
					// Agent is typeof Student
					const auto& student = castAgentTo<Student>(agent);
					students.emplace_back(student);

					const auto& minKnowledgeTemp = student->getKnowledge();
					if (minKnowledgeTemp < minimumKnowledge)
						minimumKnowledge = minKnowledgeTemp;

					if (student->getIntoxication() > 0)
						isEveryStudentSober = false;

					studentsCount++;
				}
			}

			/* If there are no examiners on a field students drink;
			 * otherwise, they are being examined and don't drink
			 */
			if (mainExaminer == nullptr) {
				if (!isEveryStudentSober && studentsCount > 1) {
					/* minimumKnowledge is unlikeliness of drinking a beer
					 * so any number above it means they will drink
					 */
					if (randomNumberWithinRange<uint16_t>(1, 100) > minimumKnowledge) {
						for (const auto& student : students)
							student->drinkBeer();
					}
				}
			}
			else {
				for (const auto& student : students)
					mainExaminer->examinateStudent(student);
			}
		}
	}

	updateBoardStatusList();
}

void Simulation::drawBoard(sf::RenderWindow& window) const {
	m_board->draw(window);
}

bool Simulation::checkStatus() const {
	for (const auto& agent : m_agents)
		if (isAgentTypeof<Student>(agent)
			&& castAgentTo<Student>(agent)->getStatus() == Student::Status::Studying)
			return true;

	return false;
}

void Simulation::exportData() const {
	std::thread csvThread([&] {
		if (!std::filesystem::is_directory("./output"))
			std::filesystem::create_directory("./output");

		const auto& now = std::chrono::system_clock::now();
		const auto& inTimeT = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&inTimeT), "%Y-%m-%d_%H-%M-%S_data.csv");
		std::ofstream csvFile("./output/" + ss.str());

		if (!csvFile.good() || !csvFile.is_open())
			throw std::exception("Cannot save csv export!");

		unsigned counter = 0;
		csvFile << "Epoch;Studying;Drunk;Sleeping;Failed;Passed;Sem1;Sem2;Sem3;Sem4;Sem5;Sem6;Sem7" << std::endl;
		for (const auto& record : m_boardStatusList)
			csvFile << counter++ << ";" << record.getStudyingStudentsCount() << ";" << record.getDrunkStudentsCount() <<
			";" << record.getSleepingStudentsCount() << ";" << record.getFailedStudentsCount() <<
			";" << record.getPassedStudentsCount() << ";" << record.csvExportStudentsInSemester() << std::endl;

		csvFile.close();

		std::clog << "File: " << ss.str() << " save" << std::endl;
	});
	csvThread.detach();
}

void Simulation::generateChart() {
	std::thread chartThread([&] {
		using namespace sciplot;

		if (!std::filesystem::is_directory("./output"))
			std::filesystem::create_directories("./output");

		const auto& now = std::chrono::system_clock::now();
		const auto& inTimeT = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&inTimeT), "%Y-%m-%d_%H-%M-%S_chart.pdf");

		Plot chart;
		chart.palette("set2");
		chart.size(800, 600);

		chart.ylabel("Count");
		chart.xlabel("Epoch");
		if (m_boardStatusList[0].getStudyingStudentsCount() < 5)
			chart.ytics().increment(1);
		if (m_boardStatusList.size() < 5)
			chart.xtics().increment(1);
		chart.legend().atOutsideRight();

		const auto& epoch = range(0, m_boardStatusList.size() - 1);

		std::vector<uint16_t> studyingStudents, sleepingStudent, drunkStudents, failedStudents, passedStudents;

		for (const auto& record : m_boardStatusList) {
			failedStudents.emplace_back(record.getFailedStudentsCount());
			passedStudents.emplace_back(record.getPassedStudentsCount());
			studyingStudents.emplace_back(record.getStudyingStudentsCount());
			sleepingStudent.emplace_back(record.getSleepingStudentsCount());
			drunkStudents.emplace_back(record.getDrunkStudentsCount());
		}

		chart.drawCurve(epoch, studyingStudents).label("Studying Students").lineWidth(3);
		chart.drawCurve(epoch, failedStudents).label("Students failed").lineWidth(3);
		chart.drawCurve(epoch, passedStudents).label("Students passed").lineWidth(3);
		chart.drawCurve(epoch, sleepingStudent).label("Sleeping students").lineWidth(3);
		chart.drawCurve(epoch, drunkStudents).label("Drunk students").lineWidth(3);

		chart.save("./output/" + ss.str());
		std::clog << "File: " << ss.str() << " save" << std::endl;

		chart.show();
	});
	chartThread.detach();
}

const std::unique_ptr<Board>& Simulation::getBoard() const {
	return m_board;
}

const AgentsList& Simulation::getAgents() const {
	return m_agents;
}