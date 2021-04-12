#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <TGUI/TGUI.hpp>
#include <iostream>

#include "Simulation.h"

void setupMenu(tgui::GuiSFML& gui);

int main(int argc, char* argv[]) {
	Simulation* simulation = nullptr;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Student Life Simulator", sf::Style::Close);
	window.setFramerateLimit(60);
	
	tgui::GuiSFML gui(window);

	try {
		setupMenu(gui);
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

void setupMenu(tgui::GuiSFML& gui) {
	gui.setTextSize(15);
	
	auto exitButton = tgui::Button::create("Exit");
	exitButton->setSize(tgui::Layout2d(180, 40));
	exitButton->setPosition(tgui::Layout2d(5, 555));
	gui.add(exitButton);
	
	auto generatePlotButton = tgui::Button::create("Generate plot");
	generatePlotButton->setSize(tgui::Layout2d(180, 40));
	generatePlotButton->setPosition(tgui::Layout2d(5, 505));
	gui.add(generatePlotButton);

	auto exportDataButton = tgui::Button::create("Export Data");
	exportDataButton->setSize(tgui::Layout2d(180, 40));
	exportDataButton->setPosition(tgui::Layout2d(5, 455));
	gui.add(exportDataButton);

	auto startStopButton = tgui::Button::create("Start");
	startStopButton->setSize(tgui::Layout2d(180, 40));
	startStopButton->setPosition(tgui::Layout2d(5, 5));
	gui.add(startStopButton);

	auto boardSizeSliderText = tgui::Label::create("Size: 10");
	boardSizeSliderText->setSize(tgui::Layout2d(160, 20));
	boardSizeSliderText->setPosition(tgui::Layout2d(5, 75));
	boardSizeSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	boardSizeSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(boardSizeSliderText);
	
	auto boardSizeSlider = tgui::Slider::create(10, 100);
	boardSizeSlider->setSize(tgui::Layout2d(160, 20));
	boardSizeSlider->setPosition((tgui::Layout2d(15, 115)));
	boardSizeSlider->setStep(10);
	gui.add(boardSizeSlider);
}