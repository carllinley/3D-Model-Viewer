#include "MVVector2.h"

#include <iostream>

MVVector2::MVVector2() : MVVector(2) {
	set(0, 0);
}

MVVector2::MVVector2(float x, float y) : MVVector(2) {
	set(x, y);
}

MVVector2::MVVector2(MVVector2& copy) : MVVector(2) {
	set(copy.getElement(0), copy.getElement(1));
}

MVVector2::MVVector2(MVVector& copy) : MVVector(2) {
	set(copy.getElement(0), copy.getElement(1));
}

bool MVVector2::operator!=(MVVector2& toCheck) {
	return p_elements[0] != toCheck.p_elements[0]
		|| p_elements[1] != toCheck.p_elements[1];
}

bool MVVector2::operator==(MVVector2& toCheck) {
	return p_elements[0] == toCheck.p_elements[0]
		&& p_elements[1] == toCheck.p_elements[1];
}

MVVector2 MVVector2::operator+(MVVector2& toAdd) {
	MVVector2 result = MVVector2(*this);

	for (int i = 0; i != 2; i++) {
		result.p_elements[i] += toAdd.p_elements[i];
	}
	return result;
}

MVVector2 MVVector2::operator-(MVVector2& toSubtract) {
	MVVector2 result = MVVector2(*this);

	for (int i = 0; i != 2; i++) {
		result.p_elements[i] -= toSubtract.p_elements[i];
	}
	return result;
}

// this.x = (1 - changeAmnt)*this.x + changeAmnt*finalVec.x;

MVVector2 MVVector2::interpolate(MVVector2& destinationMVVector, float percentage) {
	if (*this == destinationMVVector) {
		return *this;
	}
	return *this * (1 - percentage) + (destinationMVVector * percentage);
}

MVVector2 MVVector2::operator*(float scalar) {
	MVVector2 result = MVVector2(*this);

	for (int i = 0; i != 2; i++) {
		result.p_elements[i] *= scalar;
	}
	return result;
}

MVVector2 MVVector2::operator*(MVVector2& toMultiply) {
	MVVector2 result = MVVector2(*this);

	for (int i = 0; i != 2; i++) {
		result.p_elements[i] *= toMultiply.p_elements[i];
	}
	return result;
}

MVVector2 MVVector2::operator/(MVVector2& toDivide) {
	MVVector2 result = MVVector2(*this);

	for (int i = 0; i != 2; i++) {
		if (result.p_elements[i] != 0 && toDivide.p_elements[i] != 0) {
			result.p_elements[i] /= toDivide.p_elements[i];
		}
	}
	return result;
}

MVVector2 MVVector2::operator/(float scalar) {
	if (scalar == 0) {
		return MVVector2();
	}

	MVVector2 result = MVVector2(*this);

	for (int i = 0; i != 2; i++) {
		if (result.p_elements[i] != 0) {
			result.p_elements[i] /= scalar;
		}
	}
	return result;
}


void MVVector2::set(MVVector2& setTo) {
	set(setTo.getX(), setTo.getY());
}

bool MVVector2::equals(float x, float y) {
	return p_elements[0] == x && p_elements[1] == y;
}

void MVVector2::set(float x, float y) {
	p_elements[0] = x;
	p_elements[1] = y;
}

void MVVector2::set(int x, int y) {
	p_elements[0] = (float) x;
	p_elements[1] = (float) y;
}

MVVector2& MVVector2::setX(float x) {
	p_elements[0] = x;
	return *this;
}

MVVector2& MVVector2::setY(float y) {
	p_elements[1] = y;
	return *this;
}

float MVVector2::getX() {
	return p_elements[0];
}

float MVVector2::getY() {
	return p_elements[1];
}