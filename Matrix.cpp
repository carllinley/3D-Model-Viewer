#include "Matrix.h"
#include "MVVector.h"
#include "Vector4.h"

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <sstream>

Matrix::Matrix(int columns, int rows) {
	init(columns, rows, true);
}

Matrix::Matrix(const Matrix& toCopy) {
	init(toCopy.sizeY, toCopy.sizeX, false);

	for (int i = 0; i != sizeX * sizeY; i++) {
		p_elements[i] = toCopy.p_elements[i];
	}
}

Matrix::~Matrix() {
	delete[] p_elements;
}

void Matrix::init(int columns, int rows, bool initialiseToZero) {
	sizeY = columns;
	sizeX = rows;
	p_elements = new float[sizeY * sizeX];

	if (initialiseToZero) {
		for (int i = 0; i != sizeX * sizeY; i++) {
			p_elements[i] = 0;
		}
	}
}

void Matrix::setElements(float values[]) {
	if (p_elements != nullptr) {
		delete[] p_elements;
	}
	p_elements = values;
}

void Matrix::setElement(int row, int column, float value) {
	if (row >= sizeY || column >= sizeX
		|| row < 0 || column < 0) {
		throw std::invalid_argument("Invalid element!");
	}
	*(p_elements + (row * sizeX) + column) = value;
}

float Matrix::getElement(int row, int column) {
	return *(p_elements + (row * sizeX) + column);
}

Matrix Matrix::transpose() {
	Matrix result = Matrix(sizeX, sizeY);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			result.setElement(x, y, getElement(y, x));
		}
	}
	return result;
}

bool Matrix::operator==(Matrix& toCheck) {
	if (&toCheck != this) {
		for (int i = 0; i != sizeX * sizeY; i++) {
			if (p_elements[i] != toCheck.p_elements[i]) {
				return false;
			}
		}
	}
	return true;
}

Matrix Matrix::operator=(Matrix& toAssign) {
	if (&toAssign != this) {
		Matrix result = Matrix(*this);

		delete[] p_elements;
		init(toAssign.sizeX, toAssign.sizeY, false);

		for (int i = 0; i != sizeX * sizeY; i++) {
			p_elements[i] = toAssign.p_elements[i];
		}
	}
	return *this;
}

Matrix Matrix::operator+(Matrix& toAdd) {
	Matrix result = Matrix(*this);

	if (toAdd.sizeX == sizeX && toAdd.sizeY == sizeY) {
		for (int i = 0; i != sizeX * sizeY; i++) {
			result.p_elements[i] += toAdd.p_elements[i];
		}
	}
	return result;
}

Matrix Matrix::operator-(Matrix& toSubtract) {
	Matrix result = Matrix(*this);

	if (toSubtract.sizeX == sizeX
	 && toSubtract.sizeY == sizeY) {
		for (int i = 0; i != sizeX * sizeY; i++) {
			result.p_elements[i] -= toSubtract.p_elements[i];
		}
	}
	return result;
}

Matrix Matrix::operator*(float scalar) {
	Matrix result = Matrix(*this);

	for (int i = 0; i != sizeX * sizeY; i++) {
		result.p_elements[i] *= scalar;
	}
	return result;
}

void Matrix::toIdentity() {
	for (int y = 0; y != sizeY; y++) {
		for (int x = 0; x != sizeX; x++) {
			if (y == x) {
				setElement(y, x, 1);
			}
			else {
				setElement(y, x, 0);
			}
		}
	}
}

Matrix Matrix::operator*(Vector4& toMultiply) {
	return *this * toMultiply.toMatrix();
}

/*
 * TODO: Linearise
 */
Matrix Matrix::operator*(Matrix& toMultiply) {
	if (sizeX != toMultiply.sizeY) {
		std::cout << "Incorrect dimensions for matrix multiplication!" << std::endl;
		throw std::invalid_argument("Incorrect dimensions for matrix multiplication!");
	}

	Matrix result(sizeY, toMultiply.sizeX);
	float value;

	for (int row = 0; row != sizeY; row++) {
		for (int column = 0; column != toMultiply.sizeX; column++) {
			value = 0;

			for (int i = 0; i < sizeX; i++) {
				value += getElement(row, i) * toMultiply.getElement(i, column);
			}
			result.setElement(row, column, value);
		}
	}
	return result;
}

Matrix Matrix::operator/(float scalar) {
	if (scalar == 0) {
		throw std::invalid_argument("Cannot divide by zero!");
	}

	for (int i = 0; i != sizeX * sizeY; i++) {
		if (p_elements[i] != 0) {
			p_elements[i] /= scalar;
		}
	}
	return *this;
}

std::string Matrix::toString() {
	std::ostringstream stringStream;

	stringStream << "[";

	for (int y = 0; y != sizeY; y++) {
		for (int x = 0; x != sizeX; x++) {
			stringStream << getElement(y, x) << (x != sizeX - 1 ? ", " : "");
		}
		stringStream << (y != sizeY - 1 ? "\n " : "]\n");
	}
	return stringStream.str();
}

int Matrix::getRows() {
	return sizeY;
}

int Matrix::getColumns() {
	return sizeX;
}