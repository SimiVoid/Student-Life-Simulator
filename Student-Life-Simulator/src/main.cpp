#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <iostream>

#include "Simulation.h"
#include "SimulationThread.h"
#include "Menu.h"

int main(int argc, char* argv[]) {
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

		if (simulationThreadRunning)
		{
			auto isLocked = simulationLock.try_lock();
			if (isLocked) {
				simulation->drawBoard(window);
				simulationLock.unlock();
			}
		}

		window.display();
	}

	stopSimulationThread();

	return 0;
}