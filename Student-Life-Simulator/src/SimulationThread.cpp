#include "SimulationThread.h"

using namespace std::chrono_literals;

std::thread simulationLoopThread;
std::mutex simulationLock;

bool simulationThreadRunning = false;

void runSimulationThread(const std::unique_ptr<Simulation>& simulation) {
	if (simulation == nullptr)
		throw std::exception("Simulation pointer is null!");

	if (simulationThreadRunning)
		throw std::exception("Tried to run simulation while it was running!");

	simulationLoopThread = std::thread([&simulation]() {
		while (1) {
			const auto start = std::chrono::system_clock::now();

			simulationLock.lock();

			if (!simulation->checkStatus()) {
				// Simulation is finished at this point
				simulationThreadRunning = false;
				simulationLock.unlock();

				std::terminate();
			}

			simulation->updateBoard();
			simulationLock.unlock();

			const auto end = std::chrono::system_clock::now();

			std::this_thread::sleep_for(1s - (end - start));
		}
	});

	simulationThreadRunning = true;

	simulationLoopThread.detach();
}

void stopSimulationThread() {
	simulationLock.lock();

	if (!simulationThreadRunning)
		goto out;

	simulationLoopThread.~thread();
	simulationThreadRunning = false;

out:
	simulationLock.unlock();
}