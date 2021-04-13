#include "Menu.h"

void setupMenu(tgui::GuiSFML& gui, sf::RenderWindow& window, Simulation& simulation) {
	gui.setTextSize(15);

	auto exitButton = tgui::Button::create("Exit");
	exitButton->setSize(tgui::Layout2d(190, 40));
	exitButton->setPosition(tgui::Layout2d(5, 955));
	exitButton->onMousePress(exitButtonOnMousePress, std::ref(window));
	gui.add(exitButton);

	auto generatePlotButton = tgui::Button::create("Generate plot");
	generatePlotButton->setSize(tgui::Layout2d(190, 40));
	generatePlotButton->setPosition(tgui::Layout2d(5, 905));
	generatePlotButton->onMousePress(generatePlotButtonOnMousePress, &simulation);
	gui.add(generatePlotButton);

	auto exportDataButton = tgui::Button::create("Export Data");
	exportDataButton->setSize(tgui::Layout2d(190, 40));
	exportDataButton->setPosition(tgui::Layout2d(5, 855));
	exportDataButton->onMousePress(exportDataButtonOnMousePress, &simulation);
	gui.add(exportDataButton);

	auto startStopButton = tgui::Button::create("Start");
	startStopButton->setSize(tgui::Layout2d(190, 40));
	startStopButton->setPosition(tgui::Layout2d(5, 5));
	startStopButton->onMousePress(startStopButtonOnMousePress);
	gui.add(startStopButton);

	auto boardSizeSliderText = tgui::Label::create("Size: 10");
	boardSizeSliderText->setSize(tgui::Layout2d(190, 20));
	boardSizeSliderText->setPosition(tgui::Layout2d(5, 55));
	boardSizeSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	boardSizeSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(boardSizeSliderText);

	auto boardSizeSlider = tgui::Slider::create(10, 100);
	boardSizeSlider->setSize(tgui::Layout2d(170, 20));
	boardSizeSlider->setPosition((tgui::Layout2d(15, 85)));
	boardSizeSlider->setStep(10);
	boardSizeSlider->onValueChange(sliderOnValueChange, boardSizeSlider, boardSizeSliderText, "Size: ");
	gui.add(boardSizeSlider);

	auto studentsCountSliderText = tgui::Label::create("Students: 1");
	studentsCountSliderText->setSize(tgui::Layout2d(190, 20));
	studentsCountSliderText->setPosition(tgui::Layout2d(5, 135));
	studentsCountSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	studentsCountSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(studentsCountSliderText);

	auto studentsCountSlider = tgui::Slider::create(1, 100);
	studentsCountSlider->setSize(tgui::Layout2d(170, 20));
	studentsCountSlider->setPosition((tgui::Layout2d(15, 165)));
	studentsCountSlider->setStep(1);
	studentsCountSlider->onValueChange(sliderOnValueChange, studentsCountSlider, studentsCountSliderText, "Students: ");
	gui.add(studentsCountSlider);

	auto examinersCountSliderText = tgui::Label::create("Examiners: 1");
	examinersCountSliderText->setSize(tgui::Layout2d(190, 20));
	examinersCountSliderText->setPosition(tgui::Layout2d(5, 215));
	examinersCountSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	examinersCountSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(examinersCountSliderText);

	auto examinersCountSlider = tgui::Slider::create(1, 100);
	examinersCountSlider->setSize(tgui::Layout2d(170, 20));
	examinersCountSlider->setPosition((tgui::Layout2d(15, 245)));
	examinersCountSlider->setStep(1);
	examinersCountSlider->onValueChange(sliderOnValueChange, examinersCountSlider, examinersCountSliderText, "Examiners: ");
	gui.add(examinersCountSlider);

	auto drunkStudentsCountSliderText = tgui::Label::create("Drunk students: 1");
	drunkStudentsCountSliderText->setSize(tgui::Layout2d(190, 20));
	drunkStudentsCountSliderText->setPosition(tgui::Layout2d(5, 295));
	drunkStudentsCountSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	drunkStudentsCountSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(drunkStudentsCountSliderText);

	auto drunkStudentsCountSlider = tgui::Slider::create(1, 100);
	drunkStudentsCountSlider->setSize(tgui::Layout2d(170, 20));
	drunkStudentsCountSlider->setPosition((tgui::Layout2d(15, 325)));
	drunkStudentsCountSlider->setStep(1);
	drunkStudentsCountSlider->onValueChange(sliderOnValueChange, drunkStudentsCountSlider, drunkStudentsCountSliderText, "Drunk students: ");
	gui.add(drunkStudentsCountSlider);

	auto studentKnowledgeRangeSliderText = tgui::Label::create("Students knowledge:\n1 - 100");
	studentKnowledgeRangeSliderText->setSize(tgui::Layout2d(190, 40));
	studentKnowledgeRangeSliderText->setPosition(tgui::Layout2d(5, 375));
	studentKnowledgeRangeSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	studentKnowledgeRangeSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(studentKnowledgeRangeSliderText);

	auto studentKnowledgeRangeSlider = tgui::RangeSlider::create(1, 100);
	studentKnowledgeRangeSlider->setSize(tgui::Layout2d(170, 20));
	studentKnowledgeRangeSlider->setPosition((tgui::Layout2d(15, 425)));
	studentKnowledgeRangeSlider->setStep(1);
	studentKnowledgeRangeSlider->setSelectionEnd(100);
	studentKnowledgeRangeSlider->onRangeChange(rangeSliderOnRangeChange, studentKnowledgeRangeSlider, studentKnowledgeRangeSliderText, "Students knowledge:\n");
	gui.add(studentKnowledgeRangeSlider);

	auto studentAlcoholResistanceRangeSliderText = tgui::Label::create("Alcohol resistance:\n1 - 100");
	studentAlcoholResistanceRangeSliderText->setSize(tgui::Layout2d(190, 40));
	studentAlcoholResistanceRangeSliderText->setPosition(tgui::Layout2d(5, 475));
	studentAlcoholResistanceRangeSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	studentAlcoholResistanceRangeSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(studentAlcoholResistanceRangeSliderText);

	auto studentAlcoholResistanceRangeSlider = tgui::RangeSlider::create(1, 100);
	studentAlcoholResistanceRangeSlider->setSize(tgui::Layout2d(170, 20));
	studentAlcoholResistanceRangeSlider->setPosition((tgui::Layout2d(15, 525)));
	studentAlcoholResistanceRangeSlider->setStep(1);
	studentAlcoholResistanceRangeSlider->setSelectionEnd(100);
	studentAlcoholResistanceRangeSlider->onRangeChange(rangeSliderOnRangeChange, studentAlcoholResistanceRangeSlider, studentAlcoholResistanceRangeSliderText, "Alcohol resistance:\n");
	gui.add(studentAlcoholResistanceRangeSlider);
	
	auto examinerSuspicionRangeSliderText = tgui::Label::create("Examiner suspicion:\n1 - 100");
	examinerSuspicionRangeSliderText->setSize(tgui::Layout2d(190, 40));
	examinerSuspicionRangeSliderText->setPosition(tgui::Layout2d(5, 575));
	examinerSuspicionRangeSliderText->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	examinerSuspicionRangeSliderText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	gui.add(examinerSuspicionRangeSliderText);

	auto examinerSuspicionRangeSlider = tgui::RangeSlider::create(1, 100);
	examinerSuspicionRangeSlider->setSize(tgui::Layout2d(170, 20));
	examinerSuspicionRangeSlider->setPosition((tgui::Layout2d(15, 625)));
	examinerSuspicionRangeSlider->setStep(1);
	examinerSuspicionRangeSlider->setSelectionEnd(100);
	examinerSuspicionRangeSlider->onRangeChange(rangeSliderOnRangeChange, examinerSuspicionRangeSlider, examinerSuspicionRangeSliderText, "Examiner suspicion:\n");
	gui.add(examinerSuspicionRangeSlider);
}

void exitButtonOnMousePress(sf::RenderWindow& window) {
	window.close();
}

void generatePlotButtonOnMousePress(Simulation* simulation) {
	if (simulation != nullptr)
		simulation->generatePlot();

	//TODO: on error msg
}

void exportDataButtonOnMousePress(Simulation* simulation) {
	if (simulation != nullptr)
		simulation->exportData();

	//TODO: on error msg
}

void startStopButtonOnMousePress() {
	
}

void sliderOnValueChange(std::shared_ptr<tgui::Slider> slider, std::shared_ptr<tgui::Label> sliderText, const std::string& text) {
	sliderText->setText(text + std::to_string(static_cast<uint16_t>(slider->getValue())));
}

void rangeSliderOnRangeChange(std::shared_ptr<tgui::RangeSlider> rangeSlider, std::shared_ptr<tgui::Label> rangeSliderText, const std::string& text) {
	rangeSliderText->setText(text + std::to_string(static_cast<int>(rangeSlider->getSelectionStart()))
		+ " - " + std::to_string(static_cast<int>(rangeSlider->getSelectionEnd())));
}