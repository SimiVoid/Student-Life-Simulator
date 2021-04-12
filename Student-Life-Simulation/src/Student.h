#pragma once

#include <cstdint>

enum class StudentStatus {
	OnStudies,
	Failed,
	Passed
};

class Student
{
	bool m_isSleeping;
	uint16_t m_intoxcination;
	uint16_t m_knowledge;
	uint16_t m_failedExams;
	uint16_t m_passedExams;
	uint16_t m_alcoholResistance;
	uint16_t m_sleepingRounds;
	StudentStatus m_status;

	public:
		Student();
		[[nodiscard]] bool isSleeping() const;
		[[nodiscard]] uint16_t getIntoxcination() const;
		[[nodiscard]] uint16_t getKnowledge() const;
		[[nodiscard]] uint16_t getFailedExams() const;
		[[nodiscard]] uint16_t getPassedExams() const;
		[[nodiscard]] uint16_t getAlcoholResistance() const;
		[[nodiscard]] uint16_t getSleepingRounds() const;
		[[nodiscard]] StudentStatus getStatus() const;
		void failExam();
		void passExam();
		void sleepNextRound();
		void soberUp();
};

