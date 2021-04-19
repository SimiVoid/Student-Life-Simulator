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

void Simulation::generateAgents(uint16_t studentsCount, uint16_t examinersCount, uint16_t drunkStudentsCount,
                                std::pair<uint16_t, uint16_t> examinerSuspicionRange,
                                std::pair<uint16_t, uint16_t> studentKnowledgeRange,
                                std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange) {
	Agent* agent;

	studentsCount -= drunkStudentsCount;

	for (; drunkStudentsCount > 0; drunkStudentsCount--) {
		agent = new Student(studentKnowledgeRange, studentAlcoholResistanceRange);
		dynamic_cast<Student*>(agent)->drinkBeer();
		m_agents.push_back(*agent);
	}

	for (; studentsCount > 0; studentsCount--) {
		agent = new Student(studentKnowledgeRange, studentAlcoholResistanceRange);
		m_agents.push_back(*agent);
	}

	for (; examinersCount > 0; examinersCount--) {
		agent = new Examiner(examinerSuspicionRange);
		m_agents.push_back(*agent);
	}
}

void Simulation::updateBoardStatusList() {
	uint16_t studentsOnStudiesCount = 0;
	uint16_t studentsFailedCount = 0;
	uint16_t studentsPassedCount = 0;

	for(auto& agent : m_agents)
		if (typeid(agent).name() == typeid(Student).name())
			switch(dynamic_cast<Student*>(&agent)->getStatus()) {
				case Student::Status::OnStudies:
					studentsOnStudiesCount++;
					break;
				case Student::Status::Failed:
					studentsFailedCount++;
					break;
				case Student::Status::Passed:
					studentsPassedCount++;
					break;
			}

	m_boardStatusList.emplace_back(BoardStatus(studentsOnStudiesCount, studentsFailedCount, studentsPassedCount));
}

Simulation::Simulation(const uint16_t boardSize, const uint16_t studentsCount, const uint16_t examinersCount, const uint16_t drunkStudentsCount,
                       const std::pair<uint16_t, uint16_t> examinerSuspicionRange, 
                       const std::pair<uint16_t, uint16_t> studentKnowledgeRange,
                       const std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange) {

	m_board = new Board(boardSize);

	generateAgents(studentsCount, examinersCount, drunkStudentsCount, examinerSuspicionRange, studentKnowledgeRange, studentAlcoholResistanceRange);

}

Simulation::~Simulation() {
	delete m_board;
}

void Simulation::updateBoard() {
	for (auto& agent : m_agents)
		agent.move(m_board->getBoardSize());

	for (auto& agent : m_agents)
		if (typeid(agent).name() == typeid(Examiner).name()) {
			auto* examiner = dynamic_cast<Examiner*>(&agent);
			const auto position = examiner->getPosition();
			auto agentOnFieldList = m_board->getField(position).getAgentIds();
			
			std::vector<Agent> studentsHandler;

			for (auto& agentHandler : m_agents)
				if (typeid(agent).name() == typeid(Student*).name()
					&& dynamic_cast<Student*>(&agentHandler)->getPosition() == position)
					studentsHandler.emplace_back(agent);

			for (auto& student : studentsHandler)
				examiner->examinateStudent(dynamic_cast<Student*>(&student));
		}

	// TODO: Add students simulation algorithm

	updateBoardStatusList();
}

void Simulation::drawBoard(sf::RenderWindow& window) {
	if (m_board != nullptr)
		m_board->draw(window, m_agents);
}

bool Simulation::checkStatus() {	
	for (auto& agent : m_agents)
		if (typeid(agent).name() == typeid(Student).name() 
			&& dynamic_cast<Student*>(&agent)->getStatus() == Student::Status::OnStudies)
			return true;

	return false;
}

void Simulation::exportData() {
	if(!std::filesystem::is_directory("./output"))
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
