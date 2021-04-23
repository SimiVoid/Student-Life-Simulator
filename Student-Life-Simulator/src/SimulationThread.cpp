#include "SimulationThread.h"

void SimulationThread::runSimulationThread(const std::unique_ptr<Simulation>& simulation) {
	if (simulation == nullptr)
		throw std::exception("Simulation pointer is null!");

	if (m_simulationThreadRunning)
		throw std::exception("Tried to run simulation while it was running!");

	m_simulationThreadShouldRun = true;

	m_simulationThread = std::thread([&]() {
		while (m_simulationThreadShouldRun) {
			{
				std::unique_lock<std::mutex> lock(m_pauseMutex);
				m_pauseConditionVariable.wait(lock, [&] {return !m_simulationThreadPaused; });
			}

			const auto start = std::chrono::system_clock::now();

			simulationLock.lock();

			if (!simulation->checkStatus()) {
				// Simulation is finished at this point
				simulation->updateAgentsPosition();
				m_simulationThreadRunning = false;
				simulationLock.unlock();

				m_simulationThread.detach();
				return;
			}

			simulation->updateBoard();
			simulationLock.unlock();

			const auto end = std::chrono::system_clock::now();

			std::this_thread::sleep_for(m_threadWait - (end - start));
		}
	});

	m_simulationThreadRunning = true;
}

void SimulationThread::stopSimulationThread(const bool& sync) {
	if (!m_simulationThreadRunning)
		return;

	m_simulationThreadShouldRun = false;

	if(sync)
		m_simulationThread.join();
	else
		m_simulationThread.detach();

	m_simulationThreadRunning = false;
}

void SimulationThread::pauseSimulationThread() {
	std::lock_guard<std::mutex> lock(m_pauseMutex);
	m_simulationThreadPaused = true;
	m_pauseConditionVariable.notify_all();
}

void SimulationThread::resumeSimulationThread() {
	std::lock_guard<std::mutex> lock(m_pauseMutex);
	m_simulationThreadPaused = false;
	m_pauseConditionVariable.notify_all();
}

void SimulationThread::doSimulationThreadStep() {
	resumeSimulationThread();
	
	// Give simulation thread chance to run
	// This is a dirty hack and could be broken
	std::this_thread::sleep_for(1us);
	
	pauseSimulationThread();
}

void SimulationThread::setSimulationWait(const std::chrono::system_clock::duration& waitTime) {
	m_threadWait = waitTime;
}

std::chrono::system_clock::duration SimulationThread::getSimulationWait() const {
	return m_threadWait;
}

bool SimulationThread::isSimulationRunning() const {
	return m_simulationThreadRunning;
}