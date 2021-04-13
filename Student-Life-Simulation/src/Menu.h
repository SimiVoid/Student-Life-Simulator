#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "Simulation.h"

void setupMenu(tgui::GuiSFML& gui, sf::RenderWindow& window, Simulation& simulation);

void exitButtonOnMousePress(sf::RenderWindow& window);
void startStopButtonOnMousePress();
void generatePlotButtonOnMousePress(Simulation* simulation);
void exportDataButtonOnMousePress(Simulation* simulation);
void sliderOnValueChange(std::shared_ptr<tgui::Slider> slider, std::shared_ptr<tgui::Label> sliderText, const std::string& text);