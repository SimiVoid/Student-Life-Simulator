#include "BoardField.h"

#include <utility>

#include "Student.h"
#include "Examiner.h"

std::set<std::shared_ptr<Agent>> BoardField::getAgents() const {
	return m_agentsOnField;
}

void BoardField::addAgent(const std::shared_ptr<Agent>& agent) {
	m_agentsOnField.insert(agent);
}

void BoardField::clearField() {
	m_agentsOnField.clear();
}

void BoardField::draw(sf::RenderWindow& window) {
	std::shared_ptr<Student> highestPrioStudent = nullptr;
	std::shared_ptr<Examiner> examinerInField = nullptr;
	
	for (const auto& agent : m_agentsOnField) {
		if (isAgentTypeof<Student>(agent)) {
			const auto student = castAgentTo<Student>(agent);
			if (highestPrioStudent == nullptr)
				highestPrioStudent = student;
			else if (student->isSleeping())
				highestPrioStudent = student;
			else if (student->getIntoxication() > 0 && !highestPrioStudent->isSleeping())
				highestPrioStudent = student;
		}
		else if(!examinerInField){
			examinerInField = castAgentTo<Examiner>(agent);
		}
	}
	
	if (highestPrioStudent && examinerInField) {
		highestPrioStudent->draw(window, false);
		examinerInField->draw(window, false);
	}
	else {
		if (highestPrioStudent)
			highestPrioStudent->draw(window);
		else if(examinerInField)
			examinerInField->draw(window);
	}
}