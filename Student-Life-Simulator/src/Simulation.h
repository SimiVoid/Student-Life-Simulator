#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <memory>

#include "BoardStatus.h"
#include "Board.h"

class Simulation {
	std::list<std::shared_ptr<Agent>> m_agents;
	std::vector<BoardStatus> m_boardStatusList;
	std::unique_ptr<Board> m_board;

	void updateBoardStatusList();
	
public:
	Simulation(const uint16_t& boardSize, uint16_t studentsCount, uint16_t examinersCount, uint16_t drunkStudentsCount,
		const std::pair<uint16_t, uint16_t>& examinerSuspicionRange,
		const std::pair<uint16_t, uint16_t>& studentKnowledgeRange,
		const std::pair<uint16_t, uint16_t>& studentAlcoholResistanceRange);
	Simulation(Simulation&& simulation) noexcept = default;
	Simulation(const Simulation&) = delete;
	Simulation& operator=(const Simulation&) = delete;
	~Simulation() = default;

	void updateBoard();
	void drawBoard(sf::RenderWindow& window) const;
	[[nodiscard]] bool checkStatus() const;
	void exportData() const;
	void generateChart();
	void updateAgentsPosition();
};
