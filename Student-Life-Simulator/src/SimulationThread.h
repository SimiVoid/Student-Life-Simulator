#pragma once

#include <chrono>
#include <thread>
#include <mutex>

#include "Simulation.h"

using namespace std::chrono_literals;

class SimulationThread {
	std::thread m_simulationThread;

	std::condition_variable m_pauseConditionVariable;
	std::mutex m_pauseMutex;

	bool m_simulationThreadPaused{ false };
	std::atomic_bool m_simulationThreadShouldRun;

	std::chrono::system_clock::duration m_threadWait = 1s;

public:
	std::atomic_bool simulationThreadRunning{ false };
	std::mutex simulationLock;

	void runSimulationThread(const std::unique_ptr<Simulation>& simulation);
	void stopSimulationThread(const bool& sync);

	void pauseSimulationThread();
	void resumeSimulationThread();
	void doSimulationThreadStep();

	void setSimulationWait(const std::chrono::system_clock::duration& waitTime);
	std::chrono::system_clock::duration getSimulationWait() const;
};