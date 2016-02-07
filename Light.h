#pragma once

#include "Vector3.h"

class Light {
	public:
		void setPosition(Vector3& position);

		Vector3& getPosition();

	private:
		Vector3 position, direction;
		// ColourRGBA colour;
};