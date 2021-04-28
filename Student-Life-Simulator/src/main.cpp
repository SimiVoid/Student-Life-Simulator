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
sf::Image loadImageFromResource(const std::wstring& name);

int main(int argc, char* argv[]) {
	setupEnvPath();

	std::unique_ptr<Simulation> simulation;
	SimulationThread thread;

	sf::ContextSettings cs;
	cs.antialiasingLevel = 2;
	
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "Student Life Simulator", sf::Style::Close, cs);
	window.setFramerateLimit(60);

	sf::Image icon;

	try {
		icon = loadImageFromResource(L"ICON_PNG");

		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	catch (const std::exception& exception) {
		std::cerr << "Failed to load icon of window: " << exception.what() << std::endl;
	}

	tgui::GuiSFML gui(window);

	try {
		setupMenu(gui, window, simulation, thread);
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

		if (simulation != nullptr) {
			std::unique_lock<std::mutex> lock(thread.simulationLock, std::try_to_lock);
			if (lock)
			{
				window.clear();
				simulation->drawBoard(window);
			}
		}

		window.draw(menuBackground);
		gui.draw();

		window.display();
	}

	thread.stopSimulationThread();

	return 0;
}

void setupEnvPath() {
	const auto pathBuffer = new WCHAR[UINT16_MAX];

	GetEnvironmentVariable(L"PATH", pathBuffer, UINT16_MAX);

	std::wstring path(pathBuffer);
	const std::wstring gnuplotPath = L"\\gnuplot";

	if (path.find(gnuplotPath) != std::wstring::npos) return;

	const auto currentPath = std::filesystem::current_path().wstring();

	path += L";" + currentPath + gnuplotPath;

	SetEnvironmentVariable(L"PATH", path.c_str());
}


sf::Image loadImageFromResource(const std::wstring& name)
{
	const auto rsrcData = FindResource(nullptr, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	const auto rsrcDataSize = SizeofResource(nullptr, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	const auto grsrcData = LoadResource(nullptr, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	const auto firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Image image;
	if (!image.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load image from memory.");

	return image;
}