#pragma once

#include "Matrix.h"

class Vector4 {
	public:
		Vector4();
		Vector4(float x, float y, float z, float w);
		~Vector4();

		Vector4 Vector4::operator+(Vector4& toAdd);
		Vector4 Vector4::operator-(Vector4& toSubtract);

		Matrix toMatrix();

		Vector4& crossLocal(Vector4& toCross);

		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);
		void set(float x, float y, float z, float w);

		float getX();
		float getY();
		float getZ();
		float getW();

		// Vector4 operator*(const Matrix& matrix);
		Vector4 mult(const Matrix& matrix);

	protected:
		float* p_elements = new float[4];
};