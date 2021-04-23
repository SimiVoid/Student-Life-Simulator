#include "Simulation.h"

#include <sciplot/sciplot.hpp>
#include <fstream>
#include <chrono>
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
	for (auto& agent : m_agents)
		agent->move(m_board->getBoardSize());

	updateAgentsPosition();

	for (uint16_t x = 0; x < m_board->getBoardSize(); ++x) {
		for (uint16_t y = 0; y < m_board->getBoardSize(); ++y) {
			const auto& agents = m_board->getField({ x, y }).getAgents();
			std::shared_ptr<Examiner> mainExaminer = nullptr;
			uint16_t minimumKnowledge = 101;
			auto isEveryStudentSober = true;

			/* Go through all agents in a field and find:
			 * 1. Highest suspicion among all Examiners
			 * 2. Lowest knowledge among all Students
			 */
			for (const auto& agent : agents) {
				if (isAgentTypeof<Examiner>(agent)) {
					if (mainExaminer == nullptr || mainExaminer->getSuspicion() < castAgentTo<Examiner>(agent)->getSuspicion())
						mainExaminer = castAgentTo<Examiner>(agent);
				}
				else if (isAgentTypeof<Student>(agent)) {
					auto student = castAgentTo<Student>(agent);

					const auto& minKnowledgeTemp = student->getKnowledge();
					if (minKnowledgeTemp < minimumKnowledge)
						minimumKnowledge = minKnowledgeTemp;

					if (student->getIntoxication() > 0)
						isEveryStudentSober = false;
				}
			}

			/* If there are no examiners on a field students drink;
			 * otherwise, they are being examined and don't drink
			 */
			if (mainExaminer == nullptr) {
				if (!isEveryStudentSober) {
					/* minimumKnowledge is unlikeliness of drinking a beer
					 * so any number above it means they will drink
					 */
					if (randomNumberWithinRange<uint16_t>(1, 100) > minimumKnowledge)
						for (const auto& agent : agents) {
							if (isAgentTypeof<Student>(agent)) {
								castAgentTo<Student>(agent)->drinkBeer();
							}
						}
				}
			}
			else {
				for (auto& agent : agents) {
					if (isAgentTypeof<Student>(agent)) {
						mainExaminer->examinateStudent(castAgentTo<Student>(agent));
					}
				}
			}
		}
	}

	updateBoardStatusList();
}

void Simulation::drawBoard(sf::RenderWindow& window) const {
	if (m_board != nullptr)
		m_board->draw(window);
}

bool Simulation::checkStatus() const {
	for (auto& agent : m_agents)
		if (isAgentTypeof<Student>(agent)
			&& castAgentTo<Student>(agent)->getStatus() == Student::Status::Studying)
			return true;

	return false;
}

void Simulation::exportData() const {
	if (!std::filesystem::is_directory("./output"))
		std::filesystem::create_directories("./output");

	const auto now = std::chrono::system_clock::now();
	auto inTimeT = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&inTimeT), "%Y-%m-%d_%H-%M-%S_data.csv");
	std::ofstream csvFile("./output/" + ss.str());

	if (csvFile.good() && csvFile.is_open()) {
		unsigned counter = 0;
		csvFile << "Epoch;Studying;Drunk;Sleeping;Failed;Passed;Sem1;Sem2;Sem3;Sem4;Sem5;Sem6;Sem7" << std::endl;
		for (auto& record : m_boardStatusList)
			csvFile << counter++ << ";" << record.getStudyingStudentsCount() << ";" << record.getDrunkStudentsCount() <<
					";" << record.getSleepingStudentsCount() << ";" << record.getFailedStudentsCount() <<
					";" << record.getPassedStudentsCount() << ";" << record.csvExportStudentsInSemester() << std::endl;
		csvFile.close();
	}
	else throw std::exception("Error!!! Cannot save data file!!!");

	std::clog << "File: " << ss.str() << " save" << std::endl;
}

void Simulation::generatePlot() {
	using namespace sciplot;

	if (!std::filesystem::is_directory("./output"))
		std::filesystem::create_directories("./output");

	const auto now = std::chrono::system_clock::now();
	auto inTimeT = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&inTimeT), "%Y-%m-%d_%H-%M-%S_plot.pdf");

	// Generating plot algorithm
	Plot plot;
	plot.palette("set2");
	plot.size(800, 600);

	const auto epoch = linspace(0, m_boardStatusList.size(), 1);

	std::vector<uint16_t> studyingStudents, sleepingStudent, drunkStudents, failedStudents, passedStudents;

	for (auto& record : m_boardStatusList) {
		failedStudents.emplace_back(record.getFailedStudentsCount());
		passedStudents.emplace_back(record.getPassedStudentsCount());
		studyingStudents.emplace_back(record.getStudyingStudentsCount());
		sleepingStudent.emplace_back(record.getSleepingStudentsCount());
		drunkStudents.emplace_back(record.getDrunkStudentsCount());
	}
	
	plot.drawBrokenCurve(epoch, studyingStudents).label("Studying Students").lineWidth(4);
	plot.drawBrokenCurve(epoch, passedStudents).label("Students failed").lineWidth(4);
	plot.drawBrokenCurve(epoch, failedStudents).label("Students passed").lineWidth(4);
	plot.drawBrokenCurve(epoch, sleepingStudent).label("Sleeping students").lineWidth(4);
	plot.drawBrokenCurve(epoch, drunkStudents).label("Drunk students").lineWidth(4);

	plot.save("./output/" + ss.str());
	plot.show();
}
