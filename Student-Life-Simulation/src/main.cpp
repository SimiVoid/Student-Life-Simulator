#include <iostream>
#include <iomanip>

#include <TGUI/TGUI.hpp>

#include "Simulation.h"

int main(int argc, char* argv[]) {
	Simulation* simulation = nullptr;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Student Life Simulator", sf::Style::Close);
	window.setFramerateLimit(60);
	
	tgui::GuiSFML gui(window);
	
	//TODO: make gui menu

	//TODO: async window drawing and simulation working

	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		gui.draw();

		window.display();
	}
	
	delete simulation;
	
	return 0;
}
