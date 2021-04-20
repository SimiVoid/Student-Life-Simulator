#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <string>
#include <map>
#include <any>

#include "Simulation.h"

void setupMenu(tgui::GuiSFML& gui, sf::RenderWindow& window,  Simulation* simulation);

void exitButtonOnMousePress(sf::RenderWindow& window);
void startButtonOnMousePress(Simulation* simulation, std::function<std::map<std::string, std::any> ()> initParametersList);
void generatePlotButtonOnMousePress(Simulation* simulation);
void exportDataButtonOnMousePress(Simulation* simulation);
void sliderOnValueChange(const std::shared_ptr<tgui::Slider>& slider, const std::shared_ptr<tgui::EditBox>& editBox);
void rangeSliderOnRangeChange(const std::shared_ptr<tgui::RangeSlider>& rangeSlider, const std::shared_ptr<tgui::EditBox>& editBoxStart, const std::shared_ptr<tgui::EditBox>& editBoxEnd);
void editBoxOnReturnOrUnfocusRange(const std::shared_ptr<tgui::EditBox>& editBoxStart, const std::shared_ptr<tgui::EditBox>& editBoxEnd, const std::shared_ptr<tgui::RangeSlider>& rangeSlider);
void editBoxOnReturnOrUnfocus(const std::shared_ptr<tgui::EditBox>& editBox, const std::shared_ptr<tgui::Slider>& slider);
