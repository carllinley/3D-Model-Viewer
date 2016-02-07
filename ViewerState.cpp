#include "ViewerState.h"

#include <iostream>

ViewerState::ViewerState(const std::string& stateID, GUI* gui, ModelViewer& modelViewer) : GUIState(stateID, gui) {
	createSliders();
	createOptions();
	p_modelViewer = &modelViewer;
}

Slider* ViewerState::createSlider(const std::string& id, Vector2& localTranslation, int defaultValue, Orientation orientation, Lineage* parent) {
	Slider* s = new Slider(id, localTranslation, 230, orientation);
	s->setIndex(defaultValue);
	parent->attachChild(s);
	return s;
}

void ViewerState::createSliders() {
	Vector2 rotLabelOffset = Vector2(-15, 12);
	Vector2 transLabelOffset = Vector2(-6, 6);

	// Rotation
	GUIElement* rotContainer = new GUIElement("rotContainer", Vector2(235, -310));
	rotContainer->attachChild(new Label("rotTitle", "Rotation", 12, Vector2(-15, 30)));

	Slider* rotX = createSlider("rotateX", Vector2(0, 0), 0, HORIZONTAL, rotContainer);
	rotX->setColour(ColourRGBA::RED);
	rotX->attachChild(new Label("rotXLabel", "X:", 10, rotLabelOffset));

	Slider* rotY = createSlider("rotateY", Vector2(0, -30), 0, HORIZONTAL, rotContainer);
	rotY->setColour(ColourRGBA::GREEN);
	rotY->attachChild(new Label("rotYLabel", "Y:", 10, rotLabelOffset));

	Slider* rotZ = createSlider("rotateZ", Vector2(0, -60), 0, HORIZONTAL, rotContainer);
	rotZ->setColour(ColourRGBA::BLUE);
	rotZ->attachChild(new Label("rotZLabel", "Z:", 10, rotLabelOffset));

	// Translate

	GUIElement* transContainer = new GUIElement("transContainer", Vector2(235, -155));
	transContainer->attachChild(new Label("transTitle", "Translation", 12, Vector2(-15, 30)));

	p_transX = createSlider("translateX", Vector2(0, 0), 50, HORIZONTAL, transContainer);
	p_transX->setColour(ColourRGBA::RED);
	p_transX->attachChild(new Label("transXLabel", "X:", 10, rotLabelOffset));

	p_transY = createSlider("translateY", Vector2(0, -30), 50, HORIZONTAL, transContainer);
	p_transY->setColour(ColourRGBA::GREEN);
	p_transY->attachChild(new Label("transYLabel", "Y:", 10, rotLabelOffset));

	p_transZ = createSlider("translateZ", Vector2(0, -60), 50, HORIZONTAL, transContainer);
	p_transZ->setColour(ColourRGBA::BLUE);
	p_transZ->attachChild(new Label("transZLabel", "Z:", 10, rotLabelOffset));

	// Scale

	GUIElement* scaleContainer = new GUIElement("scaleContainer", Vector2(235, 30));
	scaleContainer->attachChild(new Label("scaleTitle", "Scale", 12, Vector2(-15, 30)));

	p_scaleAll = createSlider("scaleAll", Vector2(), 50, HORIZONTAL, scaleContainer);
	p_scaleAll->attachChild(new Label("scaleAllLabel", "A:", 10, rotLabelOffset));

	p_scaleX = createSlider("scaleX", Vector2(0, -30), 50, HORIZONTAL, scaleContainer);
	p_scaleX->setColour(ColourRGBA::RED);
	p_scaleX->attachChild(new Label("scaleXLabel", "X:", 10, rotLabelOffset));

	p_scaleY = createSlider("scaleY", Vector2(0, -60), 50, HORIZONTAL, scaleContainer);
	p_scaleY->setColour(ColourRGBA::GREEN);
	p_scaleY->attachChild(new Label("scaleYLabel", "Y:", 10, rotLabelOffset));

	p_scaleZ = createSlider("scaleZ", Vector2(0, -90), 50, HORIZONTAL, scaleContainer);
	p_scaleZ->setColour(ColourRGBA::BLUE);
	p_scaleZ->attachChild(new Label("scaleZLabel", "Z:", 10, rotLabelOffset));

	// Slap 'em in

	attachChild(scaleContainer);
	attachChild(rotContainer);
	attachChild(transContainer);
}

void ViewerState::createOptions() {
	Vector2 labelOffset = Vector2(12, 8);

	GUIElement* optionsContainer = new GUIElement("optionsContainer", Vector2(-490, -370));

	ComboBox* modelBox = new ComboBox("modelCombo", Vector2(83, 210), 165);
	modelBox->setOptions(8, "Crate", "Cone", "Cube", "Deathstar", "Deer", "TARDIS", "Teapot", "Teddy");
	modelBox->setSelected("Teapot");
	modelBox->attachChild(new Label("modelLabel", "Model:", Vector2(-45, 11)));
	optionsContainer->attachChild(modelBox);

	p_textureCombo = new ComboBox("textureCombo", Vector2(103, 175), 165);
	p_textureCombo->attachChild(new Label("texLabel", "Texture:", Vector2(-55, 11)));
	p_textureCombo->setOptions(5, "Untextured", "Crate", "Cone", "Deer", "Derby");
	optionsContainer->attachChild(p_textureCombo);

	p_toggleSpinning = new Checkbox("togSpinning", Vector2(0, 40));
	p_toggleSpinning->attachChild(new Label("spLabel", "Idle spin", 9, labelOffset));
	p_toggleSpinning->setTicked(true);

	Checkbox* p_toggleWireframe = new Checkbox("togWireframe", Vector2(0, 10));
	p_toggleWireframe->attachChild(new Label("wfLabel", "Wireframe", 9, labelOffset));

	Checkbox* p_toggleLighting = new Checkbox("togLighting", Vector2(0, 70));
	p_toggleLighting->attachChild(new Label("lightLabel", "Lighting", 9, labelOffset));
	p_toggleLighting->setTicked(true);

	p_toggleClockwise = new Checkbox("togClockwise", Vector2(0, 100));
	p_toggleClockwise->attachChild(new Label("togClockLabel", "Draw clockwise", 9, labelOffset));
	p_toggleClockwise->setTicked(true);

	Checkbox* p_toggleCulling = new Checkbox("togCulling", Vector2(0, 130));
	p_toggleCulling->attachChild(new Label("cullLabel", "Back-face culling", 9, labelOffset));
	p_toggleCulling->setTicked(true);

	optionsContainer->attachChild(p_toggleSpinning);
	optionsContainer->attachChild(p_toggleWireframe);
	optionsContainer->attachChild(p_toggleLighting);
	optionsContainer->attachChild(p_toggleClockwise);
	optionsContainer->attachChild(p_toggleCulling);

	attachChild(optionsContainer);
}

void ViewerState::buttonPressed(Button& button) {
}

void ViewerState::resetTranslation() {
	p_transX->setIndex(50);
	p_transY->setIndex(50);
	p_transZ->setIndex(50);
}

void ViewerState::scrollZ(bool forward) {
	int newIndex = p_transZ->getSelectedIndex() + (forward ? 2 : -2);

	if (newIndex >= 0 && newIndex <= 100) {
		p_transZ->setIndex(newIndex);
	}
}

void ViewerState::valueUpdate(ComboBox& comboBox, const std::string& selectedValue) {
	if (comboBox == "modelCombo") {
		p_modelViewer->loadModel(selectedValue);

		resetTranslation();
		p_textureCombo->setSelected("Untextured");

		// Set optimal settings
		if (selectedValue == "Teapot") {
			p_toggleClockwise->setTicked(true);
			p_scaleAll->setIndex(10);
			p_transZ->setIndex(25);
		}
		else if (selectedValue == "Cube") {
			p_toggleClockwise->setTicked(false);
			p_scaleAll->setIndex(100);
			p_transZ->setIndex(75);
		}
		else if (selectedValue == "Cone") {
			p_toggleClockwise->setTicked(false);
			p_scaleAll->setIndex(100);
			p_transZ->setIndex(75);
			p_textureCombo->setSelected("Cone");
		}
		else if (selectedValue == "Teddy") {
			p_toggleClockwise->setTicked(false);
			p_transZ->setIndex(25);
		}
		else if (selectedValue == "Crate") {
			p_toggleClockwise->setTicked(true);
			p_transZ->setIndex(25);
			p_textureCombo->setSelected("Crate");
		}
		else if (selectedValue == "TARDIS") {
			p_toggleClockwise->setTicked(false);
			p_transZ->setIndex(60);
		}
		else if (selectedValue == "Death star") {
			p_toggleClockwise->setTicked(false);
			p_transZ->setIndex(60);
		}
	}
	else {
		if (selectedValue == "Untextured") {
			p_modelViewer->setTexture("");
		}
		else {
			p_modelViewer->setTexture(selectedValue);
		}
	}
}

void ViewerState::valueUpdate(Slider& slider, int index) {
	if (slider.getID().substr(0, 3) == "rot") {
		float deg = (360 / 100 * (float) index) / 50;

		if (slider == "rotateX") {
			rotX = deg;
		}
		if (slider == "rotateY") {
			rotY = deg;
		}
		if (slider == "rotateZ") {
			rotZ = deg;
		}
		p_modelViewer->rotate(rotX, rotY, rotZ);
		p_toggleSpinning->setTicked(false);
	}
	else if (slider.getID().substr(0, 3) == "tra") {
		float translation = (float) (index - 50);

		if (slider == "translateX") {
			transX = translation;
		}
		if (slider == "translateY") {
			transY = translation;
		}
		if (slider == "translateZ") {
			transZ = translation;
		}
		p_modelViewer->translate(transX, transY, transZ - 50);
	}
	else {
		if (slider == "scaleAll") {
			p_scaleX->setIndex(index);
			p_scaleY->setIndex(index);
			p_scaleZ->setIndex(index);
			return;
		}

		float scale = (float) index / 50.0f;

		if (slider == "scaleX") {
			scaleX = scale;
		}
		if (slider == "scaleY") {
			scaleY = scale;
		}
		if (slider == "scaleZ") {
			scaleZ = scale;
		}
		p_modelViewer->scale(scaleX, scaleY, scaleZ);
	}
}

void ViewerState::valueUpdate(Checkbox& checkbox, bool isChecked) {
	if (checkbox == "togWireframe") {
		p_modelViewer->setWireframe(isChecked);
	}
	if (checkbox == "togSpinning") {
		p_modelViewer->setIdlySpinning(isChecked);

		if (!isChecked) {
			p_modelViewer->rotate(rotX, rotY, rotZ);
		}
	}
	if (checkbox == "togLighting") {
		p_modelViewer->setLighting(isChecked);
	}
	if (checkbox == "togCulling") {
		p_modelViewer->setCulling(isChecked);
	}
	if (checkbox == "togClockwise") {
		p_modelViewer->setClockwise(isChecked);
	}
}