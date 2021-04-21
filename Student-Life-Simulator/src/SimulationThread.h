#pragma once

#include <chrono>
#include <thread>
#include <mutex>

#include "Simulation.h"

extern std::mutex simulation_lock;

extern bool simulationThreadRunning;

extern void runSimulationThread(const std::unique_ptr<Simulation>& simulation);
extern void stopSimulationThread();