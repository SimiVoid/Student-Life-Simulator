#include "Menu.h"

void setupMenu(tgui::GuiSFML& gui, sf::RenderWindow& window, Simulation& simulation) {
	gui.setTextSize(15);

	auto exitButton = tgui::Button::create("Exit");
	exitButton->setSize(tgui::Layout2d(190, 40));
	exitButton->setPosition(tgui::Layout2d(5, 555));
	exitButton->onMousePress(exitButtonOnMousePress, std::ref(window));
	gui.add(exitButton);

	auto generatePlotButton = tgui::Button::create("Generate plot");
	generatePlotButton->setSize(tgui::Layout2d(190, 40));
	generatePlotButton->setPosition(tgui::Layout2d(5, 505));
	gui.add(generatePlotButton);

	auto exportDataButton = tgui::Button::create("Export Data");
	exportDataButton->setSize(tgui::Layout2d(190, 40));
	exportDataButton->setPosition(tgui::Layout2d(5, 455));
	gui.add(exportDataButton);

	auto startStopButton = tgui::Button::create("Start");
	startStopButton->setSize(tgui::Layout2d(190, 40));
	startStopButton->setPosition(tgui::Layout2d(5, 5));
	gui.add(startStopButton);

	auto boardSizeSliderText = tgui::Label::create("Size: 10");
	boardSizeSliderText->setSize(tgui::Layout2d(190, 20));
	boardSizeSliderText->setPosition(tgui::Layout2d(5, 75));
	boardSizeSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	boardSizeSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(boardSizeSliderText);

	auto boardSizeSlider = tgui::Slider::create(10, 100);
	boardSizeSlider->setSize(tgui::Layout2d(170, 20));
	boardSizeSlider->setPosition((tgui::Layout2d(15, 115)));
	boardSizeSlider->setStep(10);
	boardSizeSlider->onValueChange(sliderOnValueChange, boardSizeSlider, boardSizeSliderText, "Size: ");
	gui.add(boardSizeSlider);

	auto studentsCountSliderText = tgui::Label::create("Students count: 1");
	studentsCountSliderText->setSize(tgui::Layout2d(190, 20));
	studentsCountSliderText->setPosition(tgui::Layout2d(5, 175));
	studentsCountSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	studentsCountSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(studentsCountSliderText);

	auto studentsCountSlider = tgui::Slider::create(1, 100);
	studentsCountSlider->setSize(tgui::Layout2d(170, 20));
	studentsCountSlider->setPosition((tgui::Layout2d(15, 215)));
	studentsCountSlider->setStep(1);
	studentsCountSlider->onValueChange(sliderOnValueChange, studentsCountSlider, studentsCountSliderText, "Students count: ");
	gui.add(studentsCountSlider);
}

void exitButtonOnMousePress(sf::RenderWindow& window) {
	window.close();
}

void sliderOnValueChange(std::shared_ptr<tgui::Slider> slider, std::shared_ptr<tgui::Label> sliderText, const std::string& text) {
	sliderText->setText(text + std::to_string(static_cast<uint16_t>(slider->getValue())));
}