#include "MVVector.h"
#include "math.h"

#include <sstream>
#include <stdexcept>
#include <iostream>

MVVector::MVVector(int size) {
	dimension = size;
	p_elements = new float[size];
}

MVVector::MVVector(int size, float* elements) {
	dimension = size;
	p_elements = elements;
}

MVVector::MVVector(MVVector& copy) {
	p_elements = new float[copy.dimension];
	memcpy(p_elements, copy.p_elements, sizeof(p_elements));
}

MVVector::MVVector(MVVector2& v) {
}


MVVector::~MVVector() {
	delete p_elements;
}

void MVVector::setTo(int value) {
	memset(p_elements, value, sizeof(p_elements));
}

void MVVector::setElement(int index, float value) {
	p_elements[index] = value;
}

float MVVector::getElement(int index) {
	return p_elements[index];
}

// Standard MVVector operations

/*MVVector& MVVector::operator=(MVVector& toAssign) {
	if (dimension != toAssign.dimension) {
		throw std::invalid_argument("Cannot assign between MVVectors of differing dimensions!");
	}

	for (int i = 0; i != dimension; i++) {
		p_elements[i] = toAssign.p_elements[i];
	}
	return *this;
}*/

MVVector& MVVector::operator+(MVVector& toAdd) {
	if (dimension == toAdd.dimension) {
		for (int i = 0; i != dimension; i++) {
			p_elements[i] += toAdd.p_elements[i];
		}
	}
	return *this;
}

MVVector& MVVector::operator-(MVVector& toSubtract) {
	if (dimension == toSubtract.dimension) {
		for (int i = 0; i != dimension; i++) {
			p_elements[i] -= toSubtract.p_elements[i];
		}
	}
	return *this;
}

MVVector& MVVector::operator*(float scalar) {
	for (int i = 0; i != dimension; i++) {
		p_elements[i] *= scalar;
	}
	return *this;
}

MVVector& MVVector::operator*(MVVector& toMultiply) {
	if (dimension == toMultiply.dimension) {
		for (int i = 0; i != dimension; i++) {
			p_elements[i] *= toMultiply.p_elements[i];
		}
	}
	return *this;
}

MVVector& MVVector::operator/(float scalar) {
	if (scalar != 0) {
		for (int i = 0; i != dimension; i++) {
			if (p_elements[i] != 0) {
				p_elements[i] /= scalar;
			}
		}
	}
	return *this;
}

MVVector& MVVector::operator/(MVVector& toDivide) {
	if (dimension == toDivide.dimension) {
		for (int i = 0; i != dimension; i++) {
			if (p_elements[i] != 0 && toDivide.p_elements[i] != 0) {
				p_elements[i] /= toDivide.p_elements[i];
			}
		}
	}
	return *this;
}

float MVVector::dot(MVVector& v) {
	if (dimension != v.dimension) {
		throw std::invalid_argument("Cannot dot MVVectors of differing dimensions!");
	}

	float dot = 0;

	for (int i = 0; i != dimension; i++) {
		dot += p_elements[i] * v.p_elements[i];
	}
	return dot;
}

float MVVector::length() { // AKA magnitude
	float total = 0;

	for (int i = 0; i != dimension; i++) {
		total += pow(p_elements[i], 2);
	}
	return sqrt(total);
}

int MVVector::getDimension() {
	return dimension;
}

float* MVVector::elements() {
	return p_elements;
}

std::string MVVector::toString() {
	std::ostringstream stringStream;

	stringStream << "(";

	for (int i = 0; i != dimension; i++) {
		stringStream << p_elements[i] << (i != dimension - 1 ? ", " : ")");
	}
	return stringStream.str();
}