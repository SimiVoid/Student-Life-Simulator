#include "Simulation.h"

#include <typeinfo>

#include "Examiner.h"
#include "Student.h"

void Simulation::generateAgents(uint16_t studentsCount, uint16_t examinersCount,
                                std::pair<uint16_t, uint16_t> examinerSuspicionRange,
                                std::pair<uint16_t, uint16_t> studentKnowledgeRange,
                                std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange) {
	//TODO: generate agents
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

Simulation::Simulation(const uint16_t boardSize, const uint16_t studentsCount, const uint16_t examinersCount,
                       const std::pair<uint16_t, uint16_t> examinerSuspicionRange, 
                       const std::pair<uint16_t, uint16_t> studentKnowledgeRange,
                       const std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange) {
	m_board = new Board(boardSize);

	generateAgents(studentsCount, examinersCount, examinerSuspicionRange, studentKnowledgeRange, studentAlcoholResistanceRange);
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
	// TODO: Add exporting data to csv file
}

void Simulation::generatePlot() {
	// TODO: generating plot using
}
