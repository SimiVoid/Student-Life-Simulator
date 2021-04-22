#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <filesystem>

#include "Simulation.h"
#include "SimulationThread.h"
#include "Menu.h"

void setupEnvPath();

int main(int argc, char* argv[]) {
	setupEnvPath();
	
	std::unique_ptr<Simulation> simulation;

	sf::RenderWindow window(sf::VideoMode(1200, 1000), "Student Life Simulator", sf::Style::Close);
	window.setFramerateLimit(60);

	tgui::GuiSFML gui(window);

	try {
		setupMenu(gui, window, simulation);
	}
	catch (const tgui::Exception& e) {
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;

		return 1;
	}

	sf::RectangleShape menuBackground(sf::Vector2f(200, 1000));
	menuBackground.setFillColor(sf::Color::White);
	menuBackground.setPosition(0, 0);

	while (window.isOpen()) {
		sf::Event event{};

		while (window.pollEvent(event)) {
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(menuBackground);
		gui.draw();

		auto isLocked = simulationLock.try_lock();
		if (isLocked)
		{
			if (simulationThreadRunning)
				simulation->drawBoard(window);

			simulationLock.unlock();
		}

		window.display();
	}

	stopSimulationThread();

	return 0;
}

void setupEnvPath() {
	auto pathBuffer = new WCHAR[UINT16_MAX];

	GetEnvironmentVariable(L"PATH", pathBuffer, UINT16_MAX);
	
	std::wstring path(pathBuffer);
	std::wstring gnuplotPath = L"\\gnuplot";

	if(path.find(gnuplotPath) != std::wstring::npos) return;
	
	std::wstring currentPath = std::filesystem::current_path().wstring();

	path += currentPath + gnuplotPath;
	
	SetEnvironmentVariable(L"PATH", path.c_str());
}
