#include "Menu.h"

#include <Windows.h>

#include "SimulationThread.h"

void setupMenu(tgui::GuiSFML& gui, sf::RenderWindow& window, std::unique_ptr<Simulation>& simulation, SimulationThread& thread) {
	using namespace tgui;

	gui.setTextSize(15);

	auto exitButton = Button::create("Exit");
	exitButton->setSize(Layout2d(190, 40));
	exitButton->setPosition(Layout2d(5, 955));
	exitButton->onMousePress(exitButtonOnMousePress, std::ref(window));
	gui.add(exitButton);

	auto generatePlotButton = Button::create("Generate plot");
	generatePlotButton->setSize(Layout2d(190, 40));
	generatePlotButton->setPosition(Layout2d(5, 905));
	generatePlotButton->onMousePress(generatePlotButtonOnMousePress, std::ref(simulation));
	gui.add(generatePlotButton);

	auto exportDataButton = Button::create("Export Data");
	exportDataButton->setSize(Layout2d(190, 40));
	exportDataButton->setPosition(Layout2d(5, 855));
	exportDataButton->onMousePress(exportDataButtonOnMousePress, std::ref(simulation));
	gui.add(exportDataButton);

	// Board size
	auto boardSizeSliderText = Label::create("Size:");
	boardSizeSliderText->setSize(Layout2d(190, 20));
	boardSizeSliderText->setPosition(Layout2d(5, 55));
	boardSizeSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	boardSizeSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Left);
	gui.add(boardSizeSliderText);

	auto boardSizeEditBox = EditBox::create();
	auto boardSizeSlider = Slider::create(10, 100);
	boardSizeEditBox->setText("10");
	boardSizeEditBox->setSize(Layout2d(35, 25));
	boardSizeEditBox->setPosition(Layout2d(150, 55));
	boardSizeEditBox->setInputValidator("^(100|[1-9][0|5])$");
	boardSizeEditBox->onReturnOrUnfocus(editBoxOnReturnOrUnfocus, boardSizeEditBox, boardSizeSlider);
	gui.add(boardSizeEditBox);

	boardSizeSlider->setSize(Layout2d(170, 20));
	boardSizeSlider->setPosition((Layout2d(15, 85)));
	boardSizeSlider->setStep(5);
	boardSizeSlider->onValueChange(sliderOnValueChange, boardSizeSlider, boardSizeEditBox);
	gui.add(boardSizeSlider);

	// Students
	auto studentsCountSliderText = Label::create("Students:");
	studentsCountSliderText->setSize(Layout2d(190, 20));
	studentsCountSliderText->setPosition(Layout2d(5, 135));
	studentsCountSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	studentsCountSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Left);
	gui.add(studentsCountSliderText);

	auto studentsCountEditBox = EditBox::create();
	auto studentsCountSlider = Slider::create(1, 19999);
	studentsCountEditBox->setText("1");
	studentsCountEditBox->setSize(Layout2d(55, 25));
	studentsCountEditBox->setPosition(Layout2d(130, 135));
	studentsCountEditBox->setInputValidator("^(1[0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9]|[1-9])$");
	studentsCountEditBox->onReturnOrUnfocus(editBoxOnReturnOrUnfocus, studentsCountEditBox, studentsCountSlider);
	gui.add(studentsCountEditBox);

	studentsCountSlider->setSize(Layout2d(170, 20));
	studentsCountSlider->setPosition((Layout2d(15, 165)));
	studentsCountSlider->setStep(1);
	studentsCountSlider->onValueChange(sliderOnValueChange, studentsCountSlider, studentsCountEditBox);
	gui.add(studentsCountSlider);

	// Examiners
	auto examinersCountSliderText = Label::create("Examiners:");
	examinersCountSliderText->setSize(Layout2d(190, 20));
	examinersCountSliderText->setPosition(Layout2d(5, 215));
	examinersCountSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	examinersCountSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Left);
	gui.add(examinersCountSliderText);

	auto examinersCountEditBox = EditBox::create();
	auto examinersCountSlider = Slider::create(1, 19999);
	examinersCountEditBox->setText("1");
	examinersCountEditBox->setSize(Layout2d(55, 25));
	examinersCountEditBox->setPosition(Layout2d(130, 215));
	examinersCountEditBox->setInputValidator("^(1[0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9]|[1-9])$");
	examinersCountEditBox->onReturnOrUnfocus(editBoxOnReturnOrUnfocus, examinersCountEditBox, examinersCountSlider);
	gui.add(examinersCountEditBox);

	examinersCountSlider->setSize(Layout2d(170, 20));
	examinersCountSlider->setPosition((Layout2d(15, 245)));
	examinersCountSlider->setStep(1);
	examinersCountSlider->onValueChange(sliderOnValueChange, examinersCountSlider, examinersCountEditBox);
	gui.add(examinersCountSlider);

	// Drunk students
	auto drunkStudentsCountSliderText = Label::create("Drunk students:");
	drunkStudentsCountSliderText->setSize(Layout2d(190, 20));
	drunkStudentsCountSliderText->setPosition(Layout2d(5, 295));
	drunkStudentsCountSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	drunkStudentsCountSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Left);
	gui.add(drunkStudentsCountSliderText);

	auto drunkStudentsCountEditBox = EditBox::create();
	auto drunkStudentsCountSlider = Slider::create(1, 19999);
	drunkStudentsCountEditBox->setText("1");
	drunkStudentsCountEditBox->setSize(Layout2d(52, 25));
	drunkStudentsCountEditBox->setPosition(Layout2d(133, 295));
	drunkStudentsCountEditBox->setInputValidator("^(1[0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9]|[1-9])$");
	drunkStudentsCountEditBox->onReturnOrUnfocus(editBoxOnReturnOrUnfocus, drunkStudentsCountEditBox, drunkStudentsCountSlider);
	gui.add(drunkStudentsCountEditBox);

	drunkStudentsCountSlider->setSize(Layout2d(170, 20));
	drunkStudentsCountSlider->setPosition((Layout2d(15, 325)));
	drunkStudentsCountSlider->setStep(1);
	drunkStudentsCountSlider->onValueChange(sliderOnValueChange, drunkStudentsCountSlider, drunkStudentsCountEditBox);
	gui.add(drunkStudentsCountSlider);

	// Student knowledge
	auto studentKnowledgeRangeSliderText = Label::create("Students knowledge:");
	studentKnowledgeRangeSliderText->setSize(Layout2d(190, 20));
	studentKnowledgeRangeSliderText->setPosition(Layout2d(5, 375));
	studentKnowledgeRangeSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	studentKnowledgeRangeSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Center);
	gui.add(studentKnowledgeRangeSliderText);

	auto studentKnowledgeRangeSlider = RangeSlider::create(1, 101);
	auto studentKnowledgeRangeEditBoxStart = EditBox::create();
	auto studentKnowledgeRangeEditBoxEnd = EditBox::create();

	studentKnowledgeRangeEditBoxStart->setText("1");
	studentKnowledgeRangeEditBoxStart->setSize(Layout2d(35, 25));
	studentKnowledgeRangeEditBoxStart->setPosition(Layout2d(30, 395));
	studentKnowledgeRangeEditBoxStart->setInputValidator("^(101|100|[1-9][0-9]|[1-9])$");
	studentKnowledgeRangeEditBoxStart->onReturnOrUnfocus(editBoxOnReturnOrUnfocusRange, studentKnowledgeRangeEditBoxStart,
		studentKnowledgeRangeEditBoxEnd, studentKnowledgeRangeSlider);
	gui.add(studentKnowledgeRangeEditBoxStart);

	auto studentKnowledgeRangeSeparator = Label::create("-");
	studentKnowledgeRangeSeparator->setPosition(Layout2d(95, 395));
	gui.add(studentKnowledgeRangeSeparator);

	studentKnowledgeRangeEditBoxEnd->setText("100");
	studentKnowledgeRangeEditBoxEnd->setSize(Layout2d(35, 25));
	studentKnowledgeRangeEditBoxEnd->setPosition(Layout2d(135, 395));
	studentKnowledgeRangeEditBoxEnd->setInputValidator("^(101|100|[1-9][0-9]|[1-9])$");
	studentKnowledgeRangeEditBoxEnd->onReturnOrUnfocus(editBoxOnReturnOrUnfocusRange, studentKnowledgeRangeEditBoxStart,
		studentKnowledgeRangeEditBoxEnd, studentKnowledgeRangeSlider);
	gui.add(studentKnowledgeRangeEditBoxEnd);

	studentKnowledgeRangeSlider->setSize(Layout2d(170, 20));
	studentKnowledgeRangeSlider->setPosition((Layout2d(15, 425)));
	studentKnowledgeRangeSlider->setStep(1);
	studentKnowledgeRangeSlider->setSelectionEnd(100);
	studentKnowledgeRangeSlider->onRangeChange(rangeSliderOnRangeChange, studentKnowledgeRangeSlider,
		studentKnowledgeRangeEditBoxStart, studentKnowledgeRangeEditBoxEnd);
	gui.add(studentKnowledgeRangeSlider);

	// Alcohol resistance
	auto studentAlcoholResistanceRangeSliderText = Label::create("Alcohol resistance:");
	studentAlcoholResistanceRangeSliderText->setSize(Layout2d(190, 40));
	studentAlcoholResistanceRangeSliderText->setPosition(Layout2d(5, 460));
	studentAlcoholResistanceRangeSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	studentAlcoholResistanceRangeSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Center);
	gui.add(studentAlcoholResistanceRangeSliderText);

	auto studentAlcoholResistanceRangeSlider = RangeSlider::create(1, 100);
	auto studentAlcoholResistanceRangeEditBoxStart = EditBox::create();
	auto studentAlcoholResistanceRangeEditBoxEnd = EditBox::create();

	studentAlcoholResistanceRangeEditBoxStart->setText("1");
	studentAlcoholResistanceRangeEditBoxStart->setSize(Layout2d(35, 25));
	studentAlcoholResistanceRangeEditBoxStart->setPosition(Layout2d(30, 495));
	studentAlcoholResistanceRangeEditBoxStart->setInputValidator("^(100|[1-9][0-9]|[1-9])$");
	studentAlcoholResistanceRangeEditBoxStart->onReturnOrUnfocus(editBoxOnReturnOrUnfocusRange, studentAlcoholResistanceRangeEditBoxStart,
		studentAlcoholResistanceRangeEditBoxEnd, studentAlcoholResistanceRangeSlider);
	gui.add(studentAlcoholResistanceRangeEditBoxStart);

	auto studentAlcoholResistanceRangeSeparator = Label::create("-");
	studentAlcoholResistanceRangeSeparator->setPosition(Layout2d(95, 495));
	gui.add(studentAlcoholResistanceRangeSeparator);

	studentAlcoholResistanceRangeEditBoxEnd->setText("100");
	studentAlcoholResistanceRangeEditBoxEnd->setSize(Layout2d(35, 25));
	studentAlcoholResistanceRangeEditBoxEnd->setPosition(Layout2d(135, 495));
	studentAlcoholResistanceRangeEditBoxEnd->setInputValidator("^(100|[1-9][0-9]|[1-9])$");
	studentAlcoholResistanceRangeEditBoxEnd->onReturnOrUnfocus(editBoxOnReturnOrUnfocusRange, studentAlcoholResistanceRangeEditBoxStart,
		studentAlcoholResistanceRangeEditBoxEnd, studentAlcoholResistanceRangeSlider);
	gui.add(studentAlcoholResistanceRangeEditBoxEnd);

	studentAlcoholResistanceRangeSlider->setSize(Layout2d(170, 20));
	studentAlcoholResistanceRangeSlider->setPosition((Layout2d(15, 525)));
	studentAlcoholResistanceRangeSlider->setStep(1);
	studentAlcoholResistanceRangeSlider->setSelectionEnd(100);
	studentAlcoholResistanceRangeSlider->onRangeChange(rangeSliderOnRangeChange, studentAlcoholResistanceRangeSlider,
		studentAlcoholResistanceRangeEditBoxStart, studentAlcoholResistanceRangeEditBoxEnd);
	gui.add(studentAlcoholResistanceRangeSlider);

	// Examiner suspicion
	auto examinerSuspicionRangeSliderText = Label::create("Examiner suspicion:");
	examinerSuspicionRangeSliderText->setSize(Layout2d(190, 40));
	examinerSuspicionRangeSliderText->setPosition(Layout2d(5, 560));
	examinerSuspicionRangeSliderText->setVerticalAlignment(Label::VerticalAlignment::Center);
	examinerSuspicionRangeSliderText->setHorizontalAlignment(Label::HorizontalAlignment::Center);
	gui.add(examinerSuspicionRangeSliderText);

	auto examinerSuspicionRangeSlider = RangeSlider::create(0, 100);
	auto examinerSuspicionRangeEditBoxStart = EditBox::create();
	auto examinerSuspicionRangeEditBoxEnd = EditBox::create();

	examinerSuspicionRangeEditBoxStart->setText("1");
	examinerSuspicionRangeEditBoxStart->setSize(Layout2d(35, 25));
	examinerSuspicionRangeEditBoxStart->setPosition(Layout2d(30, 595));
	examinerSuspicionRangeEditBoxStart->setInputValidator("^(100|[1-9][0-9]|[0-9])$");
	examinerSuspicionRangeEditBoxStart->onReturnOrUnfocus(editBoxOnReturnOrUnfocusRange, examinerSuspicionRangeEditBoxStart,
		examinerSuspicionRangeEditBoxEnd, examinerSuspicionRangeSlider);
	gui.add(examinerSuspicionRangeEditBoxStart);

	auto examinerSuspicionRangeSeparator = Label::create("-");
	examinerSuspicionRangeSeparator->setPosition(Layout2d(95, 595));
	gui.add(examinerSuspicionRangeSeparator);

	examinerSuspicionRangeEditBoxEnd->setText("100");
	examinerSuspicionRangeEditBoxEnd->setSize(Layout2d(35, 25));
	examinerSuspicionRangeEditBoxEnd->setPosition(Layout2d(135, 595));
	examinerSuspicionRangeEditBoxEnd->setInputValidator("^(100|[1-9][0-9]|[0-9])$");
	examinerSuspicionRangeEditBoxEnd->onReturnOrUnfocus(editBoxOnReturnOrUnfocusRange, examinerSuspicionRangeEditBoxStart,
		examinerSuspicionRangeEditBoxEnd, examinerSuspicionRangeSlider);
	gui.add(examinerSuspicionRangeEditBoxEnd);

	examinerSuspicionRangeSlider->setSize(Layout2d(170, 20));
	examinerSuspicionRangeSlider->setPosition((Layout2d(15, 625)));
	examinerSuspicionRangeSlider->setStep(1);
	examinerSuspicionRangeSlider->setSelectionStart(1);
	examinerSuspicionRangeSlider->setSelectionEnd(100);
	examinerSuspicionRangeSlider->onRangeChange(rangeSliderOnRangeChange, examinerSuspicionRangeSlider,
		examinerSuspicionRangeEditBoxStart, examinerSuspicionRangeEditBoxEnd);
	gui.add(examinerSuspicionRangeSlider);

	auto stopButton = Button::create("Stop");
	auto startButton = Button::create("Start");
	startButton->setSize(Layout2d(190, 40));
	startButton->setPosition(Layout2d(5, 5));
	startButton->onMousePress(startButtonOnMousePress, stopButton, startButton, std::ref(simulation), std::ref(thread), [=]() -> std::map<std::string, std::any> {
		std::map<std::string, std::any> map{
			std::make_pair("board_size", static_cast<uint16_t>(boardSizeSlider->getValue())),
			std::make_pair("students_count", static_cast<uint16_t>(studentsCountSlider->getValue())),
			std::make_pair("drunk_students_count", static_cast<uint16_t>(drunkStudentsCountSlider->getValue())),
			std::make_pair("examiners_count", static_cast<uint16_t>(examinersCountSlider->getValue())),
			std::make_pair("examiners_suspicion",
				std::make_pair(static_cast<uint16_t>(examinerSuspicionRangeSlider->getSelectionStart()),
					static_cast<uint16_t>(examinerSuspicionRangeSlider->getSelectionEnd()))),
			std::make_pair("student_knowledge",
				std::make_pair(static_cast<uint16_t>(studentKnowledgeRangeSlider->getSelectionStart()),
					static_cast<uint16_t>(studentKnowledgeRangeSlider->getSelectionEnd()))),
			std::make_pair("student_resistance",
				std::make_pair(static_cast<uint16_t>(studentAlcoholResistanceRangeSlider->getSelectionStart()),
					static_cast<uint16_t>(studentAlcoholResistanceRangeSlider->getSelectionEnd()))) };
		return map;
		});
	gui.add(startButton);

	stopButton->setSize(Layout2d(190, 40));
	stopButton->setPosition(Layout2d(5, 5));
	stopButton->setVisible(false);
	stopButton->onMousePress(stopButtonOnMousePress, stopButton, startButton, std::ref(thread));
	gui.add(stopButton);

	thread.setSimulationFinishCallback(onSimulationFinish, stopButton, startButton);
}

void exitButtonOnMousePress(sf::RenderWindow& window) {
	window.close();
}

void generatePlotButtonOnMousePress(std::unique_ptr<Simulation>& simulation) {
	if (simulation == nullptr) {
		MessageBoxA(nullptr, "Cannot generate plot because simulation is not initialized", "Warring!", MB_OK | MB_ICONWARNING);
		return;
	}

	try {
		simulation->generatePlot();
	}
	catch (const std::exception& exception) {
		std::cerr << exception.what() << std::endl;
	}
}

void exportDataButtonOnMousePress(std::unique_ptr<Simulation>& simulation) {
	if (simulation != nullptr) {
		MessageBoxA(nullptr, "Cannot export data because simulation is not initialized", "Warning!", MB_OK | MB_ICONWARNING);
		return;
	}

	try {
		simulation->exportData();
	}
	catch (const std::exception& exception) {
		std::cerr << exception.what() << std::endl;
	}
}

void startButtonOnMousePress(tgui::Button::Ptr stopButton, tgui::Button::Ptr startButton, std::unique_ptr<Simulation>& simulation, SimulationThread& thread, std::function<std::map<std::string, std::any>()> initParametersListFunc) {
	auto initParametersList = initParametersListFunc();

	if (std::any_cast<uint16_t>(initParametersList["drunk_students_count"]) > std::any_cast<uint16_t>(initParametersList["students_count"]))
	{
		MessageBoxA(nullptr, "Drunk students count exceeds all students count!\nStudents count should be more or equal to drunk students count.", "Error!", MB_OK | MB_ICONWARNING);
		return;
	}

	if (std::any_cast<uint16_t>(initParametersList["examiners_count"]) + std::any_cast<uint16_t>(initParametersList["students_count"]) >
		2 * std::pow(std::any_cast<uint16_t>(initParametersList["board_size"]), 2))
	{
		std::string msg = "Agents count exceeds maximal agents to board fields ratio: 2";
		msg += "\nDefine less agents or larger board size.";
		MessageBoxA(nullptr, msg.c_str(), "Error!", MB_OK | MB_ICONWARNING);
		return;
	}

	simulation = std::make_unique<Simulation>(Simulation(std::any_cast<uint16_t>(initParametersList["board_size"]),
		std::any_cast<uint16_t>(initParametersList["students_count"]),
		std::any_cast<uint16_t>(initParametersList["examiners_count"]),
		std::any_cast<uint16_t>(initParametersList["drunk_students_count"]),
		std::any_cast<std::pair<uint16_t, uint16_t>>(initParametersList["examiners_suspicion"]),
		std::any_cast<std::pair<uint16_t, uint16_t>>(initParametersList["student_knowledge"]),
		std::any_cast<std::pair<uint16_t, uint16_t>>(initParametersList["student_resistance"])));

	thread.runSimulationThread(simulation);
	stopButton->setVisible(true);
	startButton->setVisible(false);
}

void sliderOnValueChange(const std::shared_ptr<tgui::Slider>& slider, const std::shared_ptr<tgui::EditBox>& editBox) {
	editBox->setText(std::to_string(static_cast<uint16_t>(slider->getValue())));
}

void rangeSliderOnRangeChange(const std::shared_ptr<tgui::RangeSlider>& rangeSlider, const std::shared_ptr<tgui::EditBox>& editBoxStart,
	const std::shared_ptr<tgui::EditBox>& editBoxEnd) {
	editBoxStart->setText(std::to_string(static_cast<int>(rangeSlider->getSelectionStart())));
	editBoxEnd->setText(std::to_string(static_cast<int>(rangeSlider->getSelectionEnd())));
}

void editBoxOnReturnOrUnfocus(const std::shared_ptr<tgui::EditBox>& editBox, const std::shared_ptr<tgui::Slider>& slider) {
	const auto& editBoxText = editBox->getText();
	if (editBoxText == "")
		editBox->setText(std::to_string(static_cast<int>(slider->getValue())));
	else
		slider->setValue(editBoxText.toFloat());
}

void editBoxOnReturnOrUnfocusRange(const std::shared_ptr<tgui::EditBox>& editBoxStart,
	const std::shared_ptr<tgui::EditBox>& editBoxEnd,
	const std::shared_ptr<tgui::RangeSlider>& rangeSlider) {
	const auto& editBoxTextStart = editBoxStart->getText();
	const auto& editBoxTextEnd = editBoxEnd->getText();

	// This block can safely return because no other changes could be made if statement is true
	if (editBoxTextStart == "") {
		editBoxStart->setText(std::to_string(static_cast<int>(rangeSlider->getSelectionStart())));
		return;
	}
	if (editBoxTextEnd == "") {
		editBoxEnd->setText(std::to_string(static_cast<int>(rangeSlider->getSelectionEnd())));
		return;
	}

	if (editBoxTextStart.toInt() > editBoxTextEnd.toInt()) {
		const auto swap = editBoxTextEnd;
		editBoxEnd->setText(editBoxTextStart);
		editBoxStart->setText(swap);
	}

	rangeSlider->onRangeChange.setEnabled(false);
	rangeSlider->setSelectionStart(editBoxTextStart.toFloat());
	rangeSlider->setSelectionEnd(editBoxTextEnd.toFloat());
	rangeSlider->onRangeChange.setEnabled(true);
}

void stopButtonOnMousePress(tgui::Button::Ptr stopButton, tgui::Button::Ptr startButton, SimulationThread& thread) {
	thread.stopSimulationThread();
	onSimulationFinish(stopButton, startButton);
}

void onSimulationFinish(tgui::Button::Ptr stopButton, tgui::Button::Ptr startButton) {
	stopButton->setVisible(false);
	startButton->setVisible(true);
}