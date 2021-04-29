#pragma once

#include "Agent.h"
#include "Util.h"

class Student : public Agent
{
public:
	enum class Status {
		Studying,
		Failed,
		Passed
	};

private:
	bool m_isSleeping{};
	uint16_t m_intoxication{};
	uint16_t m_roundsWithoutDrinking{};
	uint16_t m_knowledge;
	uint16_t m_failedExams{};
	uint16_t m_passedExams{};
	uint16_t m_alcoholResistance;
	uint16_t m_sleepingRounds{};
	uint16_t m_inSemester{ 1 };
	Status m_status;
	
	void nextRound();
public:
	explicit Student(const std::pair<uint16_t, uint16_t>& knowledgeRange, const std::pair<uint16_t, uint16_t>& alcoholResistanceRange, const uint16_t& boardSize);
	~Student() = default;
	
	[[nodiscard]] const bool& isSleeping() const;
	[[nodiscard]] const uint16_t& getIntoxication() const;
	[[nodiscard]] const uint16_t& getKnowledge() const;
	[[nodiscard]] const uint16_t& getFailedExams() const;
	[[nodiscard]] const uint16_t& getPassedExams() const;
	[[nodiscard]] const uint16_t& getAlcoholResistance() const;
	[[nodiscard]] const Status& getStatus() const;
	[[nodiscard]] const uint16_t& getCurrentSemester() const;
	void acceptExamResult(const bool& hasPassed);
	void drinkBeer();
	void move(const uint16_t& boardSize);
};

