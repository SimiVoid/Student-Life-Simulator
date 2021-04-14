#pragma once

#include <vector>

#include "BoardStatus.h"
#include "Board.h"

class Simulation {
	std::list<Agent> m_agents;
	std::vector<BoardStatus> m_boardStatusList;

	Board* m_board;

	void generateAgents(uint16_t studentsCount, uint16_t examinersCount,
		std::pair<uint16_t, uint16_t> examinerSuspicionRange,
		std::pair<uint16_t, uint16_t> studentKnowledgeRange,
		std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange);
	
public:
	explicit Simulation(uint16_t boardSize, uint16_t studentsCount, uint16_t examinersCount,
		std::pair<uint16_t, uint16_t> examinerSuspicionRange, 
		std::pair<uint16_t, uint16_t> studentKnowledgeRange,
		std::pair<uint16_t, uint16_t> studentAlcoholResistanceRange);
	~Simulation();

	void updateBoard();
	void drawBoard(sf::RenderWindow& window);
	[[nodiscard]] bool checkStatus();
	void exportData();
	void generatePlot();
};
