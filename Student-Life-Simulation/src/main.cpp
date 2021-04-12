#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <TGUI/TGUI.hpp>

#include "Simulation.h"

void setupMenu(tgui::GuiSFML& gui);

int main(int argc, char* argv[]) {
	Simulation* simulation = nullptr;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Student Life Simulator", sf::Style::Close);
	window.setFramerateLimit(60);
	
	tgui::GuiSFML gui(window);

	setupMenu(gui);
	
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

		gui.draw();

		window.display();
	}
	
	delete simulation;
	
	return 0;
}

void setupMenu(tgui::GuiSFML& gui) {
	auto exitButton = tgui::Button::create("Exit");
	exitButton->setSize(tgui::Layout2d(180, 40));
	exitButton->setPosition(tgui::Layout2d(5, 555));
	gui.add(exitButton);
}