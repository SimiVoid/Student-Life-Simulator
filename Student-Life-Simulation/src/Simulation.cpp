#include "Simulation.h"

void Simulation::generateAgents(uint16_t studentsCount, uint16_t examinersCount) {
	//TODO: generate agents
}

Simulation::Simulation(const uint16_t boardSize, const uint16_t studentsCount, const uint16_t examinersCount) {
	m_board = new Board(boardSize);

	generateAgents(studentsCount, examinersCount);
}

Simulation::~Simulation() {
	delete m_board;
}

void Simulation::updateBoard() {
}

void Simulation::drawBoard(sf::RenderWindow& window) {
}

bool Simulation::checkStatus() {
	//TODO: check true simulation status algorithm 
	
	return false;
}

void Simulation::exportData() {
}

void Simulation::generatePlot() {
}
