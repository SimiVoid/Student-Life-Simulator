#include "Simulation.h"

#include <typeinfo>

#include "Student.h"

void Simulation::generateAgents(uint16_t studentsCount, uint16_t examinersCount,
                                std::pair<uint16_t, uint16_t> examinerSuspicionRange,
                                std::pair<uint16_t, uint16_t> studentKnowledgeRange,
                                std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange) {
	//TODO: generate agents
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
}

void Simulation::drawBoard(sf::RenderWindow& window) {
}

bool Simulation::checkStatus() {
	for (const auto& agent : m_agents)
		if (typeid(agent.get()).name() == typeid(Student*).name() 
			&& dynamic_cast<Student*>(agent.get())->getStatus() == Student::Status::OnStudies)
			return true;

	return false;
}

void Simulation::exportData() {
}

void Simulation::generatePlot() {
}
