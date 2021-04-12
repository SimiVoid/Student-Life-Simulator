#pragma once

#include <cstdint>
#include <Student.h>

class Examiner
{
	uint16_t m_suspicion;

	public:
		Examiner();
		[[nodiscard]] uint16_t getSuspicion() const;
		void examinateStudent(Student &student);
};

