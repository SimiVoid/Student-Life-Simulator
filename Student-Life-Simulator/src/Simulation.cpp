#include "Simulation.h"

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

}

Simulation::Simulation(Simulation&&) noexcept {
	
}

void Simulation::updateBoard() {
	for (auto& agent : m_agents)
		agent->move(m_board->getBoardSize());

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
				if (typeid(agent).name() == typeid(Examiner).name()) {
					if (mainExaminer == nullptr || mainExaminer->getSuspicion() < std::dynamic_pointer_cast<Examiner>(agent)->getSuspicion())
						mainExaminer = std::dynamic_pointer_cast<Examiner>(agent);
				}
				else if (typeid(agent).name() == typeid(Student).name()) {
					auto student = std::dynamic_pointer_cast<Student>(agent);

					// Inform each student about a new round
					student->nextRound();

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
							if (typeid(agent).name() == typeid(Student*).name()) {
								std::dynamic_pointer_cast<Student>(agent)->drinkBeer();
							}
						}
				}
			}
			else {
				for (auto& agent : agents) {
					if (typeid(agent).name() == typeid(Student*).name()) {
						mainExaminer->examinateStudent(std::dynamic_pointer_cast<Student>(agent));
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
		if (typeid(agent).name() == typeid(Student).name()
			&& std::dynamic_pointer_cast<Student>(agent)->getStatus() == Student::Status::OnStudies)
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
		for (auto& record : m_boardStatusList)
			csvFile << record.getStudentsOnStudiesCount() << "," << record.getStudentsFailedCount() << "," << record.getStudentsPassedCount() << std::endl;
		csvFile.close();
	}
	else throw std::exception("Error!!! Cannot save data file!!!");

	std::clog << "File: " << ss.str() << " save" << std::endl;
}

void Simulation::generatePlot() {
	// TODO: generating plot algorithm
}
