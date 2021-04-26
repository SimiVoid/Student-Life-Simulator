#include "Examiner.h"
#include "Util.h"

Examiner::Examiner(const std::pair<uint16_t, uint16_t>& suspicionRange, const uint16_t& boardSize)
	: Agent(boardSize) {
	m_suspicion = randomNumberWithinRange(suspicionRange);

	const float fieldSize = static_cast<float>(1000 / boardSize - 1);

	m_singleView.setSize({ fieldSize, fieldSize });
	m_singleView.setFillColor(sf::Color(165, 42, 42));

	m_multipleView.setPointCount(3);
	m_multipleView.setPoint(0, { fieldSize, fieldSize });
	m_multipleView.setPoint(1, { fieldSize, 0 });
	m_multipleView.setPoint(2, { 0, fieldSize });
	m_multipleView.setFillColor(sf::Color(165, 42, 42));
}

uint16_t Examiner::getSuspicion() const {
	return m_suspicion;
}

void Examiner::examinateStudent(std::shared_ptr<Student> student) const {
	// Examiners hate sleeping students...
	if (student->isSleeping()) {
		student->acceptExamResult(false);
		return;
	}

	// Sober student always passes an exam
	if (student->getIntoxication() == 0) {
		student->acceptExamResult(true);
		return;
	}

	/* Student is drunk.
	 * Choose a random number between 1 and 100
	 * Compare it to m_suspicion scaled by ratio
	 * of beers drunk to maximum alcohol resistance
	 */
	if (randomNumberWithinRange<uint16_t>(1, 100) <= m_suspicion * student->getIntoxication() / student->getAlcoholResistance()) {
		student->acceptExamResult(false);
		return;
	}

	/* The chance of drunk student passing an
	 * exam is (100 - suspicion * drunk beers / alcohol resistance) %
	 */
	student->acceptExamResult(true);
}
