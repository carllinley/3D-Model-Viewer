#include "Light.h"

void Light::setPosition(Vector3 & position) {
	this->position.set(position);
}

Vector3& Light::getPosition() {
	return position;
}