#pragma once

#include "MVVector.h"

class Vector4;

/*
 * Provides a level of abstraction on top of Vector allowing three-dimensional vectors.
 */
class Vector3 : public MVVector {
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(Vector3& copy);
		Vector3(MVVector& conversion);
		Vector3(Vector4& conversion);

		Vector3& normaliseLocal();
		Vector3& addLocal(Vector3& toAdd);
		Vector3& divideLocal(float scalar);

		Vector3& crossLocal(Vector3& toCross);
		Vector3 Vector3::operator+(Vector3& toAdd);
		Vector3 Vector3::operator-(Vector3& toSubtract);

		float length();

		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void set(float x, float y, float z);

		void set(Vector3 & v);

		float getX();
		float getY();
		float getZ();
};