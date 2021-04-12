#pragma once

#include <cstdint>

#include "Student.h"
#include "Agent.h"

class Examiner : protected Agent {
	uint16_t m_suspicion;

public:
	Examiner();
	~Examiner() = default;
	
	[[nodiscard]] uint16_t getSuspicion() const;
	void examinateStudent(Student &student);
};
