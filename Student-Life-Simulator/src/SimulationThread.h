#pragma once

#include <chrono>
#include <thread>
#include <mutex>

#include "Simulation.h"
#include <functional>

using namespace std::chrono_literals;

class SimulationThread {
	std::thread m_simulationThread;

	std::condition_variable m_pauseConditionVariable;
	std::mutex m_pauseMutex;

	std::atomic_bool m_simulationThreadRunning{ false };
	bool m_simulationThreadPaused{ false };

	std::chrono::system_clock::duration m_threadWait = 1s;

	std::function<void ()> m_finishCallback;

public:
	std::mutex simulationLock;

	void runSimulationThread(const std::unique_ptr<Simulation>& simulation);
	void stopSimulationThread();

	bool isSimulationRunning() const;

	void pauseSimulationThread();
	void resumeSimulationThread();
	void doSimulationThreadStep();

	void setSimulationWait(const std::chrono::system_clock::duration& waitTime);
	std::chrono::system_clock::duration getSimulationWait() const;

	template<typename Func, typename... Targs>
	void setSimulationFinishCallback(const Func& onFinishCallback, const Targs&... args) {
		m_finishCallback = [=] { std::invoke(onFinishCallback, args...); };
	}
};