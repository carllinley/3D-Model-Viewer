#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3() : MVVector(3) {
	set(0, 0, 0);
}

Vector3::Vector3(float x, float y, float z) : MVVector(3) {
	set(x, y, z);
}

Vector3::Vector3(Vector3& copy) : MVVector(3) {
	set(copy.getX(), copy.getY(), copy.getZ());
}

Vector3::Vector3(MVVector& conversion) : MVVector(3) {
	set(conversion.getElement(0), conversion.getElement(1), conversion.getElement(2));
}

Vector3::Vector3(Vector4& conversion) : MVVector(3) {

	p_elements = new float[3] {conversion.getX(), conversion.getY(), conversion.getZ()};
}

Vector3& Vector3::normaliseLocal() {
	float len = length();

	p_elements[0] /= len;
	p_elements[1] /= len;
	p_elements[2] /= len;

	return *this;
}

float Vector3::length() { // AKA magnitude
	float total = 0;

	for (int i = 0; i != 3; i++) {
		total += pow(p_elements[i], 2);
	}
	return sqrt(total);
}

Vector3& Vector3::addLocal(Vector3& toAdd) {
	for (int i = 0; i != 3; i++) {
		p_elements[i] += toAdd.p_elements[i];
	}
	return *this;
}

Vector3& Vector3::divideLocal(float scalar) {
	for (int i = 0; i != 3; i++) {
		p_elements[i] /= scalar;
	}
	return *this;
}

Vector3& Vector3::crossLocal(Vector3& b) {
	float crossX = (p_elements[1] * b.p_elements[2]) - (p_elements[2] * b.p_elements[1]);
	float crossY = (p_elements[2] * b.p_elements[0]) - (p_elements[0] * b.p_elements[2]);
	float crossZ = (p_elements[0] * b.p_elements[1]) - (p_elements[1] * b.p_elements[0]);

	set(crossX, crossY, crossZ);
	return *this;
}

Vector3 Vector3::operator+(Vector3& toAdd) {
	return Vector3();
}

Vector3 Vector3::operator-(Vector3& toSubtract) {
	return static_cast<Vector3>(MVVector::operator-(toSubtract));
}

void Vector3::set(float x, float y, float z) {
	p_elements[0] = x;
	p_elements[1] = y;
	p_elements[2] = z;
}

void Vector3::set(Vector3& v) {
	p_elements[0] = v.getX();
	p_elements[1] = v.getY();
	p_elements[2] = v.getZ();
}

void Vector3::setX(float x) {
	p_elements[0] = x;
}

void Vector3::setY(float y) {
	p_elements[1] = y;
}

void Vector3::setZ(float z) {
	p_elements[2] = z;
}

float Vector3::getX() {
	return p_elements[0];
}

float Vector3::getY() {
	return p_elements[1];
}

float Vector3::getZ() {
	return p_elements[2];
}