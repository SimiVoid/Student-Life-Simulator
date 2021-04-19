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
void sliderOnValueChange(std::shared_ptr<tgui::Slider> slider, std::shared_ptr<tgui::EditBox> editBox);
void rangeSliderOnRangeChange(std::shared_ptr<tgui::RangeSlider> rangeSlider, std::shared_ptr<tgui::EditBox> editBoxStart,
	std::shared_ptr<tgui::EditBox> editBoxEnd);
void editBoxOnReturnOrUnfocusRange(std::shared_ptr<tgui::EditBox> editBoxStart, std::shared_ptr<tgui::EditBox> editBoxEnd,
	std::shared_ptr<tgui::RangeSlider> rangeSlider);
void editBoxOnReturnOrUnfocus(std::shared_ptr<tgui::EditBox> editBox, std::shared_ptr<tgui::Slider> slider);