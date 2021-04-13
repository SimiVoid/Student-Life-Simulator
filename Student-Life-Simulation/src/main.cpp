#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <iostream>

#include "Simulation.h"
#include "Menu.h"

int main(int argc, char* argv[]) {
	Simulation* simulation = nullptr;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Student Life Simulator", sf::Style::Close);
	window.setFramerateLimit(60);
	
	tgui::GuiSFML gui(window);

	try {
		setupMenu(gui, window, *simulation);
	}
	catch (const tgui::Exception& e) {
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;

		return 1;
	}

	sf::RectangleShape menuBackground(sf::Vector2f(200, 600));
	menuBackground.setFillColor(sf::Color::White);
	menuBackground.setPosition(0, 0);
	
	//TODO: make gui menu

	//TODO: async window drawing and simulation working

	while(window.isOpen()) {
		sf::Event event{};

		while(window.pollEvent(event)) {
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(menuBackground);
		gui.draw();

		window.display();
	}
	
	delete simulation;
	
	return 0;
}
