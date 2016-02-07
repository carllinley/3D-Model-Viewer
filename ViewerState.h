#pragma once

#include "gui/GUIState.h"
#include "ModelViewer.h"

class ViewerState : public GUIState {
	public:
		ViewerState(const std::string& stateID, GUI* gui, ModelViewer& modelViewer);

		/*
		 Convenience - create and return a slider
		 */
		Slider* createSlider(const std::string& id, Vector2& localTranslation, int defaultValue, Orientation orientation, Lineage* parent);

		/*
		 Init the transform sliders
		 */
		void createSliders();

		/*
		 Init the option area
		 */
		void createOptions();

		void scrollZ(bool forward);

		void buttonPressed(Button& button);
		void valueUpdate(ComboBox& comboBox, const std::string& selectedValue);
		void valueUpdate(Slider& slider, int index);
		void valueUpdate(Checkbox& checkbox, bool isChecked);

	private:
		ModelViewer* p_modelViewer;

		ComboBox* p_textureCombo;

		Checkbox* p_toggleClockwise;
		Checkbox* p_toggleSpinning;

		Slider* p_scaleAll;
		Slider* p_scaleX;
		Slider* p_scaleY;
		Slider* p_scaleZ;

		Slider* p_transX;
		Slider* p_transY;
		Slider* p_transZ;

		float transX, transY, transZ,
			  rotX, rotY, rotZ,
			  scaleX, scaleY, scaleZ;

		void resetTranslation();
};