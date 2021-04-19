#pragma once

#include "Agent.h"
#include "Util.h"

class Student : public Agent
{
public:
	enum class Status {
		OnStudies,
		Failed,
		Passed
	};

private:
	bool m_isSleeping{};
	uint16_t m_intoxication{};
	uint16_t m_knowledge;
	uint16_t m_failedExams{};
	uint16_t m_passedExams{};
	uint16_t m_alcoholResistance;
	uint16_t m_sleepingRounds{};
	Status m_status;

public:
	explicit Student(std::pair<uint16_t, uint16_t> knowledgeRange, std::pair<uint16_t, uint16_t> alcoholResistanceRange);
	~Student() = default;
	
	[[nodiscard]] bool isSleeping() const;
	[[nodiscard]] uint16_t getIntoxication() const;
	[[nodiscard]] uint16_t getKnowledge() const;
	[[nodiscard]] uint16_t getFailedExams() const;
	[[nodiscard]] uint16_t getPassedExams() const;
	[[nodiscard]] uint16_t getAlcoholResistance() const;
	[[nodiscard]] uint16_t getSleepingRounds() const;
	[[nodiscard]] Status getStatus() const;
	void failExam();
	void passExam();
	void drinkBeer();
	void sleepNextRound();
	void soberUp();
};

