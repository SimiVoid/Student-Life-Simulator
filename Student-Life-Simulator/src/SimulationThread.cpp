#include "SimulationThread.h"

using namespace std::chrono_literals;

std::thread simulationLoopThread;

bool simulationThreadRunning = false;

void runSimulationThread(const std::unique_ptr<Simulation>& simulation) {
	if (simulation == nullptr)
		throw std::exception("Simulation pointer is null!");

	if (simulationThreadRunning)
		throw std::exception("Tried to run simulation while it was running!");

	simulationLoopThread = std::thread([&simulation]() {
		while (1) {
			const auto start = std::chrono::system_clock::now();

			if (simulation->checkStatus()) {
				simulation->updateBoard();
			}
			else {
				simulationThreadRunning = false;
				std::terminate();
			}

			const auto end = std::chrono::system_clock::now();

			std::this_thread::sleep_for(1s - (end - start));
		}
	});

	simulationThreadRunning = true;
}

void stopSimulationThread() {
	simulationThreadRunning = false;

	if (simulationThreadRunning)
		simulationLoopThread.~thread();
}