#include "Vector4.h"

#include <iostream>

Vector4::Vector4() {
	set(0, 0, 0, 0);
}

Vector4::Vector4(float x, float y, float z, float w) {
	set(x, y, z, w);
}

Vector4::~Vector4() {
	delete[] p_elements;
}

Vector4 Vector4::operator+(Vector4& toAdd) {
	Vector4 result = Vector4(*this);

	for (int i = 0; i != 4; i++) {
		result.p_elements[i] += toAdd.p_elements[i];
	}
	return result;
}

Vector4 Vector4::operator-(Vector4& toSubtract) {
	Vector4 result = Vector4(*this);

	for (int i = 0; i != 4; i++) {
		result.p_elements[i] -= toSubtract.p_elements[i];
	}
	return result;
}

void Vector4::set(float x, float y, float z, float w) {
	p_elements[0] = x;
	p_elements[1] = y;
	p_elements[2] = z;
	p_elements[3] = w;
}

Vector4 Vector4::mult(const Matrix& matrix) {
	Matrix transformed = Matrix(matrix) * toMatrix();

	return Vector4(transformed.getElement(0, 0), transformed.getElement(1, 0), transformed.getElement(2, 0), transformed.getElement(3, 0));
}

Matrix Vector4::toMatrix() {
	Matrix asMatrix = Matrix(4, 1);
	asMatrix.setElement(0, 0, p_elements[0]);
	asMatrix.setElement(1, 0, p_elements[1]);
	asMatrix.setElement(2, 0, p_elements[2]);
	asMatrix.setElement(3, 0, p_elements[3]);

	return asMatrix;
}

Vector4& Vector4::crossLocal(Vector4& toCross) {
	// TODO: insert return statement here
	return *this;
}

void Vector4::setX(float x) {
	p_elements[0] = x;
}

void Vector4::setY(float y) {
	p_elements[1] = y;
}

void Vector4::setZ(float z) {
	p_elements[2] = z;
}

void Vector4::setW(float w) {
	p_elements[3] = w;
}

float Vector4::getX() {
	return p_elements[0];
}

float Vector4::getY() {
	return p_elements[1];
}

float Vector4::getZ() {
	return p_elements[2];
}

float Vector4::getW() {
	return p_elements[3];
}