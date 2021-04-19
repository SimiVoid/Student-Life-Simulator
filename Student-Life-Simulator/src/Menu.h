#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <any>

#include "Simulation.h"

void setupMenu(tgui::GuiSFML& gui, sf::RenderWindow& window, std::shared_ptr<Simulation>& simulation);

void exitButtonOnMousePress(sf::RenderWindow& window);
void startStopButtonOnMousePress(std::shared_ptr<Simulation>& simulation, std::map<std::string, std::any> initParametersList);
void generatePlotButtonOnMousePress(const std::shared_ptr<Simulation>& simulation);
void exportDataButtonOnMousePress(const std::shared_ptr<Simulation>& simulation);
void sliderOnValueChange(const std::shared_ptr<tgui::Slider>& slider, const std::shared_ptr<tgui::EditBox>& editBox);
void rangeSliderOnRangeChange(const std::shared_ptr<tgui::RangeSlider>& rangeSlider, const std::shared_ptr<tgui::EditBox>& editBoxStart, const std::shared_ptr<tgui::EditBox>& editBoxEnd);
void editBoxOnReturnOrUnfocusRange(const std::shared_ptr<tgui::EditBox>& editBoxStart, const std::shared_ptr<tgui::EditBox>& editBoxEnd, const std::shared_ptr<tgui::RangeSlider>& rangeSlider);
void editBoxOnReturnOrUnfocus(const std::shared_ptr<tgui::EditBox>& editBox, const std::shared_ptr<tgui::Slider>& slider);