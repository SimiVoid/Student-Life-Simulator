#pragma once

#include <cstdint>

#include "Student.h"
#include "Agent.h"

class Examiner : public Agent {
	uint16_t m_suspicion;

public:
	explicit Examiner(std::pair<uint16_t, uint16_t> suspicionRange);
	~Examiner() = default;
	
	[[nodiscard]] uint16_t getSuspicion() const;
	void examinateStudent(Student &student);
};
